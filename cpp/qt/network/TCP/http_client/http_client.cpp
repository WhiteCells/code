#include "http_client.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QJsonDocument>
#include <QJsonObject>

HttpClient::HttpClient(QWidget *parent) :
    QWidget(parent),
    manager_(new QNetworkAccessManager(this)),
    url_line_edit_(new QLineEdit()),
    post_btn_(new QPushButton("post")),
    get_btn_(new QPushButton("get")),
    log_text_edit_(new QTextEdit()) {
    QVBoxLayout *main_layout = new QVBoxLayout(this);
    QHBoxLayout *send_layout = new QHBoxLayout();
    url_line_edit_->setPlaceholderText("http://example.com");
    send_layout->addWidget(url_line_edit_);
    send_layout->addWidget(post_btn_);
    send_layout->addWidget(get_btn_);
    main_layout->addWidget(log_text_edit_);
    main_layout->addLayout(send_layout);

    this->connect(post_btn_, &QPushButton::clicked,
                  this, &HttpClient::slot_post_request);
    this->connect(get_btn_, &QPushButton::clicked,
                  this, &HttpClient::slot_get_request);
}

HttpClient::~HttpClient() {
}

void HttpClient::slot_post_request() {
    QNetworkRequest request;
    request.setUrl(QUrl(url_line_edit_->text()));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QJsonObject root;
    root["user"] = "cells";
    root["contact"] = "xxxx";
    QJsonDocument doc(root);
    QByteArray data = doc.toJson();
    QNetworkReply *response = manager_->post(request, data);
    this->connect(response, &QNetworkReply::finished, this, [=]() {
        if (response->error() == QNetworkReply::NoError) {
            QString res(response->readAll());
            log_text_edit_->setPlainText(res);
        } else {
            log_text_edit_->setPlainText(response->errorString());
        }
        response->deleteLater();
    });
}

void HttpClient::slot_get_request() {
    QUrl url(url_line_edit_->text());
    QNetworkRequest request(url);
    QNetworkReply *response = manager_->get(request);
    this->connect(response, &QNetworkReply::finished, this, [=]() {
        if (response->error() == QNetworkReply::NoError) {
            QString res(response->readAll());
            log_text_edit_->setPlainText(res);
        } else {
            log_text_edit_->setPlainText(response->errorString());
        }
        response->deleteLater();
    });
}
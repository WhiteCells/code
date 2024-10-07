#include "widget.h"

#include <QVBoxLayout>
#include <QUrl>
#include <QWebEngineView>
#include <QLineEdit>

WebBrowser::WebBrowser(QWidget *parent) :
    QWidget(parent)
{
    // 创建布局
    QVBoxLayout *layout = new QVBoxLayout(this);

    // 创建地址栏
    addressBar = new QLineEdit(this);
    layout->addWidget(addressBar);

    // 创建WebEngine视图
    webView = new QWebEngineView(this);
    layout->addWidget(webView);

    // 设置初始页面
    // webView->setUrl(QUrl("https://www.qt.io"));

    // 连接地址栏的信号
    connect(addressBar, &QLineEdit::returnPressed, this, &WebBrowser::loadPage);
}

void WebBrowser::loadPage()
{
    QString urlText = addressBar->text();
    if (!urlText.startsWith("http://") && !urlText.startsWith("https://")) {
        urlText = "https://" + urlText;
    }
    webView->setUrl(QUrl(urlText));
}
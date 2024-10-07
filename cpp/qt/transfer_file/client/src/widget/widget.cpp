#include "widget.h"
#include "src/client.h"
#include "setting_dialog.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QTextEdit>
#include <QLineEdit>
#include <QLabel>
#include <QFileDialog>
#include <QMessageBox>
#include <QDialog>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    setting_button_(new QPushButton(tr("连接服务器"))),
    file_path_edit_(new QLineEdit()),
    select_file_button_(new QPushButton(tr("选择文件"))),
    send_button_(new QPushButton(tr("发送文件"))),
    client_(new Client(this))
{
    QVBoxLayout *main_vlayout = new QVBoxLayout(this);
    QHBoxLayout *hlayout = new QHBoxLayout();
    main_vlayout->addLayout(hlayout);
    hlayout->addWidget(setting_button_);
    file_path_edit_->setPlaceholderText(tr("文件路径..."));
    hlayout->addWidget(file_path_edit_);
    hlayout->addWidget(select_file_button_);
    hlayout->addWidget(send_button_);

    this->connect(setting_button_, &QPushButton::clicked, this, [this]() {
        setting_dialog_ = new SettingDialog(this);
        setting_dialog_->show();
        this->connect(setting_dialog_, &SettingDialog::sig_setting_success, client_, &Client::slot_connect_host);
    });

    this->connect(select_file_button_, &QPushButton::clicked, this, [this]() {
        QString file_name = QFileDialog::getOpenFileName();
        file_path_edit_->setText(file_name);
    });

    this->connect(send_button_, &QPushButton::clicked, this, [this]() {
        if (file_path_edit_->text().isEmpty()) {
            QMessageBox::warning(this, tr("发送失败"), tr("文件未指定"));
            return;
        }
        emit sig_send_file(file_path_edit_->text());
    });

    this->connect(this, &Widget::sig_send_file, client_, &Client::slot_send_file);
}

Widget::~Widget()
{
}

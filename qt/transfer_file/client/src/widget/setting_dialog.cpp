#include "setting_dialog.h"
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QValidator>
#include <QMessageBox>

SettingDialog::SettingDialog(QWidget *parent) :
    ip_edit_(new QLineEdit()),
    port_edit_(new QLineEdit()),
    ok_button_(new QPushButton(tr("连接"))),
    cancel_button_(new QPushButton(tr("取消")))
{
    QVBoxLayout *main_vlayout = new QVBoxLayout();

    QHBoxLayout *host_hlayout = new QHBoxLayout();
    QRegularExpression ipRegex(R"((\d{1,3}\.){3}\d{1,3})"); // 匹配类似于 x.x.x.x 的IP地址格式
    QRegularExpressionValidator *ipValidator = new QRegularExpressionValidator(ipRegex, this);
    ip_edit_->setValidator(ipValidator);
    // ip_edit_->setInputMask("000.000.000.000;_");
    // ip_edit_->setFixedWidth(150);
    ip_edit_->setPlaceholderText(tr("ip 地址"));
    port_edit_->setValidator(new QIntValidator(1, 65535, this));
    port_edit_->setFixedWidth(60);
    port_edit_->setPlaceholderText(tr("端口"));
    host_hlayout->addWidget(ip_edit_);
    host_hlayout->addWidget(port_edit_);
    // host_hlayout->addStretch(1);

    QHBoxLayout *button_hlayout = new QHBoxLayout();
    button_hlayout->addWidget(ok_button_);
    button_hlayout->addWidget(cancel_button_);

    main_vlayout->addLayout(host_hlayout);
    main_vlayout->addLayout(button_hlayout);
    this->setLayout(main_vlayout);

    this->connect(ip_edit_, &QLineEdit::textChanged, this, [this]() {
        if (ip_edit_->text().isEmpty()) {
            return;
        }
        QString ip_text = ip_edit_->text();
        QStringList segements = ip_text.split('.');
        for (const auto &segement : segements) {
            int value = segement.toInt();
            qDebug() << value;
            if (value < 0 || value > 255) {
                QMessageBox::warning(this, tr("IP 错误"), tr("IP 错误"));
                QString update_text = ip_edit_->text();
                update_text.chop(1);
                ip_edit_->setText(update_text);
                return;
            }
        }
    });

    this->connect(ok_button_, &QPushButton::clicked, this, [this]() {
        // 检查 ip 和 端口 是否完整
        emit sig_setting_success(QHostAddress(ip_edit_->text()), port_edit_->text().toShort());
    });
}

SettingDialog::~SettingDialog()
{
}
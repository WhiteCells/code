#include "register_dialog.h"

RegisterDialog::RegisterDialog(QWidget *parent)
    : QDialog(parent) {

    this->setMinimumSize(300, 500);
    this->setMaximumSize(300, 500);

    title_label_ = new QLabel("注册");
    user_name_label_ = new QLabel("用户");
    user_pass_label_ = new QLabel("密码");
    user_name_edit_ = new QLineEdit();
    user_pass_edit_ = new QLineEdit();
    cancel_btn_ = new QPushButton("取消");
    confirm_btn_ = new QPushButton("确认");

    main_layout_ = new QGridLayout(this);
    main_layout_->addWidget(title_label_, 0, 0);
    main_layout_->addWidget(user_name_label_, 1, 0);
    main_layout_->addWidget(user_name_edit_, 1, 1);
    main_layout_->addWidget(user_pass_label_, 2, 0);
    main_layout_->addWidget(user_pass_edit_, 2, 1);
    main_layout_->addWidget(cancel_btn_, 3, 0);
    main_layout_->addWidget(confirm_btn_, 3, 1);

    this->connect(cancel_btn_, &QPushButton::clicked,
                  this, &RegisterDialog::sig_cancel_btn_clicked);
}

RegisterDialog::~RegisterDialog() {
    qDebug() << "RegisterDialog destruct";
}
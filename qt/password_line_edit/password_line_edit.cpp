#include "password_line_edit.h"
#include "account_label.h"
#include <QApplication>
#include <QStyle>
#include <QLabel>
#include <QWidgetAction>
#include <QPushButton>

PasswordLineEdit::PasswordLineEdit(QWidget *parent) :
    QLineEdit(parent),
    show_pass_action_(new QAction()),
    clear_action_(new QAction()),
    dropdown_action_(new QAction()),
    dropdown_menu_(new QMenu())
{
    connectSigAndSlot();

    dropdown_action_->setIcon(QIcon(":/icon/down"));

    this->addAction(show_pass_action_, QLineEdit::LeadingPosition);
    this->addAction(new QAction(), QLineEdit::LeadingPosition);
    this->addAction(dropdown_action_, QLineEdit::TrailingPosition);
    this->addAction(clear_action_, QLineEdit::TrailingPosition);

    AccountLabel *label1 = new AccountLabel("229292213");
    AccountLabel *label2 = new AccountLabel("129292213");
    AccountLabel *label3 = new AccountLabel("429292213");
    addAccount(label1);
    addAccount(label2);
    addAccount(label3);

    this->setEchoMode(QLineEdit::Password);
    this->setAlignment(Qt::AlignCenter);
    this->setFocusPolicy(Qt::FocusPolicy::ClickFocus);
    this->setContentsMargins(0, 0, 0, 0);
}

PasswordLineEdit::~PasswordLineEdit()
{
}

void PasswordLineEdit::addAccount(AccountLabel *account)
{
    this->connect(account, &AccountLabel::sig_clicked, this, [this](const QString &text) {
        this->setText(text);
    });
    QWidgetAction *widget_action = new QWidgetAction(dropdown_menu_);
    widget_action->setDefaultWidget(account);
    dropdown_menu_->addAction(widget_action);
}

void PasswordLineEdit::focusInEvent(QFocusEvent *event)
{
    QLineEdit::focusInEvent(event);
    switch (this->echoMode()) {
        case QLineEdit::Normal: {
            show_pass_action_->setIcon(QIcon(":/icon/eye_on"));
            break;
        }
        case QLineEdit::Password: {
            show_pass_action_->setIcon(QIcon(":/icon/eye_off"));
            break;
        }
        default:
            break;
    }
    clear_action_->setIcon(QIcon(":/icon/close"));
}

void PasswordLineEdit::focusOutEvent(QFocusEvent *event)
{
    QLineEdit::focusOutEvent(event);
    show_pass_action_->setIcon(QIcon());
    clear_action_->setIcon(QIcon());
}

void PasswordLineEdit::connectSigAndSlot()
{
    this->connect(show_pass_action_, &QAction::triggered, this, [this]() {
        switch (this->echoMode()) {
            case QLineEdit::Password:
                this->setEchoMode(QLineEdit::Normal);
                show_pass_action_->setIcon(QIcon(":/icon/eye_on"));
                break;
            case QLineEdit::Normal:
                this->setEchoMode(QLineEdit::Password);
                show_pass_action_->setIcon(QIcon(":/icon/eye_off"));
            default:
                break;
        }
    });
    this->connect(clear_action_, &QAction::triggered, this, &QLineEdit::clear);
    this->connect(dropdown_action_, &QAction::triggered, this, [this]() {
        if (dropdown_menu_->isVisible()) {
            dropdown_action_->setIcon(QIcon(":/icon/down"));
            dropdown_menu_->hide();
        }
        else {
            dropdown_action_->setIcon(QIcon(":/icon/up"));
            QPoint pos = mapToGlobal(this->rect().bottomLeft());
            dropdown_menu_->setFixedWidth(this->width() + 50);
            dropdown_menu_->move(pos);
            dropdown_menu_->show();
        }
    });
    this->connect(dropdown_menu_, &QMenu::aboutToShow, this, [this]() {
        dropdown_menu_->setIcon(QIcon(":/icon/up"));
    });
    this->connect(dropdown_menu_, &QMenu::aboutToHide, this, [this]() {
        dropdown_action_->setIcon(QIcon(":/icon/down"));
    });
}
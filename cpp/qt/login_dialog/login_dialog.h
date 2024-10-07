#ifndef _LOGIN_DIALOG_H_
#define _LOGIN_DIALOG_H_

#include <QDialog>
#include <QLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

class LoginDialog : public QDialog {
    Q_OBJECT
public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();

signals:
    void sig_register_btn_clicked();

private:
    QLabel *title_label_;
    QLabel *user_name_label_;
    QLabel *user_pass_label_;
    QLineEdit *user_name_edit_;
    QLineEdit *user_pass_edit_;
    QPushButton *cancel_btn_;
    QPushButton *confirm_btn_;
    QPushButton *register_btn_;
    QGridLayout *main_layout_;
};

#endif // _LOGIN_DIALOG_H_
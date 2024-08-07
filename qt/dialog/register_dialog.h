#ifndef _REGISTER_DIALOG_H_
#define _REGISTER_DIALOG_H_

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QLayout>

class RegisterDialog : public QDialog {
    Q_OBJECT
public:
    RegisterDialog(QWidget *parent = nullptr);
    ~RegisterDialog();

signals:
    void sig_cancel_btn_clicked();

private:
    QLabel *title_label_;
    QLabel *user_name_label_;
    QLabel *user_pass_label_;
    QLineEdit *user_name_edit_;
    QLineEdit *user_pass_edit_;
    QPushButton *cancel_btn_;
    QPushButton *confirm_btn_;
    QGridLayout *main_layout_;
};

#endif // _REGISTER_DIALOG_H_
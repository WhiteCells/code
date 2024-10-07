#ifndef _SETTING_DIALOG_H_
#define _SETTING_DIALOG_H_

#include <QDialog>
#include <QHostAddress>

class QLineEdit;
class QPushButton;

class SettingDialog : public QDialog
{
    Q_OBJECT
public:
    explicit SettingDialog(QWidget *parent = nullptr);
    ~SettingDialog();

private:
    QLineEdit *ip_edit_;
    QLineEdit *port_edit_;
    QPushButton *ok_button_;
    QPushButton *cancel_button_;

signals:
    void sig_setting_success(const QHostAddress &host, qint16 port);
};

#endif // _SETTING_DIALOG_H_
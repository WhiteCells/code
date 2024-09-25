#ifndef _WIDGET_H_
#define _WIDGET_H_

#include <QWidget>

class QPushButton;
class QLineEdit;
class QTextEdit;
class QLabel;

class Client;
class SettingDialog;

class Widget : public QWidget
{
    Q_OBJECT
public:
    explicit Widget(QWidget *parent = nullptr);  
    ~Widget();

private:
    QPushButton *setting_button_;
    QLineEdit *file_path_edit_;
    QPushButton *select_file_button_;
    QPushButton *send_button_;
    Client *client_;
    SettingDialog *setting_dialog_;
    
signals:
    void sig_send_file(const QString &file_path);
    void sig_open_file(const QString &file_path);
};

#endif // _WIDGET_H_
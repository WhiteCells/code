#ifndef _MAIN_WINDOW_H_
#define _MAIN_WINDOW_H_

#include "login_dialog.h"
#include "register_dialog.h"
#include <QMainWindow>

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void slot_show_login_dialog();
    void slot_show_register_dialog();

private:
    LoginDialog *login_dialog_;
    RegisterDialog *register_dialog_;
};

#endif // _MAIN_WINDOW_H_
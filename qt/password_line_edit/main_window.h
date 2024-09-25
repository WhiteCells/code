#ifndef _MAIN_WINDOW_H_
#define _MAIN_WINDOW_H_

#include <QMainWindow>

class PasswordLineEdit;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    virtual void mousePressEvent(QMouseEvent *event) override;

private:
    PasswordLineEdit *pass_line_edit_;
};

#endif // _MAIN_WINDOW_H_
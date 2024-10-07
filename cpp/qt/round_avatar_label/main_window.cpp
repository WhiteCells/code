#include "main_window.h"
#include "round_avatar_label.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    RoundAvatarLabel *avatar = new RoundAvatarLabel(this);
    avatar->setDiameter(100);
    avatar->setAvatar(":/icon/avatar");
    avatar->show();
}

MainWindow::~MainWindow()
{
    
}
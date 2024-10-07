#ifndef _MAIN_WINDOW_H_
#define _MAIN_WINDOW_H_

#include <QMainWindow>

class Widget;
class QHBoxLayout;
// 包含 左侧侧边部件
// 中间堆叠部件
// 右侧堆叠部件
// MainSplitter 包含 CentralStackedWidget 和 RightStackedWidget 
class LeftSideWidget;
class CentralStackedWidget;
class RightStackedWidget;

class MainSplitter;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QWidget *main_widget_;
    QHBoxLayout *main_hlayout_;
    LeftSideWidget *left_side_widget_;
    // CentralStackedWidget *central_stacked_widget_;
    // RightStackedWidget *right_stacked_widget_;
    MainSplitter *main_splitter_;
};

#endif // _MAIN_WINDOW_H_
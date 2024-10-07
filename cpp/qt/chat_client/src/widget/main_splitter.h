#ifndef _MAIN_SPLITTER_H_
#define _MAIN_SPLITTER_H_

#include <QSplitter>

// 包含 CentralStackedWidget 和 RightStackedWidget
class CentralStackedWidget;
class RightStackedWidget;

class MainSplitter : public QSplitter
{
public:
    explicit MainSplitter(QWidget *parent = nullptr);
    ~MainSplitter();

private:
    CentralStackedWidget *central_stacked_widget_;
    RightStackedWidget *right_stacked_widget_;
};

#endif // _MAIN_SPLITTER_H_
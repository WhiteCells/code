#ifndef _WIDGET_H_
#define _WIDGET_H_

#include <QWidget>
#include <QSplitter>

class MainSplitter;

class Widget : public QWidget
{
    Q_OBJECT
public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    MainSplitter *main_splitter_;
};

#endif // _WIDGET_H_
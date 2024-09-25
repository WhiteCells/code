#ifndef _EMPTY_PAGE_WIDGET_H_
#define _EMPTY_PAGE_WIDGET_H_

#include <QWidget>

class EmptyPageWidget : public QWidget
{
public:
    explicit EmptyPageWidget(QWidget *parent = nullptr);
    ~EmptyPageWidget();
};

#endif // _EMPTY_PAGE_WIDGET_H_
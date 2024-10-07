#ifndef _CONTROL_SIDE_WIDGET_H_
#define _CONTROL_SIDE_WIDGET_H_

#include <QToolButton>
#include <QSpacerItem>
#include <QVBoxLayout>

class LeftSideWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LeftSideWidget(QWidget *parent = nullptr);
    ~LeftSideWidget();

private:
    QVBoxLayout *main_layout_;
    QToolButton *chat_btn_;
    QToolButton *friend_btn_;
    QToolButton *set_btn_;
};

#endif // _CONTROL_SIDE_WIDGET_H_
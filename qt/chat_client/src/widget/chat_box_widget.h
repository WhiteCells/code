#ifndef _CHAT_BOX_WIDGET_H_
#define _CHAT_BOX_WIDGET_H_

#include <QWidget>

class ChatBoxWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ChatBoxWidget(QWidget *parent = nullptr);
    ~ChatBoxWidget();

private:
    void initUi();
};

#endif // _CHAT_BOX_WIDGET_H_
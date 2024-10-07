#ifndef _RIGHT_STACKED_WIDGET_H_
#define _RIGHT_STACKED_WIDGET_H_

#include <QStackedWidget>

class Widget;
// 包含 ChatSplitter
// EmptyPageWidget
// UserInfoWidget
class ChatSplitter;
class EmptyPageWidget;
class UserInfoWidget;

class RightStackedWidget : public QStackedWidget
{
public:
    explicit RightStackedWidget(QWidget *parent = nullptr);
    ~RightStackedWidget();

private:
    ChatSplitter *chat_splitter_;        // index 0
    UserInfoWidget *user_info_widget_;   // index 1
    EmptyPageWidget *empty_page_widget_; // index 2
};

#endif // _RIGHT_STACKED_WIDGET_H_
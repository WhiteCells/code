#ifndef _RIGHT_SPLITTER_H_
#define _RIGHT_SPLITTER_H_

#include <QSplitter>

// 包含 ChatBoxWidget
// ChatEditWidget
class ChatBoxWidget;
class ChatEditWidget;

// ChatSplitter 被 RightStackedWidget 包含

class ChatSplitter : public QSplitter
{
public:
    explicit ChatSplitter(QWidget *parent = nullptr);
    ~ChatSplitter();

private:
    ChatBoxWidget *chat_box_widget_;
    ChatEditWidget *chat_edit_widget_;
};

#endif // _RIGHT_SPLITTER_H_
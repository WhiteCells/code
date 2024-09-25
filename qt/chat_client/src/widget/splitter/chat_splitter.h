#ifndef _CHAT_SPLITTER_H_
#define _CHAT_SPLITTER_H_

#include <QSplitter>
#include <QWidget>

class ChatSplitter : public QSplitter
{
    Q_OBJECT
public:
    explicit ChatSplitter(QWidget *parent = nullptr);
    ~ChatSplitter();

private:
    // ChatBoxWidget *chat_box_widget_;
    // ChatEditWidget *chat_edit_widget_;
    QWidget *widget1_;
    QWidget *widget2_;
};

#endif // _CHAT_SPLITTER_H_
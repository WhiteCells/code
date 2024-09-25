#ifndef _SPLITTER_H_
#define _SPLITTER_H_

#include <QSplitter>

class ChatSplitter;
class QWidget;

class MainSplitter : public QSplitter
{
    Q_OBJECT
public:
    explicit MainSplitter(QWidget *parent = nullptr);
    ~MainSplitter();

private:
    QWidget *list_widget_;
    ChatSplitter *chat_splitter_;
};

#endif // _SPLITTER_H_
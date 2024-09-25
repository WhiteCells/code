#ifndef _SEARCH_LINE_EDIT_H_
#define _SEARCH_LINE_EDIT_H_

#include <QLineEdit>

class QAction;

class SearchLineEdit : public QLineEdit
{
public:
    explicit SearchLineEdit(QWidget *parent = nullptr);
    ~SearchLineEdit();

private:
    QAction *search_action_;
    QAction *clear_action_;
};

#endif // _SEARCH_LINE_EDIT_H_
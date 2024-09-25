#ifndef _PASSWORD_LINE_EDIT_H_
#define _PASSWORD_LINE_EDIT_H_

#include <QLineEdit>
#include <QAction>
#include <QMenu>

class AccountLabel;

class FocusEventFilter : QObject
{
    Q_OBJECT
public:
    FocusEventFilter(QLineEdit *line_edit);

private:
};

class PasswordLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit PasswordLineEdit(QWidget *parent = nullptr);
    ~PasswordLineEdit();

    void addAccount(AccountLabel *account);

protected:
    virtual void focusInEvent(QFocusEvent *event) override;
    virtual void focusOutEvent(QFocusEvent *event) override;

private:
    void connectSigAndSlot();

    QAction *show_pass_action_;
    QAction *clear_action_;
    QAction *dropdown_action_;
    QMenu *dropdown_menu_;
};

#endif // _PASSWORD_LINE_EDIT_H_
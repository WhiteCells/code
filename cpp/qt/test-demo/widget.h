#ifndef _WIDGET_H_
#define _WIDGET_H_

#include <QWidget>

class QWebEngineView;
class QLineEdit;

class WebBrowser : public QWidget
{
    Q_OBJECT

public:
    WebBrowser(QWidget *parent = nullptr);

private slots:
    void loadPage();

private:
    QWebEngineView *webView;
    QLineEdit *addressBar;
};

#endif // _WIDGET_H_
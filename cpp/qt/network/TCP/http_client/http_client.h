#ifndef _HTTP_CLIENT_H_
#define _HTTP_CLIENT_H_

#include <QWidget>

class QNetworkAccessManager;
class QLineEdit;
class QPushButton;
class QTextEdit;

class HttpClient : public QWidget {
    Q_OBJECT
public:
    explicit HttpClient(QWidget *parent = nullptr);
    ~HttpClient();

private:
    QNetworkAccessManager *manager_;
    QLineEdit *url_line_edit_;
    QPushButton *post_btn_;
    QPushButton *get_btn_;
    QTextEdit *log_text_edit_;

private:
    void slot_post_request();
    void slot_get_request();
};

#endif // _HTTP_CLIENT_H_
#include <QApplication>
#include <QDialog>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QDebug>

class ModernInputDialog : public QDialog {
public:
    ModernInputDialog(QWidget *parent = nullptr) : QDialog(parent) {
        setWindowTitle("Modern Input Box");

        // 创建布局
        QVBoxLayout *layout = new QVBoxLayout(this);

        // 添加说明文本
        QLabel *label = new QLabel("Please enter your text:", this);
        layout->addWidget(label);

        // 添加输入框
        QLineEdit *lineEdit = new QLineEdit(this);
        layout->addWidget(lineEdit);

        // 添加按钮布局
        QHBoxLayout *buttonLayout = new QHBoxLayout();

        QPushButton *okButton = new QPushButton("OK", this);
        QPushButton *cancelButton = new QPushButton("Cancel", this);

        buttonLayout->addWidget(okButton);
        buttonLayout->addWidget(cancelButton);

        layout->addLayout(buttonLayout);

        // 连接按钮信号到槽
        connect(okButton, &QPushButton::clicked, [=]() {
            QString text = lineEdit->text();
            qDebug() << "User entered:" << text;
            accept(); // 关闭对话框并返回 QDialog::Accepted
        });

        connect(cancelButton, &QPushButton::clicked, [=]() {
            reject(); // 关闭对话框并返回 QDialog::Rejected
        });

        // 设置自定义样式
        setStyleSheet(
            "QDialog {"
            "background-color: #f0f0f0;"
            "border-radius: 10px;"
            "padding: 15px;"
            "font-family: 'Segoe UI';"
            "font-size: 14px;"
            "}"
            "QPushButton {"
            "background-color: #0078D7;"
            "color: white;"
            "border: none;"
            "border-radius: 5px;"
            "padding: 8px 16px;"
            "}"
            "QPushButton:hover {"
            "background-color: #005a9e;"
            "}"
            "QLineEdit {"
            "border: 1px solid #ccc;"
            "border-radius: 4px;"
            "padding: 6px;"
            "font-size: 14px;"
            "}"
        );

        setLayout(layout);
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // 创建并显示自定义的现代化输入框对话框
    ModernInputDialog dialog;
    if (dialog.exec() == QDialog::Accepted) {
        qDebug() << "User clicked OK!";
    } else {
        qDebug() << "User clicked Cancel!";
    }

    return app.exec();
}
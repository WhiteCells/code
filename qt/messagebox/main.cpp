#include <QApplication>
#include <QMessageBox>
#include <QIcon>
#include <QStyle>
#include <QDebug>

void showModernMessageBox() {
    // 创建消息框
    QMessageBox msgBox;

    // 设置窗口标题
    msgBox.setWindowTitle("Modern Output Box");

    // 设置文本内容
    msgBox.setText("This is a modern styled output box.");

    // 设置详细信息
    msgBox.setInformativeText("Would you like to proceed with the operation?");

    // 自定义图标 (可以加载自己的图标)
    msgBox.setIconPixmap(QPixmap(":/icons/modern_icon.png"));

    // 添加按钮
    QPushButton *acceptButton = msgBox.addButton("Accept", QMessageBox::AcceptRole);
    QPushButton *cancelButton = msgBox.addButton("Cancel", QMessageBox::RejectRole);

    // 自定义样式
    msgBox.setStyleSheet(
        "QMessageBox {"
        "background-color: #f0f0f0;"
        "border-radius: 8px;"
        "font-family: 'Segoe UI';"
        "font-size: 14px;"
        "padding: 20px;"
        "}"
        "QPushButton {"
        "background-color: #0078D7;"
        "color: white;"
        "border: none;"
        "border-radius: 4px;"
        "padding: 8px 16px;"
        "}"
        "QPushButton:hover {"
        "background-color: #005a9e;"
        "}");

    // 显示对话框并等待用户选择
    msgBox.exec();

    if (msgBox.clickedButton() == (QAbstractButton *)acceptButton) {
        // 处理 "Accept" 选项
        qDebug("User accepted the operation.");
    } else if (msgBox.clickedButton() == (QAbstractButton *)cancelButton) {
        // 处理 "Cancel" 选项
        qDebug("User canceled the operation.");
    }
}

// int main(int argc, char *argv[]) {
//     QApplication app(argc, argv);

//     // 调用显示现代化消息框的函数
//     showModernMessageBox();

//     return app.exec();
// }

#include "dynamic_line_edit.h"

DynamicLineEdit::DynamicLineEdit(QWidget *parent) :
    QFrame(parent),
    TipsLabel{new QLabel(this)},
    edit{new QLineEdit(this)},
    Edit_Animation{new QPropertyAnimation(this)},
    TipsLabel_Animation{new QPropertyAnimation(this)} {
    setPosParameters();
    edit->setFocusPolicy(Qt::ClickFocus);                     // 设置焦点策略为点击获取
    setTipsText("Please enter text");                         // 默认的提示文字
    TipsLabel->setAlignment(Qt::AlignLeft | Qt::AlignBottom); // 设置提示文字左下对齐
}

void DynamicLineEdit::setEditExpansionHeight(int edit_expansion_height) {
    Edit_Expansion_H = edit_expansion_height;
    setPosParameters();       // 更新坐标位置等参数
    setAnimationProperties(); // 更新动画属性
}

void DynamicLineEdit::setTipsText(const QString &text) {
    TipsLabel->setText(text);
}

void DynamicLineEdit::setEditFontColor(const QColor &fontColor) {
    QPalette fontcolor{edit->palette()};
    fontcolor.setColor(QPalette::Text, fontColor);
    edit->setPalette(fontcolor);
}

void DynamicLineEdit::setEditFont(const QFont &font, const QColor &fontcolor) {
    edit->setFont(font);
    setEditFontColor(fontcolor);
}

void DynamicLineEdit::setTipsFontColor(const QColor &fontColor) {
    QPalette fontcolor = TipsLabel->palette();
    fontcolor.setColor(QPalette::WindowText, fontColor);
    TipsLabel->setPalette(fontcolor);
}

void DynamicLineEdit::setTipsFont(const QFont &font, const QColor &fontcolor) {
    TipsLabel->setFont(font);
    setTipsFontColor(fontcolor);
}

void DynamicLineEdit::setEditBackgroundColor(const QColor &bk_color) {
    setStyleSheet("QLineEdit{background-color:" + bk_color.name() + ";}");
}

void DynamicLineEdit::setBorderRadius(const int border_radius) {
    setStyleSheet(QString("QLineEdit{border-radius:%1px;}").arg(QString::number(border_radius)));
}

void DynamicLineEdit::setBorderColor(QColor border_color, int border_thickness) {
    setStyleSheet(QString("QLineEdit{border:%1px solid %2;}").arg(QString::number(border_thickness), border_color.name()));
}

void DynamicLineEdit::setStyleSheet(const QString &stylesheet) {
    QFrame::setStyleSheet(styleSheet() + stylesheet);
}

void DynamicLineEdit::setUpspringTime(int time) {
    Edit_Animation->setDuration(time);
    TipsLabel_Animation->setDuration(time);
}

QString DynamicLineEdit::text() {
    return edit->text();
}

bool DynamicLineEdit::hasFocus() {
    return edit->hasFocus();
}

void DynamicLineEdit::setPosParameters() {
    Edit_Initial_y = height() - Edit_Initial_H;
    Edit_Expansion_y = height() - Edit_Expansion_H;
    TipsLabel_H = height() - Edit_Expansion_H;
    TipsLabel_Initial_y = Edit_Expansion_H - Edit_Initial_H;
    edit->setGeometry(0, Edit_Initial_y, width(), Edit_Expansion_H);
    TipsLabel->setGeometry(10, TipsLabel_Initial_y, width(), TipsLabel_H);
}

void DynamicLineEdit::setAnimationProperties() {
    Edit_Animation->setTargetObject(edit);                                                             // 设置作用对象
    Edit_Animation->setPropertyName("geometry");                                                       // 设置属性名称为geometry(位置和尺寸)
    Edit_Animation->setDuration(200);                                                                  // 设置过渡时间100ms
    Edit_Animation->setStartValue(QRect(QPoint(0, Edit_Initial_y), QSize(width(), Edit_Initial_H)));   // 设置起始值
    Edit_Animation->setEndValue(QRect(QPoint(0, Edit_Expansion_y), QSize(width(), Edit_Expansion_H))); // 设置结束值
    TipsLabel_Animation->setTargetObject(TipsLabel);
    TipsLabel_Animation->setPropertyName("pos");
    TipsLabel_Animation->setDuration(200);
    TipsLabel_Animation->setStartValue(QPoint(TipsLabel_Initial_x, TipsLabel_Initial_y));
    TipsLabel_Animation->setEndValue(QPoint(0, 0));
}

void DynamicLineEdit::mousePressEvent(QMouseEvent *event) {
    QFrame::mousePressEvent(event);
    if (!edit->hasFocus()) {
        edit->setFocus();                                          // 设置焦点
        Edit_Animation->setDirection(QAbstractAnimation::Forward); // 设置动画正向
        TipsLabel_Animation->setDirection(QAbstractAnimation::Forward);
        Edit_Animation->start();
        TipsLabel_Animation->start();
    }
}

void DynamicLineEdit::leaveEvent(QEvent *event) {
    QFrame::leaveEvent(event);
    if (edit->hasFocus() && edit->text() == "") {
        edit->clearFocus();                                         // 清除焦点
        Edit_Animation->setDirection(QAbstractAnimation::Backward); // 设置动画逆向
        TipsLabel_Animation->setDirection(QAbstractAnimation::Backward);
        Edit_Animation->start();
        TipsLabel_Animation->start();
    }
}

void DynamicLineEdit::resizeEvent(QResizeEvent *event) {
    QFrame::resizeEvent(event);
    setPosParameters();       // 更新坐标位置等参数
    setAnimationProperties(); // 更新动画属性
}

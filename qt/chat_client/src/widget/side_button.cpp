#include "side_button.h"
#include <QEvent>
#include <QMouseEvent>
#include <QEnterEvent>
#include <QKeyEvent>

SideButton::SideButton(int index, int width, int height, QWidget *parent) :
    index_(index),
    width_(width),
    height_(height),
    normal_color_(qRgb(0, 0, 0)),
    hover_color_(qRgb(0, 0, 0)),
    color_brush_(normal_color_),
    QToolButton(parent)
{
    this->setFixedSize(width_, height_);
    this->connect(this, &QToolButton::clicked, this, [this]() {
        emit sig_clicked_index(index_);
    });
}

SideButton::~SideButton()
{
}

void SideButton::setIndex(const int index)
{
    index_ = index;
}

void SideButton::setWidth(const int width)
{
    width_ = width;
}

void SideButton::setHeight(const int height)
{
    height_ = height;
}

void SideButton::setNormalIcon(const QIcon &icon)
{
    if (icon.isNull()) {
        qDebug() << "icon is null";
        return;
    }
    normal_icon_ = icon;
    this->setIcon(icon);
}

void SideButton::setHoverIcon(const QIcon &icon)
{
    if (icon.isNull()) {
        qDebug() << "icon is null";
        return;
    }
    hover_icon_ = icon;
}

void SideButton::setClickedIcon(const QIcon &icon)
{
    if (icon.isNull()) {
        qDebug() << "icon is null";
        return;
    }
    clicked_icon_ = icon;
}

void SideButton::setNormalColor(const QColor &color)
{
    normal_color_ = color;
}

void SideButton::setHoverColor(const QColor &color)
{
    hover_color_ = color;
}

void SideButton::setClickedColor(const QColor &color)
{
    clicked_color_ = color;
}

void SideButton::enterEvent(QEnterEvent *event)
{
    QToolButton::enterEvent(event);
    color_brush_.setColor(hover_color_);
    this->setIcon(QIcon(hover_icon_));
}

void SideButton::leaveEvent(QEvent *event)
{
    QToolButton::leaveEvent(event);
    color_brush_.setColor(normal_color_);
    this->setIcon(QIcon(normal_icon_));
}

void SideButton::keyPressEvent(QKeyEvent *event)
{
    QToolButton::keyPressEvent(event);
}

void SideButton::keyReleaseEvent(QKeyEvent *event)
{
    QToolButton::keyReleaseEvent(event);
    color_brush_.setColor(hover_color_);
    this->setHoverIcon(QIcon(hover_icon_));
}

void SideButton::mousePressEvent(QMouseEvent *event)
{
    QToolButton::mousePressEvent(event);
    color_brush_.setColor(clicked_color_);
    this->setHoverIcon(QIcon(clicked_icon_));
}

void SideButton::mouseReleaseEvent(QMouseEvent *event)
{
    QToolButton::mouseReleaseEvent(event);
    color_brush_.setColor(hover_color_);
    this->setHoverIcon(QIcon(hover_icon_));
}
#include "round_avatar_label.h"
#include <QPixmap>
#include <QPainter>
#include <QPainterPath>

RoundAvatarLabel::RoundAvatarLabel(QWidget *parent) :
    QLabel(parent),
    diameter_(10)
{
}

RoundAvatarLabel::~RoundAvatarLabel()
{
}

void RoundAvatarLabel::setDiameter(int diameter)
{
    this->setFixedWidth(diameter);
    this->setFixedHeight(diameter);
    diameter_ = diameter;
}

void RoundAvatarLabel::setAvatar(QString avatar_path)
{
    QPixmap avatar_pixmap(avatar_path);
    if (avatar_pixmap.isNull()) {
        qWarning() << "failed to load image from " << avatar_path;
        return;
    }
    QPixmap res_pixmap(diameter_, diameter_);
    res_pixmap.fill(Qt::transparent);
    QPainter painter(&res_pixmap);
    painter.setRenderHint(QPainter::Antialiasing);
    QPainterPath path;
    path.addEllipse(0, 0, diameter_, diameter_);
    painter.setClipPath(path);
    painter.drawPixmap(0, 0, diameter_, diameter_, avatar_pixmap);
    this->setPixmap(res_pixmap);
}
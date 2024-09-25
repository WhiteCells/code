#ifndef _ROUND_AVATAR_LABEL_H_
#define _ROUND_AVATAR_LABEL_H_

#include <QLabel>

class RoundAvatarLabel : public QLabel
{
    Q_OBJECT
public:
    explicit RoundAvatarLabel(QWidget *parent = nullptr);
    ~RoundAvatarLabel();

    void setDiameter(int diameter);
    void setAvatar(QString avatar_path);

private:
    int diameter_;
};

#endif // _ROUND_AVATAR_LABEL_H_
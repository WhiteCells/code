#ifndef _SIDE_BUTTON_H_
#define _SIDE_BUTTON_H_

#include <QToolButton>

class QEvent;
class QEnterEvent;
class QMouseEvent;
class QKeyEvent;

class SideButton : public QToolButton
{
    Q_OBJECT
public:
    explicit SideButton(int index, int width, int height, QWidget *parent = nullptr);
    ~SideButton();

    void setIndex(const int index);
    void setWidth(const int width);
    void setHeight(const int height);
    void setNormalIcon(const QIcon &icon);
    void setHoverIcon(const QIcon &icon);
    void setClickedIcon(const QIcon &icon);
    void setNormalColor(const QColor &color);
    void setHoverColor(const QColor &color);
    void setClickedColor(const QColor &color);

protected:
    virtual void enterEvent(QEnterEvent *event) override;
    virtual void leaveEvent(QEvent *event) override;
    virtual void keyPressEvent(QKeyEvent *event) override;
    virtual void keyReleaseEvent(QKeyEvent *event) override;
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;

private:
    int index_;            // StackWidget setCurrentIndex(index)
    int width_;            // button width
    int height_;           // button height
    QIcon normal_icon_;    // button normal icon
    QIcon hover_icon_;     // button hover icon
    QIcon clicked_icon_;   // button clicked icon
    QColor normal_color_;  // button normal background color
    QColor hover_color_;   // button hover background color
    QColor clicked_color_; // button clicked background color
    QBrush color_brush_;   // button background color brush

signals:
    void sig_clicked_index(int index);
};

#endif // _SIDE_BUTTON_H_
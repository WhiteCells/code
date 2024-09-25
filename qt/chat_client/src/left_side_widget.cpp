#include "left_side_widget.h"
#include "widget/side_button.h"

LeftSideWidget::LeftSideWidget(QWidget *parent) :
    main_layout_(new QVBoxLayout(this)),
    chat_btn_(new QToolButton()),
    friend_btn_(new QToolButton()),
    set_btn_(new QToolButton())
{
    SideButton *chat_btn = new SideButton(0, 40, 40);
    chat_btn->setNormalIcon(QIcon(":/icon/chat_btn_icon"));
    chat_btn->setHoverIcon(QIcon(":/icon/chat_btn_icon_hover"));
    chat_btn->setClickedIcon(QIcon(":/icon/chat_btn_icon_hover"));

    main_layout_->addWidget(chat_btn);
    main_layout_->addWidget(friend_btn_);
    main_layout_->addSpacerItem(new QSpacerItem(20, 20, QSizePolicy::Expanding));
    main_layout_->addWidget(set_btn_);
    main_layout_->setContentsMargins(0, 0, 0, 0);
}

LeftSideWidget::~LeftSideWidget()
{
}
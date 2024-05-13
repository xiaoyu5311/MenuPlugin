#include "StoreUserWidget.h"

StoreUserWidget::StoreUserWidget()
{
    sell_user_widget_ = new SellUserWidget();
    sell_btn_callback_ = std::bind(&SellUserWidget::CreateUserWidget, sell_user_widget_, std::placeholders::_1);
    buy_user_widget_ = new BuyUserWidget();
    buy_btn_callback_ = std::bind(&BuyUserWidget::CreateUserWidget, buy_user_widget_,
                                  std::placeholders::_1);
}

StoreUserWidget::~StoreUserWidget()
{
    if (sell_user_widget_)
    {
        delete sell_user_widget_;
        sell_user_widget_ = nullptr;
    }

    if (buy_user_widget_)
    {
        delete buy_user_widget_;
        buy_user_widget_ = nullptr;
    }
}

void StoreUserWidget::CreateUserWidget(Player& player)
{
    simple_form = new SimpleForm();
    simple_form->appendButton("我要买东西", buy_btn_callback_);
    simple_form->appendButton("我要卖东西", sell_btn_callback_);
    simple_form->sendTo(player);
}

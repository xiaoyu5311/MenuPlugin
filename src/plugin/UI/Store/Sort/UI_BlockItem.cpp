#include "UI_BlockItem.h"

#include <plugin/Log/Log.h>

void UI_BlockItem::CreateUserWidget(Player& player)
{
    simple_form = new SimpleForm();
    simple_form->appendButton("圆石", buy_detail_callback_);
    simple_form->appendButton("沙子");
    simple_form->appendButton("橡木");
    simple_form->sendTo(player);
}

UI_BlockItem::UI_BlockItem()
{
    buy_detail_ = new UI_BuyDetail();
    buy_detail_callback_ = std::bind(&UI_BuyDetail::CreateUserWidget, buy_detail_, std::placeholders::_1);
}

UI_BlockItem::~UI_BlockItem()
{
    if (buy_detail_)
    {
        delete buy_detail_;
        buy_detail_ = nullptr;
    }
}

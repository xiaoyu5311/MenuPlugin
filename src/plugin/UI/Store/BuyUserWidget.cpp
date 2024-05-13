#include "BuyUserWidget.h"

BuyUserWidget::BuyUserWidget()
{
    food_item_ = new UI_FoodItem();
    cate_food_button_callback_ = std::bind(&UI_FoodItem::CreateUserWidget, food_item_, std::placeholders::_1);
    block_item_ = new UI_BlockItem();
    cate_block_button_callback_ = std::bind(&UI_BlockItem::CreateUserWidget, block_item_, std::placeholders::_1);
}

BuyUserWidget::~BuyUserWidget()
{
    if (food_item_)
    {
        delete food_item_;
        food_item_ = nullptr;
    }
    if (block_item_)
    {
        delete block_item_;
        block_item_ = nullptr;
    }
}

void BuyUserWidget::CreateUserWidget(Player& player )
{
    simple_form = new SimpleForm();
    simple_form->appendButton("方块", cate_block_button_callback_);
    simple_form->appendButton("食物", cate_food_button_callback_);
    simple_form->sendTo(player);
}

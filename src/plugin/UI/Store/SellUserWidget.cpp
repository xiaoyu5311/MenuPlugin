#include "SellUserWidget.h"


SellUserWidget::SellUserWidget()
{
    block_item = new UI_BlockItem();
    food_item = new UI_FoodItem();

    block_btn_callback = std::bind(&UI_BlockItem::CreateUserWidget, block_item, std::placeholders::_1);
    food_btn_callback = std::bind(&UI_FoodItem::CreateUserWidget, food_item, std::placeholders::_1);
}

SellUserWidget::~SellUserWidget()
{
    if (block_item)
    {
        delete block_item;
        block_item = nullptr;
    }
    if (food_item)
    {
        delete food_item;
        food_item = nullptr;
    }
}

void SellUserWidget::CreateUserWidget(Player& player )
{
    simple_form = new SimpleForm("买");
    simple_form->appendButton("方块", block_btn_callback);
    simple_form->appendButton("食物", food_btn_callback);
    simple_form->sendTo(player);
}

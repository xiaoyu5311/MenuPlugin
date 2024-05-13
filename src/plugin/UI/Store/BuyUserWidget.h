#pragma once
#include "plugin/UI/Core/UserWidgetBase.h"
#include "plugin/UI/Core/UserWiget.h"
#include "Sort/UI_BlockItem.h"
#include "Sort/UI_FoodItem.h"

class BuyUserWidget : public UserWidgetBase
{
public:
    BuyUserWidget();
    ~BuyUserWidget() override;

private:
    UI_FoodItem* food_item_;
    ButtonCallback cate_food_button_callback_;
    UI_BlockItem* block_item_;
    ButtonCallback cate_block_button_callback_;

public:
    void CreateUserWidget(Player& player) override;
};

#pragma once
#include "plugin/UI/Core/UserWidgetBase.h"
#include "plugin/UI/Core/UserWiget.h"
#include "Sort/UI_BlockItem.h"
#include "Sort/UI_FoodItem.h"

class SellUserWidget : public UserWidgetBase
{
public:
    SellUserWidget();
    ~ SellUserWidget() override;

private:
    UI_BlockItem* block_item;
    UI_FoodItem* food_item;
    ButtonCallback block_btn_callback;
    ButtonCallback food_btn_callback;

public:
    void CreateUserWidget(Player& player) override;
};

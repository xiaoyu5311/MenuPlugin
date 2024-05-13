#include "UI_FoodItem.h"

void UI_FoodItem::CreateUserWidget(Player& player)
{
    simple_form = new SimpleForm();
    simple_form->appendButton("面包");
    simple_form->appendButton("胡萝卜");
    simple_form->appendButton("烤肉");
    simple_form->sendTo(player);
}

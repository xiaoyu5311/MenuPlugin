#include "TeleportUserWidget.h"

void TeleportUserWidget::CreateUserWidget(Player& player)
{
    simple_form = new SimpleForm();
    simple_form->appendButton("我要传送");
    simple_form->sendTo(player);
}

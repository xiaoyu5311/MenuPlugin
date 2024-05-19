#include "TeleportUserWidget.h"

void TeleportUserWidget::CreateUserWidget(Player& player)
{
    m_simple_form = new SimpleForm();
    m_simple_form->appendButton("我要传送");
    m_simple_form->sendTo(player);
}

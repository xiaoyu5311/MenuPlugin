#include "MainUserWidget.h"
#include "ll/api/form/SimpleForm.h"
using ll::form::SimpleForm;

MainUserWidget::MainUserWidget()
{
    store_user_widget = new StoreUserWidget();
    store_btn_callback_ = std::bind(&StoreUserWidget::CreateUserWidget, store_user_widget,
                                    std::placeholders::_1);
    teleport_user_widget_ = new TeleportUserWidget();
    teleport_btn_callback_ = std::bind(&TeleportUserWidget::CreateUserWidget, teleport_user_widget_,
                                       std::placeholders::_1);
}

MainUserWidget::~MainUserWidget()
{
    if (store_user_widget)
    {
        delete store_user_widget;
        store_user_widget = nullptr;
    }
}

void MainUserWidget::CreateUserWidget(Player& player)
{
    simple_form = new SimpleForm("菜单");
    simple_form->appendButton("商店", store_btn_callback_);
    simple_form->appendButton("传送", teleport_btn_callback_);

    simple_form->sendTo(player);
}

#pragma once
#include <mc/world/actor/player/Player.h>

#include "Core/UserWiget.h"
#include "Store/StoreUserWidget.h"
#include "Teleport/TeleportUserWidget.h"

class MainUserWidget : public UserWidgetBase
{
public:
    MainUserWidget();
    ~MainUserWidget() override;

private:
    StoreUserWidget* store_user_widget;
    TeleportUserWidget* teleport_user_widget_;
    ButtonCallback store_btn_callback_;
    ButtonCallback teleport_btn_callback_;

public:
    void CreateUserWidget(Player& player) override;
};

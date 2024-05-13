#pragma once
#include "plugin/UI/Core/UserWidgetBase.h"
#include "plugin/UI/Core/UserWiget.h"

class TeleportUserWidget : public UserWidgetBase
{
public:
    void CreateUserWidget(Player& player) override;
};

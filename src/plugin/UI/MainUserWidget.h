#pragma once
#include <mc/world/actor/player/Player.h>

#include "Core/UserWiget.h"
#include "plugin/Constant/NavTitle.h"
#include "Teleport/TeleportUserWidget.h"


class MainUserWidget : public UserWidgetBase
{
public:
    MainUserWidget(const string& path = URL::MAIN_MENU)
        : path(path)
    {
    }

    ~MainUserWidget() override;

private:
    string path;

public:
    void CreateUserWidget(Player& player) override;
};

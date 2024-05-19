#pragma once
#include <mc/world/actor/player/Player.h>

#include "Core/UserWiget.h"
#include "Teleport/TeleportUserWidget.h"


class MainUserWidget : public UserWidgetBase
{
public:
    MainUserWidget(const string& path = "/menu/catelist")
        : path(path)
    {
    }

    ~MainUserWidget() override;

private:
    string path;

public:
    void CreateUserWidget(Player& player) override;
};

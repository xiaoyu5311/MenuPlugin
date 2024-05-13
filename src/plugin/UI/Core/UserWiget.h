#pragma once
#include <mc/world/actor/player/Player.h>


class UserWiget
{
public:
    virtual ~UserWiget() = default;
    virtual void CreateUserWidget(Player& player) =0;
};

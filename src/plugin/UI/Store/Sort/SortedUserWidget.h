#pragma once
#include "plugin/UI/Core/UserWidgetBase.h"

class SortedUserWidget:public  UserWidgetBase
{
public:
    void CreateUserWidget(Player& player) override =0;

};

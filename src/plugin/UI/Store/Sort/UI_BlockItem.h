#pragma once
#include "SortedUserWidget.h"
#include "plugin/UI/Store/UI_BuyDetail.h"

class UI_BlockItem : public SortedUserWidget
{
public:
    UI_BlockItem();
    ~ UI_BlockItem() override;
    void CreateUserWidget(Player& player) override;

private:
    UI_BuyDetail* buy_detail_;
    ButtonCallback buy_detail_callback_;
};

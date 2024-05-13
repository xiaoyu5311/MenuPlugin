#pragma once
#include "BuyUserWidget.h"
#include "SellUserWidget.h"
#include "plugin/UI/Core/UserWidgetBase.h"
#include "plugin/UI/Core/UserWiget.h"

class StoreUserWidget : public UserWidgetBase
{
public:
    StoreUserWidget();
    ~StoreUserWidget() override;

private:
    SellUserWidget* sell_user_widget_;
    BuyUserWidget* buy_user_widget_;

    ButtonCallback sell_btn_callback_;
    ButtonCallback buy_btn_callback_;

public:
    void CreateUserWidget(Player& player) override;
};

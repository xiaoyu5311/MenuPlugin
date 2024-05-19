#pragma once
#include <string>
#include <plugin/Log/Log.h>
#include <plugin/UI/MainUserWidget.h>
#include <plugin/UI/Core/UserWidgetBase.h>

class UI_MenuItem : public UserWidgetBase
{
private:
    MenuItem m_menu_item;

public:
    UI_MenuItem(json json)
    {
        m_menu_item = MenuItem(json);
        Log::Info("构造出 m_menu_item" + m_menu_item.toString());
    }

    void CreateUserWidget(Player& player) override;

    void create_goods_form(Player& player);

    bool execute_givecommand(Player& player, string object_id, int amount);
};

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
    }

    void create_recycle_goods_form(Player& player);
    void CreateUserWidget(Player& player) override;

    void create_goods_form(Player& player);

    bool execute_givecommand(Player& player, string object_id, int amount);
    bool execute_reduce_command(const Player& player, const string& string, int amount);
    //查询你的背包够不够这个数量
    bool query_objects_amount(const Player& player, const string& object_id, int amount);
};

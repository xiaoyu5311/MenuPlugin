#include "MainUserWidget.h"

#include <nlohmann/json.hpp>
using nlohmann::json;

#include "Store/UI_MenuItem.h"
using ll::form::SimpleForm;


MainUserWidget::~MainUserWidget()
{
}


void MainUserWidget::CreateUserWidget(Player& player)
{
    m_simple_form = new SimpleForm("菜单");
    string res = HttpService_::get_request(path);
    json data = JsonHelper::get_data(res);

    if (data.is_array())
    {
        for (const json& itemJson : data)
        {
            string btnName = itemJson.at("name");
            m_simple_form->appendButton(btnName, [=](Player& player_)
            {
                UI_MenuItem ui_menu_item(itemJson);//局部变量能否被成员变量引用？
                ui_menu_item.CreateUserWidget(player_);
            });
        }
    }
    //说明返回是一个
    else
    {
        string btnName = data.at("name");
        m_simple_form->appendButton(btnName, [=](Player& player_)
        {
            UI_MenuItem ui_menu_item(data);
            ui_menu_item.CreateUserWidget(player_);
        });
    }
    m_simple_form->sendTo(player);
}

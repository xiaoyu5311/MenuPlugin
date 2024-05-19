#pragma once
#include <ll/api/form/SimpleForm.h>
#include <ll/api/form/CustomForm.h>
#include <plugin/HTTP/HttpService.h>

#include "ll/api/form/SimpleForm.h"
#include "plugin/Utils/JsonHelper.h"


#include "UserWiget.h"
using ll::form::SimpleForm;
using ll::form::CustomForm;

typedef std::function<void(Player&)> ButtonCallback;


struct MenuItem
{
    int menuId;
    string name;
    int parent;
    string formType;
    int depth;

    MenuItem(const json& json)
    {
        json.at("menuId").get_to(menuId);
        json.at("name").get_to(name);
        json.at("parent").get_to(parent);
        json.at("formType").get_to(formType);
        json.at("depth").get_to(depth);
    }

    MenuItem()
    {
    }

    string toString()
    {
        json j;
        j["menuId"] = menuId;
        j["name"] = name;
        j["parent"] = parent;
        j["formType"] = formType;
        j["depth"] = depth;
        return j.dump(4);
    }
};

struct SellGoodsDetail
{
    int goodsId;
    string goodsName;
    double goodsPrice;
    double originalPrice;
    string objectId;

    SellGoodsDetail(const json& json)
    {
        json.at("goodsId").get_to(goodsId);
        json.at("goodsName").get_to(goodsName);
        json.at("goodsPrice").get_to(goodsPrice);
        json.at("originalPrice").get_to(originalPrice);
        json.at("objectId").get_to(objectId);
    }
};

struct SellGoods
{
    string uuid; //购买者ID
    int goodsId;
    int amount; //购买的数量

    SellGoods(const json& json)
    {
        json.at("uuid").get_to(uuid);
        json.at("goodsId").get_to(goodsId);
        json.at("amount").get_to(amount);
    }

    SellGoods(const string& uuid, int goods_id, int amount)
        : uuid(uuid),
          goodsId(goods_id),
          amount(amount)
    {
    }

    string toJson()
    {
        json sellGoods;
        sellGoods["uuid"] = uuid;
        sellGoods["goodsId"] = goodsId;
        sellGoods["amount"] = amount;
        string sell_data = sellGoods.dump();
        return sell_data;
    }
};

class UserWidgetBase : public UserWiget
{
protected:
    SimpleForm* m_simple_form;
    CustomForm* m_custom_form;

public:
    UserWidgetBase();
    ~UserWidgetBase() override;


    void CreateUserWidget(Player& player) override =0;
};

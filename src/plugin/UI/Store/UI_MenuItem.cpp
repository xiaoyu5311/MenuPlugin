#include "UI_MenuItem.h"

#include <regex>
#include <mc/server/commands/CommandContext.h>
#include <mc/server/commands/PlayerCommandOrigin.h>
#include <mc/world/Minecraft.h>
#include "ll/api/service/Bedrock.h"
#include <mc/server/commands/MinecraftCommands.h>

#include "plugin/Constant/NavTitle.h"


void UI_MenuItem::CreateUserWidget(Player& player)
{
    Log::Info("判断是否到底：" + m_menu_item.toString());

    if (0 == m_menu_item.depth) //因为本身没有子菜单了
    {
        Log::Info("depth=0");
        //说明需要构建详细菜单信息
        //根据表单类型进行构建
        if ("goods" == m_menu_item.formType)
        {
            Log::Info("是goods");
            create_goods_form(player);
        }

        else if ("recycle" == m_menu_item.formType)
        {
            Log::Info("是recycle");
            create_recycle_goods_form(player);
        }
        return;
    }


    std::string path = URL::SUB_MENU;
    std::string menuIdStr = std::to_string(m_menu_item.menuId);
    path = std::regex_replace(path, std::regex("\\{id\\}"), menuIdStr);


    std::string res = HttpService_::get_request(path); //获取子菜单列表
    json list = JsonHelper::get_data(res);
    //还未到底
    SimpleForm simple_form(m_menu_item.name);
    for (const json& item : list)
    {
        string name = item.at("name").get<string>();
        simple_form.appendButton(name, [=](Player& player)
        {
            UI_MenuItem ui_menu_item(item);
            ui_menu_item.CreateUserWidget(player);
        });
    }
    simple_form.sendTo(player);
}

void UI_MenuItem::create_goods_form(Player& player)
{
    std::string path = URL::GET_SELL_GOODSINFO;
    std::string menuIdStr = std::to_string(m_menu_item.menuId);
    path = std::regex_replace(path, std::regex("\\{id\\}"), menuIdStr);


    string res = HttpService_::get_request(path);
    json json_data = JsonHelper::get_data(res);
    const SellGoodsDetail sell_goods_detail(json_data);


    CustomForm m_custom_form(NavTitle::BUY + sell_goods_detail.goodsName);
    m_custom_form.appendLabel("你正在购买" + sell_goods_detail.goodsName + "...");


    m_custom_form.appendLabel(
        "价格：1 / " + std::to_string(static_cast<int>(sell_goods_detail.goodsPrice * 100) / 100.0) + "￥" + " 原价：" +
        std::to_string(static_cast<int>(sell_goods_detail.originalPrice * 100) / 100.0)
        + "￥");
    m_custom_form.appendSlider("slieder1", "请输入要购买的数量", 1, 64, 1, 0);
    m_custom_form.sendTo(player, [=](Player& player, ll::form::CustomFormResult const& result,
                                     ll::form::FormCancelReason cancel_reason)
    {

        if (cancel_reason.has_value()) return;
        
        
        SellGoodsDetail sell_goods_detail_inner = sell_goods_detail;
        string uuid = player.getUuid().asString();
        int amount = static_cast<int>(get<double>(result->at("slieder1")));

        SellGoods sell_goods(uuid, sell_goods_detail_inner.goodsId, amount);

        string jsonStr = sell_goods.toJson();
        string sellUrl = URL::SELL_GOODS;
        string res = HttpService_::post_request(sellUrl, jsonStr);
        json jsonData = JsonHelper::get_data(res);

        BoughtGoodsVO bought_goods_vo(jsonData);
        //购买成功
        if (bought_goods_vo.commit)
        {
            //执行指令
            execute_givecommand(player, sell_goods_detail_inner.objectId, amount);
            player.sendMessage("购买成功~\n "
                "剩余余额:" + std::to_string(bought_goods_vo.balance) + "￥");
        }
        //购买失败
        else
        {
            player.sendMessage("购买失败,余额不足\n余额:" + std::to_string(bought_goods_vo.balance) + "￥");
        }
    });
}

void UI_MenuItem::create_recycle_goods_form(Player& player)
{
    string path = URL::GET_RECYCLEDGOODSINFO;
    std::string menuIdStr = std::to_string(m_menu_item.menuId);
    // 使用 std::regex_replace 来替换 {id}
    path = std::regex_replace(path, std::regex("\\{id\\}"), menuIdStr);


    string res = HttpService_::get_request(path);
    json json_data = JsonHelper::get_data(res);
    const RecycledGoodsDetail recycle_goods_detail(json_data);

    CustomForm m_custom_form(NavTitle::RECYCLE + recycle_goods_detail.goodsName);
    m_custom_form.appendLabel("回收" + recycle_goods_detail.goodsName + "...");
    m_custom_form.appendLabel(
        "价格：1 / " + std::to_string(static_cast<int>(recycle_goods_detail.recycledPrice * 100) / 100.0) + "￥" +
        "       原价：" +
        std::to_string(static_cast<int>(recycle_goods_detail.originalPrice * 100) / 100.0)
        + "￥");
    m_custom_form.appendSlider("slieder1", "请输入要回收的数量", 1, 64, 1, 0);

    m_custom_form.sendTo(player, [=](Player& player, ll::form::CustomFormResult const& result,
                                     ll::form::FormCancelReason cancel_reason)
    {
        if (cancel_reason.has_value()) return;
        RecycledGoodsDetail recycle_goods_detail_inner = recycle_goods_detail;
        string uuid = player.getUuid().asString();
        int amount = static_cast<int>(get<double>(result->at("slieder1"))); //要出售的数量

        bool objects_amount = query_objects_amount(player, recycle_goods_detail_inner.objectId, amount);

        //足够
        if (objects_amount)
        {
            RecycleGoods recycle_goods(uuid, recycle_goods_detail_inner.goodsId, amount);
            string jsonStr = recycle_goods.toJson();
            std::string path = URL::RECYCLE_GOODS;

            string res = HttpService_::post_request(path, jsonStr);
            json jsonData = JsonHelper::get_data(res);
            RecycleGoodsEchoVO recycle_goods_echo_vo(jsonData);


            if (recycle_goods_echo_vo.balanceIncr > 0)
            {
                //执行指令
                execute_reduce_command(player, recycle_goods_detail_inner.objectId, amount);
                player.sendMessage(
                    "回收成功~\n您的财富增加" + std::to_string(recycle_goods_echo_vo.balanceIncr) + "当前财富：" + std::to_string(
                        recycle_goods_echo_vo.balance));
            }
        }
        //购买失败
        else
        {
            player.sendMessage("回收失败，数量不足");
        }
    });
}

bool UI_MenuItem::execute_givecommand(Player& player, string object_id, int amount)
{
    string command = "give " + player.getName() + " " + object_id + " " + std::to_string(amount);
    CommandContext context = CommandContext(command, std::make_unique<PlayerCommandOrigin>(PlayerCommandOrigin(player))
    );
    optional_ref<Minecraft> minecraft = ll::service::getMinecraft();
    minecraft->getCommands().executeCommand(context);
    return true;
}

bool UI_MenuItem::execute_reduce_command(const Player& player, const string& string, int amount)
{
    return true;
}

bool UI_MenuItem::query_objects_amount(const Player& player, const string& object_id, int amount)
{
    //查询是一组
    return true;
}

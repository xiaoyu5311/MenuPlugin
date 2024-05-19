#include "UI_MenuItem.h"

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
        return;
    }
    string path = "/menu/sublist/" + std::to_string(m_menu_item.menuId);
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
    string base = "/store/sell/";
    string path = base.append(std::to_string(m_menu_item.menuId)); //parent_id就是商品
    string res = HttpService_::get_request(path);
    json json_data = JsonHelper::get_data(res);
    const SellGoodsDetail sell_goods_detail(json_data);
    CustomForm m_custom_form(NavTitle::BUY_CATE_BLOCK);
    m_custom_form.appendLabel("你正在购买" + sell_goods_detail.goodsName + "...");


    m_custom_form.appendLabel(
        "价格：50 / " + std::to_string(static_cast<int>(sell_goods_detail.goodsPrice * 100) / 100.0) + "￥" + " 原价：" +
        std::to_string(static_cast<int>(sell_goods_detail.originalPrice * 100) / 100.0)
        + "￥");
    m_custom_form.appendSlider("slieder1", "请输入要购买的数量", 1, 64, 1, 0);
    m_custom_form.appendSlider("slieder2", "请输入要再次购买的数量", 1, 128, 1, 0);
    m_custom_form.sendTo(player, [=](Player& player, ll::form::CustomFormResult const& result,
                                     ll::form::FormCancelReason cancel_reason)
    {
        SellGoodsDetail sell_goods_detail_inner = sell_goods_detail;
        string uuid = player.getUuid().asString();
        int amount1 = static_cast<int>(get<double>(result->at("slieder1")));
        int amount2 = static_cast<int>(get<double>(result->at("slieder2")));
        int amount = amount1 + amount2;

        SellGoods sell_goods(uuid, sell_goods_detail_inner.goodsId, amount);

        string jsonStr = sell_goods.toJson();
        string sellUrl = "/store/sell";
        string res = HttpService_::post_request(sellUrl, jsonStr);
        bool bSuccess = JsonHelper::get_data(res).get<bool>();

        //购买成功
        if (bSuccess)
        {
            //执行指令
            execute_givecommand(player, sell_goods_detail_inner.objectId, amount);
            player.sendMessage("购买成功");
        }
        //购买失败
        else
        {
            player.sendMessage("购买失败,余额不足");
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

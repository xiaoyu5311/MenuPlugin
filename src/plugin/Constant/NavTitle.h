#pragma once
#include <string>
using std::string ;


namespace NavTitle
{
    const string MAIN_MENU = "主菜单";
    const string BUY = "主菜单>商店>购买>";
    const string RECYCLE = "主菜单>商店>回收>";
    const string TELOPORT = "主菜单>传送";
}


namespace URL
{
    const string LOGIN="/user/login";
    const string MAIN_MENU="/menu/catelist";
    const string SUB_MENU="/menu/sublist/{id}";
    const string GET_SELL_GOODSINFO="/store/sell/{id}";
    const string SELL_GOODS="/store/sell";
    const string GET_RECYCLEDGOODSINFO="/store/recycle/{id}";
    const string RECYCLE_GOODS="/store/recycle";
}

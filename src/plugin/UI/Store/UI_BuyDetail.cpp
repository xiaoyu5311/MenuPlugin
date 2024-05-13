#include "UI_BuyDetail.h"

#include <plugin/Log/Log.h>

void UI_BuyDetail::CreateUserWidget(Player& player)
{
    Log::Info("正在购买圆石");
    custom_form_ = new CustomForm();
    custom_form_->appendLabel("你正在购买圆石");
    custom_form_->appendLabel("价格：50/1");
    custom_form_->appendSlider("滑块名字", "请输入要购买的数量", 1, 64, 1,0);
    custom_form_->appendSlider("滑块名字", "请输入要再次购买的数量", 1, 128, 1,0);
    custom_form_->sendTo(player);
}

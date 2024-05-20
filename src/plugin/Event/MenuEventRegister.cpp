#include "MenuEventRegister.h"

#include <mc/server/commands/CommandRegistry.h>
#include <mc/world/item/registry/ItemStack.h>
#include "ll/api/event/EventBus.h"
#include "ll/api/event/player/PlayerJoinEvent.h"
#include "ll/api/event/player/PlayerUseItemEvent.h"
#include "mc/server/commands/CommandContext.h"
#include "mc/server/commands/PlayerCommandOrigin.h"
#include "ll/api/service/Bedrock.h"

#include <mc/world/Minecraft.h>
#include <mc/server/commands/MinecraftCommands.h>
#include <plugin/HTTP/HttpService.h>
#include <plugin/Log/Log.h>

#include "plugin/Constant/NavTitle.h"
#include "plugin/Utils/JsonHelper.h"


using ll::event::ListenerPtr;
using ll::event::player::PlayerJoinEvent;
using ll::event::player::PlayerUseItemEvent;

void MenuEventRegister::EventRegister()
{
    playerJoinEventListener = eventBus->emplaceListener<PlayerJoinEvent>(
        [](PlayerJoinEvent& event)
        {
            auto& player = event.self();
            const auto& uuid = player.getUuid();
            const string& name = player.getName();

            json loginInfo;
            loginInfo["uuid"] = uuid;
            loginInfo["nickname"] = name;

            string json = loginInfo.dump();
            string url = URL::LOGIN;
            string res = HttpService_::post_request(url, json);

            bool bNewPlayer = JsonHelper::get_data(res).get<bool>();

            //如果玩家是第一次进入游戏  数据库没有查询到
            if (bNewPlayer)
            {
                Log::Info("新玩家" + name + "进入游戏");
                ItemStack itemStack("clock", 1);
                player.add(itemStack);
                player.refreshInventory();
                player.sendMessage("欢迎新玩家：" + name);
            }
            else
            {
                Log::Info("老玩家" + name + "进入游戏");
                player.sendMessage("欢迎回来：" + name);
            }
        }
    );

    playerUseItemEventListener =
        eventBus->emplaceListener<PlayerUseItemEvent>([](PlayerUseItemEvent& event)
        {
            auto& player = event.self();
            auto& itemStack = event.item();
            if (itemStack.getRawNameId() == "clock")
            {
                CommandContext context = CommandContext(
                    "menu",
                    std::make_unique<PlayerCommandOrigin>(PlayerCommandOrigin(player))
                );
                optional_ref<Minecraft> minecraft = ll::service::getMinecraft();
                minecraft->getCommands().executeCommand(context);
            }
        });
}

void MenuEventRegister::RemoveEventListener()
{
    eventBus->removeListener(playerJoinEventListener);
    eventBus->removeListener(playerUseItemEventListener);
}

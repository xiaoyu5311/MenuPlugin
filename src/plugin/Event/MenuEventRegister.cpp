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

            //如果玩家是第一次进入游戏  数据库没有查询到
            ItemStack itemStack("clock", 1);
            player.add(itemStack);
            player.refreshInventory();

            
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

#include "MenuCommandRegister.h"

#include <ll/api/command/CommandRegistrar.h>
#include "ll/api/service/Bedrock.h"

#include <mc/server/commands/CommandOutput.h>
#include <mc/world/actor/player/Player.h>

#include "plugin/Log/Log.h"

void MenuCommandRegister::RegisterRootCommand(const string& rootCommandName,
                                                  const string& description,
                                                  CommandPermissionLevel permissionLevel,
                                                  CommandFlag flag,
                                                  weak_ptr<Plugin> plugin)
{
    auto commandRegistry = ll::service::getCommandRegistry();
    if (!commandRegistry) throw std::runtime_error("failed to get command registry 获取命令注册表失败");

    commandHandle = &CommandRegistrar::getInstance().getOrCreateCommand(
        rootCommandName,
        description,
        permissionLevel,
        flag,
        plugin);
}

void MenuCommandRegister::CommandRegister()
{
    RegisterRootCommand("/killmyslef", "杀自己");
    if (commandHandle)
    {
        commandHandle->overload().execute([](CommandOrigin const& origin,
                                             CommandOutput& output
        )
            {
                if (origin.getOriginType() != CommandOriginType::Player)
                {
                    output.error("Please type the name of player you want to query");
                    return;
                }

                if (Player* player = static_cast<Player*>(origin.getEntity()))
                {
                    player->kill();
                    Log::Info("玩家自杀");
                }
            });
    }
    else
    {
        Log::Info("指令 注册失败");
    }
}

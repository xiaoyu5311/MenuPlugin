#include "MenuCommandRegister.h"

#include <ll/api/command/CommandRegistrar.h>
#include "ll/api/service/Bedrock.h"

#include <mc/server/commands/CommandOutput.h>
#include <mc/world/actor/player/Player.h>

#include "plugin/Log/Log.h"
#include "plugin/UI/MainUserWidget.h"

MenuCommandRegister::MenuCommandRegister()
{
}

void MenuCommandRegister::RegisterRootCommand(const string& rootCommandName,
                                              const string& description,
                                              CommandPermissionLevel permissionLevel,
                                              CommandFlag flag,
                                              weak_ptr<Plugin> plugin)
{
    auto commandRegistry = ll::service::getCommandRegistry();
    if (!commandRegistry) throw std::runtime_error("failed to get command registry 获取命令注册表失败");
    Log::Info("指令正在注册....");
    commandHandle = &CommandRegistrar::getInstance().getOrCreateCommand(
        rootCommandName,
        description,
        permissionLevel,
        flag,
        plugin);
}

void MenuCommandRegister::CommandRegister()
{
    RegisterRootCommand("menu", "打开主菜单");
    if (commandHandle)
    {
        commandHandle->overload().execute([&](CommandOrigin const& origin,
                                              CommandOutput& output
        )
            {
                if (Player* player = static_cast<Player*>(origin.getEntity()))
                {
                    if (nullptr == main_user_widget)
                    {
                        main_user_widget = new MainUserWidget(); //因为复用
                    }
                    main_user_widget->CreateUserWidget(*player);
                    Log::Info("打开主菜单");
                }
                else
                {
                    Log::Info("玩家为null");
                }
            });
    }
    else
    {
        Log::Info("指令 注册失败");
        return;
    }
    Log::Info("指令 注册完成");
}

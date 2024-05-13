#pragma once
#include "CommandRegisterBase.h"

#include <ll/api/command/Command.h>
#include <ll/api/command/CommandRegistrar.h>

using ll::command::CommandHandle;
using ll::command::CommandRegistrar;
using std::string;
using std::weak_ptr;
using ll::plugin::Plugin;
using ll::plugin::NativePlugin;
using ll::reflection::Reflectable;
using ll::command::EmptyParam;

class MenuCommandRegister : public CommandRegisterBase
{
public:
    MenuCommandRegister();

    void RegisterRootCommand(const string& rootCommandName,
                             const string& description,
                             CommandPermissionLevel permissionLevel = CommandPermissionLevel::Any,
                             CommandFlag flag = CommandFlagValue::NotCheat,
                             weak_ptr<Plugin> plugin = NativePlugin::current());
    void CommandRegister() override;
};

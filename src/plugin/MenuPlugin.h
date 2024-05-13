#pragma once

#include "Command/Core/ICommandRegister.h"
#include "Event/Core/IEventRegister.h"
#include "ll/api/plugin/NativePlugin.h"

namespace MenuPlugin {

class MenuPlugin {
private:
    ICommandRegister* command_register = nullptr;
    IEventRegister* event_register = nullptr;
public:
    static MenuPlugin& getInstance();

    MenuPlugin(ll::plugin::NativePlugin& self) : mSelf(self) {}

    [[nodiscard]] ll::plugin::NativePlugin& getSelf() const { return mSelf; }

    /// @return True if the plugin is loaded successfully.
    bool load();

    /// @return True if the plugin is enabled successfully.
    bool enable();

    /// @return True if the plugin is disabled successfully.
    bool disable();

    // TODO: Implement this method if you need to unload the plugin.
    // /// @return True if the plugin is unloaded successfully.
    // bool unload();

private:
    ll::plugin::NativePlugin& mSelf;
};

} // namespace my_plugin

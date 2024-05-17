#include "plugin/MenuPlugin.h"

#include <memory>
#include "Command/MenuCommandRegister.h"
#include "Event/MenuEventRegister.h"
#include "HTTP/HttpService.h"
// #include "HTTP/http/HttpClient.h"
#include "ll/api/plugin/NativePlugin.h"
#include "ll/api/plugin/RegisterHelper.h"
#include "Log/Log.h"
// #include "curl/curl.h"
#include "hv/HttpClient.h"
#include "hv/requests.h"

// using namespace hv;

namespace MenuPlugin
{
    static std::unique_ptr<MenuPlugin> instance;

    MenuPlugin& MenuPlugin::getInstance() { return *instance; }

    bool MenuPlugin::load()
    {
        Log::Init(&getSelf().getLogger());
        Log::Info("插件加载中...Loading... ");

        return true;
    }

    bool MenuPlugin::enable()
    {

        command_register = new MenuCommandRegister();
        event_register = new MenuEventRegister();
        
        command_register->CommandRegister();
        event_register->EventRegister();

        return true;
    }

    bool MenuPlugin::disable()
    {
        Log::Info("插件关闭中...Disabling...");

        event_register->RemoveEventListener();
        delete command_register;
        delete event_register;
        return true;
    }
}

LL_REGISTER_PLUGIN(MenuPlugin::MenuPlugin, MenuPlugin::instance);

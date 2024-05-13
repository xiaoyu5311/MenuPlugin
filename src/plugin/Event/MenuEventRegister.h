#pragma once
#include "EventRegisterBase.h"
#include "Core/IEventRegister.h"
#include "ll/api/event/Listener.h"

using ll::event::ListenerPtr;

class MenuEventRegister : public EventRegisterBase {

private:
    ListenerPtr playerJoinEventListener;
    ListenerPtr playerUseItemEventListener;

public:
    MenuEventRegister() { }

    void EventRegister() override;
    void RemoveEventListener() override;

};

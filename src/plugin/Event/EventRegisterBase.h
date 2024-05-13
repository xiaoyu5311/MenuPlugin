#pragma once
#include "Core/IEventRegister.h"

#include <ll/api/event/EventBus.h>
using ll::event::EventBus;

class EventRegisterBase : public IEventRegister {

protected:
    EventBus* eventBus;

public:
    explicit EventRegisterBase()
        : eventBus(nullptr) {
        eventBus = &EventBus::getInstance();
    }

    virtual void EventRegister() =0;
    virtual void RemoveEventListener() =0;
};

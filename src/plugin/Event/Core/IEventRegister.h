#pragma once

class IEventRegister {
public:
    virtual ~IEventRegister() = default;

    virtual void EventRegister() =0;
    virtual void RemoveEventListener() =0;

};

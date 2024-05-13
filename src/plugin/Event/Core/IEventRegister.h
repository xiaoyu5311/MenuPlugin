#pragma once

class IEventRegister {
public:
    virtual void EventRegister() =0;
    virtual void RemoveEventListener() =0;

    
    virtual ~IEventRegister() = default;

};

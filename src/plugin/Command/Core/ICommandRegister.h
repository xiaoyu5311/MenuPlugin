#pragma once

class ICommandRegister {
public:
    virtual ~ICommandRegister() = default;
    virtual void CommandRegister() =0;
};

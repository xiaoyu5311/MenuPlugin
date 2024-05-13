#pragma once
#include "Core/ICommandRegister.h"

#include <ll/api/command/CommandHandle.h>

using ll::command::CommandHandle;

class CommandRegisterBase : public ICommandRegister {

protected:
    CommandHandle* commandHandle;

public:
    explicit CommandRegisterBase()
        : commandHandle(nullptr) {}

    virtual void CommandRegister() =0;
};

#pragma once
#include "Core/ICommandRegister.h"

#include <ll/api/command/CommandHandle.h>

#include "plugin/UI/MainUserWidget.h"

using ll::command::CommandHandle;

class CommandRegisterBase : public ICommandRegister
{
protected:
    CommandHandle* commandHandle;
    MainUserWidget* main_user_widget;

public:
    CommandRegisterBase();
    ~CommandRegisterBase() override;


    void CommandRegister() override =0;
};

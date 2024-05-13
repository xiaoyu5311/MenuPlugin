#include "CommandRegisterBase.h"

CommandRegisterBase::CommandRegisterBase()
    : commandHandle(nullptr), main_user_widget(nullptr)
{
}

CommandRegisterBase::~CommandRegisterBase()
{
    // if (commandHandle)
    // {
    //     delete commandHandle;
    //     commandHandle = nullptr;
    // }
    if (main_user_widget)
    {
        delete main_user_widget;
        main_user_widget = nullptr;
    }
}

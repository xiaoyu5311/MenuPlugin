#pragma once
#include <ll/api/form/SimpleForm.h>
#include <ll/api/form/CustomForm.h>

#include "UserWiget.h"
using ll::form::SimpleForm;
using ll::form::CustomForm;

typedef std::function<void(Player&)> ButtonCallback;

class UserWidgetBase : public UserWiget
{
protected:
    SimpleForm* simple_form;
    CustomForm* custom_form_;

public:
    UserWidgetBase();
    ~UserWidgetBase() override;


    void CreateUserWidget(Player& player) override =0;
};

#include "UserWidgetBase.h"


UserWidgetBase::UserWidgetBase()
    : simple_form(nullptr), custom_form_(nullptr)
{
}

UserWidgetBase::~UserWidgetBase()
{
    if (simple_form)
    {
        delete simple_form;
        simple_form = nullptr;
    }
    if (custom_form_)
    {
        delete custom_form_;
        custom_form_ = nullptr;
    }
};

#include "UserWidgetBase.h"


UserWidgetBase::UserWidgetBase()
    : m_simple_form(nullptr), m_custom_form(nullptr)
{
}

UserWidgetBase::~UserWidgetBase()
{
    if (m_simple_form)
    {
        delete m_simple_form;
        m_simple_form = nullptr;
    }
    if (m_custom_form)
    {
        delete m_custom_form;
        m_custom_form = nullptr;
    }
}




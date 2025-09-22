#pragma once
#include "core/helpers/enums.hpp"
namespace core
{
    struct Stateable
    {
        virtual void setState(ComponentState state) = 0;
        virtual ComponentState getState() const = 0;
        virtual bool isEnabled() const = 0;
        virtual bool isDisabled() const = 0;
        virtual bool isSelected() const = 0;
        virtual ~Stateable() = default;
    };
}
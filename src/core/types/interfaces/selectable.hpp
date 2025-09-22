#pragma once
#include "core/helpers/enums.hpp"
namespace core
{
    // Abstract interface for selectable components
    struct Selectable
    {
        virtual void setSelectable(SelectabilityState selectable) = 0;
        virtual SelectabilityState isSelectable() const = 0;
        virtual ~Selectable() = default;
    };
}
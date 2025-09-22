#pragma once
#include "core/helpers/enums.hpp"
namespace core
{
    // Abstract interface for visible components
    struct Visible
    {
        virtual void setVisible(VisibilityState visible) = 0;
        virtual VisibilityState isVisible() const = 0;
        virtual ~Visible() = default;
    };
}
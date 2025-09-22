#pragma once
#include "core/interfaces/visible.hpp"
#include "core/helpers/enums.hpp"
namespace core
{
    // Default implementation of Visible with storage
    class VisibleBase : public Visible
    {
    public:
        VisibleBase(VisibilityState visible_ = VisibilityState::VISIBLE) : visible(visible_) {}

        void setVisible(VisibilityState v) override { visible = v; }
        VisibilityState isVisible() const override { return visible; }

    protected:
        VisibilityState visible;
    };
}
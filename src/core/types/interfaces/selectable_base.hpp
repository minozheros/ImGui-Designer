#pragma once
#include "core/interfaces/selectable.hpp"
#include "core/helpers/enums.hpp"

namespace core
{
    // Default implementation of Selectable with storage
    class SelectableBase : public Selectable
    {
    public:
        SelectableBase(SelectabilityState selectable_ = SelectabilityState::NON_SELECTABLE) : selectable(selectable_) {}

        void setSelectable(SelectabilityState s) override { selectable = s; }
        SelectabilityState isSelectable() const override { return selectable; }

    protected:
        SelectabilityState selectable;
    };
}
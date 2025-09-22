#pragma once
#include "core/interfaces/stateable.hpp"
#include "core/helpers/enums.hpp"
namespace core
{
    // Default implementation of Stateable with storage
    class StateableBase : public Stateable
    {
    public:
        StateableBase(ComponentState state = ComponentState::DEFAULT) : state(state) {}

        void setState(ComponentState s) override { state = s; }
        ComponentState getState() const override { return state; }
        bool isEnabled() const override { return state == ComponentState::DEFAULT; }
        bool isDisabled() const override { return state == ComponentState::DISABLED; }
        bool isSelected() const override { return state == ComponentState::SELECTED; }

    protected:
        ComponentState state;
    };
}
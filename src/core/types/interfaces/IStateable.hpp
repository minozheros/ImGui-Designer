#pragma once

enum class State
{
    Enabled,
    Disabled,
    Selected
};

struct IStateable
{
    virtual void setState(State state) = 0;
    virtual State getState() const = 0;
    virtual bool isEnabled() const = 0;
    virtual bool isDisabled() const = 0;
    virtual bool isSelected() const = 0;
    virtual ~IStateable() = default;
};

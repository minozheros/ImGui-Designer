#pragma once

enum class VisibilityState
{
    Visible,
    Hidden,
    Collapsed
};

// Abstract interface for visible components
struct IVisible
{
    virtual void setVisible(VisibilityState visible) = 0;
    virtual VisibilityState isVisible() const = 0;
    virtual ~IVisible() = default;
};

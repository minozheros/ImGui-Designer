#pragma once
#include "core/interfaces/drawable.hpp"
#include "core/interfaces/positionable_base.hpp"
#include "core/interfaces/sizeable_base.hpp"
#include "core/components/event_handler.hpp"
#include "core/events/events.hpp"

namespace core
{
    // Abstract interface for a Screen
    // - Drawable, Positionable, Sizeable
    // - Not Selectable, always Visible
    // - Receives events via EventHandler

    struct Screen : public Drawable, public PositionableBase, public SizeableBase
    {
        // Event handler for this screen
        EventHandler<QuitEvent<>> eventHandler;
    };
}
#pragma once
#include <functional>
namespace core
{
    // Generic event handler component for composition
    // Usage: EventHandler<MyEvent> handler; handler.onEvent = [](const MyEvent& e) { ... };
    template <typename EventType>
    struct EventHandler
    {
        std::function<void(const EventType &)> onEvent;
    };
}
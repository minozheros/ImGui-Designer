#pragma once
#include <nlohmann/json.hpp>

// Interface for classes that can save/load their state as JSON
class ISaveable
{
public:
    virtual ~ISaveable() = default;
    // Save the component's state to JSON
    virtual nlohmann::json saveState() const = 0;
    // Load the component's state from JSON
    virtual void loadState(const nlohmann::json &state) = 0;
};

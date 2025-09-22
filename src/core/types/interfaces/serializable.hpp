#pragma once
#include <string>

// Interface for serializable objects
class ISerializable
{
public:
    virtual ~ISerializable() = default;
    // Serialize to a string (could be JSON, bitmask, etc.)
    virtual std::string serialize() const = 0;
    // Deserialize from a string
    virtual void deserialize(const std::string &data) = 0;
};

#pragma once

#include <string>
#include <memory>

namespace ImGuiDesigner {

// Marker base for replaceable / pluggable components.
class IReplaceable {
public:
    virtual ~IReplaceable() = default;
};

} // namespace ImGuiDesigner

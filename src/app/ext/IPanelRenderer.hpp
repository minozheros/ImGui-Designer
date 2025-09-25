#pragma once

#include "ExtensibilityFwd.hpp"
#include "IReplaceable.hpp"
#include <string>

namespace ImGuiDesigner {

class IPanelRenderer : public IReplaceable {
public:
    ~IPanelRenderer() override = default;

    virtual const std::string &panelId() const = 0; // Unique panel id
    virtual void draw() = 0;                       // Draw panel UI
};

} // namespace ImGuiDesigner

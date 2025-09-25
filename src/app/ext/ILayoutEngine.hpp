#pragma once

#include "ExtensibilityFwd.hpp"
#include "IReplaceable.hpp"
#include <string>

namespace ImGuiDesigner {

class ILayoutEngine : public IReplaceable {
public:
    ~ILayoutEngine() override = default;

    virtual const std::string &id() const = 0;          // Engine id
    virtual const std::string &scope() const = 0;       // Layout scope (e.g., global graph or subgraph id)
    virtual void computeLayout(void *graphContext) = 0; // Perform layout (graph context type TBD)
};

} // namespace ImGuiDesigner

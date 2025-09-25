#pragma once

#include "ExtensibilityFwd.hpp"
#include "IReplaceable.hpp"
#include <string>

namespace ImGuiDesigner
{

    class IBlockRenderer : public IReplaceable
    {
    public:
        ~IBlockRenderer() override = default;

        virtual const std::string &id() const = 0;      // Renderer id
        virtual const std::string &blockId() const = 0; // Block identifier it renders
        virtual void draw(void *context) = 0;           // Context TBD (graph/editor context)
    };

} // namespace ImGuiDesigner

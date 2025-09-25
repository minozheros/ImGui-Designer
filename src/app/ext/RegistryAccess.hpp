#pragma once

#include "ReplaceableRegistry.hpp"
#include <memory>

namespace ImGuiDesigner
{

    // Accessors for core registries (simple singletons for now). Implementation is header-only.

    template <typename IFace>
    ReplaceableRegistry<IFace> &registrySingleton()
    {
        static ReplaceableRegistry<IFace> instance;
        return instance;
    }

} // namespace ImGuiDesigner

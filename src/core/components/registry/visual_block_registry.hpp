
#pragma once
#include <type_traits>
#include <memory>
#include "enums/visual_block_types.hpp"
#include "core/components/registry/visual_block_factory.hpp"

// Template registration helper
template <typename Block, typename Params>
void registerVisualBlock(VisualBlockType type)
{
    VisualBlockFactory::instance().registerBlock(
        type,
        []()
        { return std::make_unique<Block>(std::make_unique<Params>()); });
}
#pragma once

// Call this function at application startup to register all block types with the VisualBlockFactory.
// This is the central place to register every block type you want available in the editor/toolbox.
void registerAllVisualBlocks();

// Template registration helper for individual block types.
// Use this inside registerAllVisualBlocks() to reduce boilerplate and ensure consistency.
// Example: registerVisualBlock<ButtonBlock, ButtonBlockParams>(VisualBlockType::ImGui_Button);

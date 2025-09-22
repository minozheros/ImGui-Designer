#pragma once
#include <functional>
#include <memory>
#include <unordered_map>
#include "enums/visual_block_types.hpp"
#include "core/components/base/visual_block.hpp"

class VisualBlockFactory
{
public:
    using BlockCreator = std::function<std::unique_ptr<VisualBlock>()>;
    static VisualBlockFactory &instance();
    void registerBlock(VisualBlockType type, BlockCreator creator);
    std::unique_ptr<VisualBlock> createBlock(VisualBlockType type);

private:
    std::unordered_map<VisualBlockType, BlockCreator> creators;
};

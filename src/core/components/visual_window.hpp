#pragma once
#include "core/components/base/visual_block.hpp"
#include <vector>
#include <memory>

class VisualWindow
{
public:
    void addBlock(std::unique_ptr<VisualBlock> block)
    {
        blocks.push_back(std::move(block));
    }
    void render()
    {
        for (auto &block : blocks)
        {
            block->render();
        }
    }
    void clear() { blocks.clear(); }

private:
    std::vector<std::unique_ptr<VisualBlock>> blocks;
};

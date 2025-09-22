#include "core/components/registry/visual_block_factory.hpp"
#include <utility>

VisualBlockFactory &VisualBlockFactory::instance()
{
    static VisualBlockFactory inst;
    return inst;
}

void VisualBlockFactory::registerBlock(VisualBlockType type, BlockCreator creator)
{
    creators[type] = std::move(creator);
}

std::unique_ptr<VisualBlock> VisualBlockFactory::createBlock(VisualBlockType type)
{
    auto it = creators.find(type);
    if (it != creators.end())
    {
        return it->second();
    }
    return nullptr;
}

#pragma once
#include <memory>
#include <string>
#include <unordered_map>
#include "core/types/maps/node_factory_map.hpp"
#include "core/components/base/visual_block.hpp"
#include <any>
namespace core
{
    class NodeFactory
    {
    public:
        NodeFactory();
        std::unique_ptr<VisualBlock> createBlockByName(const std::string &name);
    };
}

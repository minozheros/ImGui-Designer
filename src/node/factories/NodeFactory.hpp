#pragma once
#include <memory>
#include <string>
#include <unordered_map>
#include "core/types/maps/NodeFactoryMap.hpp"
#include "core/types/maps/NodeParamsMap.hpp"
#include "core/components/base/VisualBlock.hpp"
#include <any>

class NodeFactory
{
public:
    NodeFactory();
    std::unique_ptr<VisualBlock> createBlockByName(const std::string &name);
};

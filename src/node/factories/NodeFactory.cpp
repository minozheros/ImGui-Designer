#include "node/factories/NodeFactory.hpp"
#include <spdlog/spdlog.h>
#include <typeinfo>
#include <atomic>
#include <imgui_node_editor.h>
#include "node/blocks/GenericVisualBlock.hpp"

NodeFactory::NodeFactory()
{
    spdlog::info("NodeFactory constructed");
}

std::unique_ptr<VisualBlock> NodeFactory::createBlockByName(const std::string &name)
{
    auto it = NODE_CLASS_MAP.find(name);
    if (it == NODE_CLASS_MAP.end())
    {
        spdlog::warn("NodeFactory: No node class found for '{}'.", name);
        return nullptr;
    }
    auto paramsIt = core::NODE_PARAMS_FACTORY.find(name);
    if (paramsIt == core::NODE_PARAMS_FACTORY.end())
    {
        spdlog::warn("NodeFactory: No parameter struct found for '{}'.", name);
        return nullptr;
    }
    // Generate a unique NodeId for the new block
    static std::atomic<uintptr_t> nextId{1};
    ed::NodeId nodeId{nextId++};

    // Create params
    auto params = paramsIt->second();

    // Create GenericVisualBlock with the params
    spdlog::info("NodeFactory: Creating GenericVisualBlock for '{}' with id {}", name, nodeId.Get());
    // Convert IParameter* to IParameterBase* using dynamic_cast (safe since Parameter<T> inherits from both)
    auto paramsVector = params->getParameters();
    std::vector<IParameterBase *> baseParams;
    baseParams.reserve(paramsVector.size());
    for (auto *param : paramsVector)
    {
        // Use dynamic_cast to safely cast from IParameter* to IParameterBase*
        if (auto *baseParam = dynamic_cast<IParameterBase *>(param))
        {
            baseParams.push_back(baseParam);
        }
        else
        {
            spdlog::error("NodeFactory: Failed to cast parameter to IParameterBase*");
        }
    }
    return std::make_unique<core::GenericVisualBlock>(nodeId, name, baseParams);
}

#include "core/factories/node_factory.hpp"
#include <spdlog/spdlog.h>
#include <typeinfo>
#include <atomic>
#include <imgui_node_editor.h>
#include "core/components/blocks/BeginCombo/begin_combo_node.hpp"

core::NodeFactory::NodeFactory()
{
    spdlog::info("NodeFactory constructed");
}

std::unique_ptr<VisualBlock> core::NodeFactory::createBlockByName(const std::string &name)
{
    auto it = NODE_CLASS_MAP.find(name);
    if (it == NODE_CLASS_MAP.end())
    {
        spdlog::warn("NodeFactory: No node class found for '{}'.", name);
        return nullptr;
    }

    // Generate a unique NodeId for the new block
    static std::atomic<uintptr_t> nextId{1};
    ed::NodeId nodeId{nextId++};

    // Create the appropriate node type
    if (it->second == "BeginComboNode")
    {
        spdlog::info("NodeFactory: Creating BeginComboNode with id {}", nodeId.Get());
        return std::make_unique<core::BeginComboNode>(nodeId);
    }

    // TODO: Add factory logic for other node types
    spdlog::warn("NodeFactory: Node type '{}' not implemented yet.", it->second);
    return nullptr;
}

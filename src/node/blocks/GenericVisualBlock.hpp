#pragma once
#include <string>
#include <vector>
#include <imgui_node_editor.h>
#include "core/components/base/VisualBlock.hpp"
#include "node/blocks/GenericNode.hpp"
#include "core/types/base/ParameterBase.hpp"

namespace ed = ax::NodeEditor;

namespace core
{
    class GenericVisualBlock : public VisualBlock
    {
    private:
        GenericNode genericNode_;
        ed::NodeId nodeId_;

    public:
        GenericVisualBlock(ed::NodeId id, const std::string &title, const std::vector<IParameterBase *> &params)
            : genericNode_(title, params), nodeId_(id)
        {
            setNodeId(id);
        }

        void render() override
        {
            genericNode_.render();
        }

        ed::NodeId getNodeId() const override
        {
            return nodeId_;
        }
    };
}
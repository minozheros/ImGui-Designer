#pragma once
#include <string>
#include <imgui.h>
#include <imgui_node_editor.h>
#include <unordered_map>
#include <any>
#include <memory>
#include <functional>
#include <vector>
#include <cstring>
#include <implot.h>
#include <spdlog/spdlog.h>

namespace ed = ax::NodeEditor;

class VisualBlock
{
public:
    VisualBlock()
    {
        const auto &self = *this;
        spdlog::info("VisualBlock constructed: {}", typeid(self).name());
    }
    virtual ~VisualBlock()
    {
        const auto &self = *this;
        spdlog::info("VisualBlock destroyed: {}", typeid(self).name());
    }
    virtual void render() = 0;
    virtual ImVec2 getPreferredSize(const char *name = nullptr, const char *value = nullptr, int numInputs = 0, int numOutputs = 0) const;
    virtual void setInput(const std::string &name, std::any value);
    virtual std::any getOutput(const std::string &name) const;
    virtual void setOutput(const std::string &name, std::any value);
    const std::unordered_map<std::string, std::any> &getInputs() const;
    const std::unordered_map<std::string, std::any> &getOutputs() const;

    virtual void setNodeId(ed::NodeId id) { nodeId_ = id; }
    virtual ed::NodeId getNodeId() const { return nodeId_; }

protected:
    std::unordered_map<std::string, std::any> inputs_;
    std::unordered_map<std::string, std::any> outputs_;
    ed::NodeId nodeId_{0};
};

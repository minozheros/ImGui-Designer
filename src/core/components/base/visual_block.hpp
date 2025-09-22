#pragma once
#include <string>
#include <imgui.h>
#include <unordered_map>
#include <any>
#include <memory>
#include <functional>
#include <vector>
#include <cstring>
#include <implot.h>

class VisualBlock
{
public:
    virtual ~VisualBlock() = default;
    virtual void render() = 0;
    virtual ImVec2 getPreferredSize(const char *name = nullptr, const char *value = nullptr, int numInputs = 0, int numOutputs = 0) const;
    virtual void setInput(const std::string &name, std::any value);
    virtual std::any getOutput(const std::string &name) const;
    virtual void setOutput(const std::string &name, std::any value);
    const std::unordered_map<std::string, std::any> &getInputs() const;
    const std::unordered_map<std::string, std::any> &getOutputs() const;

protected:
    std::unordered_map<std::string, std::any> inputs_;
    std::unordered_map<std::string, std::any> outputs_;
};

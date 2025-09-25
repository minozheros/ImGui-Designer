#pragma once

#include "ExtensibilityFwd.hpp"
#include "IReplaceable.hpp"
#include <string>
#include <span>
#include <vector>

namespace ImGuiDesigner {

class IFrameHook : public IReplaceable {
public:
    enum class Stage {
        BeginFrame,
        PreUpdate,
        GraphResolve,
        Panels,
        Overlays,
        LateDecorators,
        RenderSubmit,
        PostFrame
    };

    ~IFrameHook() override = default;

    virtual const std::string &id() const = 0;               // Hook id
    virtual std::span<const Stage> stages() const = 0;        // Stages this hook participates in
    virtual void run(Stage stage) = 0;                        // Execute for a stage
};

} // namespace ImGuiDesigner

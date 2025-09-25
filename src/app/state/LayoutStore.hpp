#pragma once
#include <string>

struct ImGuiContext;

namespace app::state
{

    class LayoutStore final
    {
    public:
        explicit LayoutStore(ImGuiContext *ctx = nullptr) : imguiCtx(ctx) {}

        // Update context if it changes
        void setContext(ImGuiContext *ctx) { imguiCtx = ctx; }

        // Save current ImGui layout (ini) to the provided file path
        bool saveLayoutToFile(const std::string &path) const;

        // Load an ImGui layout (ini) from file path and apply to current context
        bool loadLayoutFromFile(const std::string &path) const;

        // Convenience default path helpers
        static std::string defaultLayoutPath();
        bool saveDefaultLayout() const { return saveLayoutToFile(defaultLayoutPath()); }
        bool loadDefaultLayout() const { return loadLayoutFromFile(defaultLayoutPath()); }

        // Reset current layout to empty/default (clears ini settings in memory)
        void resetLayoutToDefault() const;

    private:
        ImGuiContext *imguiCtx = nullptr;
    };

} // namespace app::state

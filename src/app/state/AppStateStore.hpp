#pragma once
#include <string>
#include <optional>

namespace app::state
{

    class AppStateStore final
    {
    public:
        // The store writes to "registry/app_state.json" in the current project root (cwd).
        AppStateStore() = default;

        std::optional<std::string> loadLastLeftTab() const;
        void saveLastLeftTab(const std::string &tabName) const;
    };

} // namespace app::state

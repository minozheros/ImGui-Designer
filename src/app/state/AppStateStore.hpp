#pragma once
#include <string>
#include <optional>

namespace app::state
{

    class AppStateStore final
    {
    public:
        // By default, writes to "registry/app_state.json" in the current project root (cwd).
        AppStateStore();
        explicit AppStateStore(std::string statePath);

        std::optional<std::string> loadLastLeftTab() const;
        void saveLastLeftTab(const std::string &tabName) const;

    private:
        std::string statePath;
    };

} // namespace app::state

#include "app/state/AppStateStore.hpp"

#include <nlohmann/json.hpp>
#include <fstream>

namespace app::state
{

    static const char *kDefaultStatePath = "registry/app_state.json";

    AppStateStore::AppStateStore() : statePath(kDefaultStatePath) {}
    AppStateStore::AppStateStore(std::string statePath) : statePath(std::move(statePath)) {}

    std::optional<std::string> AppStateStore::loadLastLeftTab() const
    {
    std::ifstream f(statePath);
        if (!f.is_open())
            return std::nullopt;
        try
        {
            nlohmann::json j;
            f >> j;
            if (j.contains("lastLeftTab") && j["lastLeftTab"].is_string())
                return j["lastLeftTab"].get<std::string>();
        }
        catch (...)
        {
            return std::nullopt;
        }
        return std::nullopt;
    }

    void AppStateStore::saveLastLeftTab(const std::string &tabName) const
    {
        nlohmann::json j;
        // Load existing if present to preserve future fields
        {
            std::ifstream f(statePath);
            if (f.is_open())
            {
                try
                {
                    f >> j;
                }
                catch (...)
                {
                    j = nlohmann::json{};
                }
            }
        }
        j["lastLeftTab"] = tabName;
        std::ofstream o(statePath);
        o << j.dump(2);
    }

} // namespace app::state

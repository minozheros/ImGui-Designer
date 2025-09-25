#include "app/packs/PackIndexLoader.hpp"

#include <fstream>
#include <nlohmann/json.hpp>

namespace app::packs
{

    using nlohmann::json;

    static PackEntry parseEntry(const json &j)
    {
        PackEntry e{};
        e.id = j.value("id", "");
        e.kind = j.value("kind", "");
        e.repo = j.value("repo", "");
        e.ref = j.value("ref", "");
        e.path = j.value("path", "");
        e.dest = j.value("dest", "");
        e.trust = j.value("trust", "community");
        e.license = j.value("license", "");
        e.description = j.value("description", "");
        e.enabled = j.value("enabled", true);
        return e;
    }

    std::optional<PackIndex> loadFromFile(const std::string &path)
    {
        std::ifstream f(path);
        if (!f.is_open())
            return std::nullopt;
        json j;
        try
        {
            f >> j;
        }
        catch (...)
        {
            return std::nullopt;
        }
        PackIndex idx{};
        idx.version = j.value("version", "");
        idx.updatedAt = j.value("updatedAt", "");
        if (j.contains("entries") && j["entries"].is_array())
        {
            for (const auto &je : j["entries"])
            {
                idx.entries.push_back(parseEntry(je));
            }
        }
        return idx;
    }

} // namespace app::packs

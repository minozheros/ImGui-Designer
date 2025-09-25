#pragma once

#include <string>
#include <vector>
#include <optional>

namespace app::packs
{

    struct PackEntry
    {
        std::string id;
        std::string kind; // featureset|package|tutorial
        std::string repo;
        std::string ref;
        std::string path;
        std::string dest;
        std::string trust; // official|verified|community
        std::string license;
        std::string description;
        bool enabled{true};
    };

    struct PackIndex
    {
        std::string version;
        std::string updatedAt;
        std::vector<PackEntry> entries;
    };

    // Load PackIndex JSON from a local file on disk.
    std::optional<PackIndex> loadFromFile(const std::string &path);

} // namespace app::packs

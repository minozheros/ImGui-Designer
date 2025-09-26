// ProjectService.cpp
#include "app/state/ProjectService.hpp"
#include <spdlog/spdlog.h>
#include <filesystem>

namespace fs = std::filesystem;
namespace app::state
{
    bool ProjectService::newProject(const std::string &name)
    {
        // Reset current project meta; mark dirty (empty new state not yet saved)
        currentProject = ProjectMeta{.name = name, .path = {}};
        dirty = true;
        spdlog::info("[ProjectService] New project created: {}", name);
        return true;
    }

    bool ProjectService::openProject(const std::string &filepath)
    {
        // Placeholder: verify file exists; actual parse deferred until format decided
        if (!fs::exists(filepath))
        {
            spdlog::warn("[ProjectService] Open failed. File does not exist: {}", filepath);
            return false;
        }
        // TODO(ARCH/FMT): parse file once format established.
        currentProject = ProjectMeta{.name = fs::path(filepath).stem().string(), .path = fs::weakly_canonical(filepath).string()};
        dirty = false;
        spdlog::info("[ProjectService] Opened project: {} (path={})", currentProject->name, currentProject->path);
        return true;
    }

    bool ProjectService::saveProject()
    {
        if (!currentProject)
        {
            spdlog::warn("[ProjectService] saveProject called with no active project");
            return false;
        }
        if (currentProject->path.empty())
        {
            spdlog::info("[ProjectService] saveProject requires path (invoke saveProjectAs)");
            return false; // caller must handle Save As flow
        }
        // Placeholder: persist current model once defined
        spdlog::info("[ProjectService] Saved project to {}", currentProject->path);
        dirty = false;
        return true;
    }

    bool ProjectService::saveProjectAs(const std::string &filepath)
    {
        if (!currentProject)
        {
            spdlog::warn("[ProjectService] saveProjectAs with no active project");
            return false;
        }
        // Placeholder: write data (format TBD)
        currentProject->path = fs::weakly_canonical(fs::path(filepath)).string();
        spdlog::info("[ProjectService] Saved project as {}", currentProject->path);
        dirty = false;
        return true;
    }
}

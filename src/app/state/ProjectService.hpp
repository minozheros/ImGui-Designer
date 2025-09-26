// ProjectService.hpp
// Lightweight scaffold for project/session file operations.
// NOTE: File format intentionally undecided; this service only establishes
// the interface and logging hooks so MainMenuBar actions can be wired
// without committing to persistence details.
//
// Rules alignment:
// - ARCH-01: Encapsulate logic away from UI menu component.
// - CLEAN-01: Avoid leaving TODOs inline in UI layer.
// - ASK-01: Ambiguous file format deferred; interface documents assumptions.
// - TEST-01: Future tests will target these interfaces once format chosen.

#pragma once

#include <string>
#include <optional>

namespace app::state
{
    struct ProjectMeta
    {
        std::string name;
        std::string path; // canonical path when saved
    };

    class ProjectService
    {
    public:
        // Create a new in-memory project. Discards unsaved current state (future: warn if dirty)
        bool newProject(const std::string &name = "Untitled");

        // Load a project from disk. Format TBD. Returns false if load fails or format unsupported.
        bool openProject(const std::string &filepath);

        // Save current project. If no path yet (unsaved), caller should invoke saveProjectAs.
        bool saveProject();

        // Save project to a new location / name.
        bool saveProjectAs(const std::string &filepath);

        // Access current meta (if any project is active and named)
        const std::optional<ProjectMeta> &current() const { return currentProject; }

        // Whether there are unsaved modifications (dirty tracking TBD)
        bool isDirty() const { return dirty; }

    private:
        std::optional<ProjectMeta> currentProject;
        bool dirty = false;
    };
}

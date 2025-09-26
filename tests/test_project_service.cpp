#include <catch2/catch_all.hpp>
#include "app/state/ProjectService.hpp"

// Implemented coverage:
//  - newProject sets meta + dirty
//  - saveProject without path fails
//  - saveProjectAs assigns path and clears dirty
//  - openProject missing file returns false
//  - openProject existing file sets name/path
//  - dirty flag transitions
// (Rules: TEST-01, TEST-03, ARCH-01, CLEAN-01)

#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

using app::state::ProjectService;

TEST_CASE("ProjectService::newProject initializes state", "[project]") {
    ProjectService svc;
    REQUIRE_FALSE(svc.current().has_value());
    REQUIRE(svc.newProject("Alpha"));
    REQUIRE(svc.current().has_value());
    REQUIRE(svc.current()->name == "Alpha");
    REQUIRE(svc.isDirty());
}

TEST_CASE("ProjectService::saveProject returns false without path", "[project]") {
    ProjectService svc;
    svc.newProject();
    REQUIRE(svc.isDirty());
    REQUIRE_FALSE(svc.saveProject()); // no path yet
    REQUIRE(svc.isDirty()); // still dirty
}

TEST_CASE("ProjectService::saveProjectAs sets path and clears dirty", "[project]") {
    ProjectService svc;
    svc.newProject("Demo");
    fs::path tmp = fs::temp_directory_path() / "imgui_designer_project_demo.proj";
    REQUIRE(svc.saveProjectAs(tmp.string()));
    REQUIRE(svc.current().has_value());
    REQUIRE(!svc.current()->path.empty());
    REQUIRE_FALSE(svc.isDirty());
}

TEST_CASE("ProjectService::openProject missing file", "[project]") {
    ProjectService svc;
    fs::path bogus = fs::temp_directory_path() / "definitely_missing_12345.fake";
    if (fs::exists(bogus)) fs::remove(bogus); // ensure
    REQUIRE_FALSE(svc.openProject(bogus.string()));
    REQUIRE_FALSE(svc.current().has_value());
}

TEST_CASE("ProjectService::openProject existing file sets name and path", "[project]") {
    ProjectService svc;
    fs::path tmp = fs::temp_directory_path() / "example_existing_project_file.proj";
    {
        std::ofstream o(tmp.string());
        o << "placeholder";
    }
    REQUIRE(svc.openProject(tmp.string()));
    REQUIRE(svc.current().has_value());
    REQUIRE(svc.current()->path == fs::weakly_canonical(tmp).string());
    REQUIRE(svc.current()->name == tmp.stem().string());
    REQUIRE_FALSE(svc.isDirty());
    fs::remove(tmp);
}

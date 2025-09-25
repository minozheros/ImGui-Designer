#include <catch2/catch_all.hpp>
#include "app/state/AppStateStore.hpp"

#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

TEST_CASE("AppStateStore saves and loads lastLeftTab", "[appstate]")
{
    // Create a temporary directory for the test state file
    auto tmp = fs::temp_directory_path() / fs::path("imgui_designer_app_state_test");
    fs::create_directories(tmp);
    auto statePath = (tmp / "app_state.json").string();

    app::state::AppStateStore store(statePath);

    // Initially missing file should return nullopt
    REQUIRE_FALSE(store.loadLastLeftTab().has_value());

    // Save a value and verify it can be loaded
    store.saveLastLeftTab("Pack Manager");
    auto loaded = store.loadLastLeftTab();
    REQUIRE(loaded.has_value());
    REQUIRE(loaded.value() == std::string("Pack Manager"));

    // Overwrite and read again
    store.saveLastLeftTab("Toolbar");
    loaded = store.loadLastLeftTab();
    REQUIRE(loaded.has_value());
    REQUIRE(loaded.value() == std::string("Toolbar"));

    // Cleanup
    fs::remove_all(tmp);
}

TEST_CASE("AppStateStore handles malformed JSON gracefully", "[appstate]")
{
    auto tmp = fs::temp_directory_path() / fs::path("imgui_designer_app_state_badjson");
    fs::create_directories(tmp);
    auto statePath = (tmp / "app_state.json").string();

    // Write malformed JSON
    {
        std::ofstream o(statePath);
        o << "{ not_json: }";
    }

    app::state::AppStateStore store(statePath);
    auto loaded = store.loadLastLeftTab();
    REQUIRE_FALSE(loaded.has_value());

    fs::remove_all(tmp);
}

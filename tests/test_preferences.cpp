#include <catch2/catch_all.hpp>
#include "core/helpers/preferences/preferences.hpp"
#include <fstream>
#include <cstdio>

TEST_CASE("Preferences basic get/set/save/load")
{
    const std::string test_file = "test_config.json";
    // Clean up any old file
    std::remove(test_file.c_str());

    core::Preferences prefs(test_file);
    prefs["main"]["window_width"] = 1024;
    prefs["main"]["window_height"] = 768;
    prefs.save();

    core::Preferences loaded(test_file);
    REQUIRE(loaded["main"]["window_width"] == 1024);
    REQUIRE(loaded["main"]["window_height"] == 768);

    // Clean up
    std::remove(test_file.c_str());
}

TEST_CASE("Preferences safe_get for nested values")
{
    core::Preferences prefs(""); // No file needed for this test
    prefs["main"]["window_x"] = 55;
    REQUIRE(prefs.safe_get<int>({"main", "window_x"}, 0) == 55);
    REQUIRE(prefs.safe_get<int>({"main", "not_found"}, 42) == 42);
    REQUIRE(prefs.safe_get<int>({"not_found", "window_x"}, 99) == 99);
}

TEST_CASE("Preferences handles missing file gracefully")
{
    const std::string missing_file = "definitely_missing_config.json";
    // Ensure file does not exist
    std::remove(missing_file.c_str());
    REQUIRE_NOTHROW(core::Preferences(missing_file));
}

TEST_CASE("Preferences handles malformed file gracefully")
{
    const std::string malformed_file = "malformed_config.json";
    {
        std::ofstream ofs(malformed_file);
        ofs << "{ this is not valid json }";
    }
    // Should not throw, should use empty/default config
    REQUIRE_NOTHROW(core::Preferences(malformed_file));
    std::remove(malformed_file.c_str());
}

TEST_CASE("Preferences type mismatch returns default")
{
    core::Preferences prefs("");
    prefs["main"]["window_x"] = "not_an_int";
    int val = prefs.safe_get<int>({"main", "window_x"}, 123);
    REQUIRE(val == 123); // Should return default on type error
}

TEST_CASE("Preferences set/get methods work as expected")
{
    core::Preferences prefs("");
    prefs.set("fps_limit", 60);
    REQUIRE(prefs.get<int>("fps_limit", 0) == 60);
    REQUIRE(prefs.get<int>("not_found", 42) == 42);
}

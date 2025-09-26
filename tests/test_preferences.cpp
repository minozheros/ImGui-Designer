#include <catch2/catch_all.hpp>
#include "core/helpers/preferences/Preferences.hpp"
#include "TestHelpers.hpp"

// Implemented coverage:
//  - set + get round trip
//  - safe_get fallback & successful nested access
//  - persistence after save + reload
// (Rules: TEST-01, TEST-03)

#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

static Preferences makePrefs(const std::string &fname) {
    auto base = testhelpers::tempDir("prefs");
    fs::create_directories(base);
    auto path = (base / fname).string();
    // Create empty JSON file to satisfy constructor existence check
    std::ofstream o(path); o << "{}"; o.close();
    return Preferences(path);
}

TEST_CASE("Preferences basic round trip", "[preferences]") {
    auto prefs = makePrefs("round_trip.json");
    prefs.set("fps_limit", 144);
    REQUIRE(prefs.get<int>("fps_limit") == 144);
    REQUIRE(prefs.get<int>("missing_key", 42) == 42);
    prefs.set("volume", 0.75);
    REQUIRE(prefs.get<double>("volume") == Catch::Approx(0.75));
}

TEST_CASE("Preferences persistence after save & reload", "[preferences]") {
    auto base = testhelpers::tempDir("prefs");
    auto path = (base / "persist.json").string();
    { std::ofstream o(path); o << "{}"; }
    {
        Preferences prefs(path);
        prefs.set("theme", std::string("dark"));
        prefs.set("nested", nlohmann::json{{"inner", 7}});
        prefs.save();
    }
    Preferences reloaded(path);
    REQUIRE(reloaded.get<std::string>("theme") == "dark");
    REQUIRE(reloaded.safe_get<int>({"nested","inner"}, -1) == 7);
}

TEST_CASE("Preferences safe_get fallback", "[preferences]") {
    auto prefs = makePrefs("fallback.json");
    REQUIRE(prefs.safe_get<int>({"non","existent"}, 123) == 123);
    // Populate nested
    prefs.set("root", nlohmann::json{{"leaf", true}});
    REQUIRE(prefs.safe_get<bool>({"root","leaf"}, false));
    // Type mismatch returns default
    REQUIRE(prefs.safe_get<int>({"root","leaf"}, 9) == 9);
}

#include <catch2/catch_all.hpp>
#include <filesystem>
#include <regex>

// Compliance test for build marker naming (governance rule: markers must end with .marker
// and use snake_case or simple lowercase + underscores before extension).

namespace fs = std::filesystem;

TEST_CASE("Build marker naming compliance", "[infra][markers]") {
    const fs::path buildDir = fs::path("."); // ctest working dir is build/
    REQUIRE(fs::exists(buildDir));

    std::regex pattern(R"(^[a-z0-9_]+\.marker$)");
    bool foundAny = false;
    for (auto &entry : fs::directory_iterator(buildDir)) {
        if (!entry.is_regular_file()) continue;
        const auto name = entry.path().filename().string();
        if (name.size() > 7 && name.rfind(".marker") == name.size() - 7) {
            foundAny = true;
            INFO("Checking marker: " << name);
            REQUIRE(std::regex_match(name, pattern));
        }
    }

    REQUIRE(foundAny); // ensure at least one marker to validate (e.g., build_succeeded.marker)
}

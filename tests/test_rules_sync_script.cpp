#include <catch2/catch_all.hpp>
#include <cstdio>
#include <array>
#include <string>
#include <memory>
#include <cstdlib>
#include <filesystem>

namespace fs = std::filesystem;

// Implemented test: executes validator python script and asserts exit code 0.
// Relies on python being in PATH as build already finds interpreter for CMake target.
// (Rules: TEST-01, CONSIST-01)

static int runValidator() {
    // Build relative path: project root assumed two levels up from build test exe working dir if run from build dir.
    // Safer: detect presence of scripts/validate_rules_sync.py walking upwards.
    fs::path start = fs::current_path();
    for(int i=0;i<6;++i) {
        auto candidate = start / "scripts" / "validate_rules_sync.py";
        if (fs::exists(candidate)) {
            std::string cmd = "python \"" + candidate.string() + "\"";
            int code = std::system(cmd.c_str());
            if (code == -1) return -1;
            // On POSIX, actual exit code is (code >> 8)
            return (code >> 8);
        }
        start = start.parent_path();
        if(start.empty()) break;
    }
    return -1; // script not found
}

TEST_CASE("Rules sync script reports OK", "[rules]") {
    int exitCode = runValidator();
    REQUIRE(exitCode == 0);
}

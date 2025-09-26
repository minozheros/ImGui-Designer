#include <catch2/catch_all.hpp>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>

// Idempotence test for scripts/generate_rules_yaml.py
// Ensures that invoking the generator twice without changing the canonical markdown
// does not modify rules.yml the second time (GEN rules + TEST-02 golden stability).

namespace fs = std::filesystem;

static std::string readFile(const fs::path& p) {
    std::ifstream in(p);
    REQUIRE(in.good());
    std::ostringstream oss; oss << in.rdbuf();
    return oss.str();
}

TEST_CASE("generate_rules_yaml.py idempotence", "[rules][generator][idempotence]") {
    const fs::path repoRoot = fs::path(".."); // test binary runs from build directory
    const fs::path script = repoRoot / "scripts" / "generate_rules_yaml.py";
    const fs::path yaml = repoRoot / ".github" / "instructions" / "rules.yml";
    const fs::path canon = repoRoot / ".github" / "instructions" / "first.instructions.md";

    REQUIRE(fs::exists(script));
    REQUIRE(fs::exists(yaml));
    REQUIRE(fs::exists(canon));

    const auto before = readFile(yaml);

    // First run (may legitimately change file if drift existed when tests started)
    {
        std::string cmd = "python3 '" + script.string() + "'"; // rely on env python3
        int rc = std::system(cmd.c_str());
        REQUIRE(rc == 0);
    }
    const auto afterFirst = readFile(yaml);

    // Second run should yield identical contents
    {
        std::string cmd = "python3 '" + script.string() + "'";
        int rc = std::system(cmd.c_str());
        REQUIRE(rc == 0);
    }
    const auto afterSecond = readFile(yaml);

    // Assert idempotence: contents stable after first correction pass
    REQUIRE(afterFirst == afterSecond);

    // If the generator mutated from initial state, we still want to ensure it settled.
    // (Optional diagnostic) Provide size diff to help debugging.
    INFO("Original size: " << before.size() << ", afterFirst: " << afterFirst.size() << ", afterSecond: " << afterSecond.size());
}

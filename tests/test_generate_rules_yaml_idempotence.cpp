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

    auto runGenerator = [&](int attempt){
        std::string cmd = "python3 '" + script.string() + "' 2>&1";
        FILE* pipe = popen(cmd.c_str(), "r");
        REQUIRE(pipe != nullptr);
        std::string output;
        char buffer[256];
        while (fgets(buffer, sizeof(buffer), pipe)) { output += buffer; }
        int rc = pclose(pipe);
        // If we hit a crash (139) allow one retry to mitigate intermittent environment flakiness
        if (rc == 139 && attempt == 0) {
            WARN("Generator exited with 139 on attempt 0; retrying once. Output:\n" << output);
            return runGenerator(attempt+1);
        }
        INFO("Generator exit code: " << rc << " output size: " << output.size());
        REQUIRE(rc == 0);
        return output;
    };

    // First run (may legitimately change file if drift existed when tests started)
    runGenerator(0);
    const auto afterFirst = readFile(yaml);

    // Second run should yield identical contents
    runGenerator(0);
    const auto afterSecond = readFile(yaml);

    // Assert idempotence: contents stable after first correction pass
    REQUIRE(afterFirst == afterSecond);

    // If the generator mutated from initial state, we still want to ensure it settled.
    // (Optional diagnostic) Provide size diff to help debugging.
    INFO("Original size: " << before.size() << ", afterFirst: " << afterFirst.size() << ", afterSecond: " << afterSecond.size());
}

#include <catch2/catch_all.hpp>
#include <fstream>
#include <sstream>
#include <string>

// Golden snippet test for generated NodeParamsMap.hpp.
// This protects against accidental reformatting or ordering changes in a
// representative cluster of menu-related factories. If the generator's
// intentional output changes, update the snippet below consciously.

TEST_CASE("Generated NodeParamsMap golden snippet", "[generated][golden][params-map]") {
    // Expected contiguous snippet taken from src/generated/maps/NodeParamsMap.hpp
    static const char* kSnippet =
        "    {\"BeginMenuBar\", []() -> std::unique_ptr<IParamsBase> { return std::make_unique<BeginMenuBarParams>(); }},\n"
        "    {\"EndMenuBar\", []() -> std::unique_ptr<IParamsBase> { return std::make_unique<EndMenuBarParams>(); }},\n"
        "    {\"BeginMainMenuBar\", []() -> std::unique_ptr<IParamsBase> { return std::make_unique<BeginMainMenuBarParams>(); }},\n"
        "    {\"EndMainMenuBar\", []() -> std::unique_ptr<IParamsBase> { return std::make_unique<EndMainMenuBarParams>(); }},\n"
        "    {\"BeginMenu\", []() -> std::unique_ptr<IParamsBase> { return std::make_unique<BeginMenuParams>(); }},\n"
        "    {\"EndMenu\", []() -> std::unique_ptr<IParamsBase> { return std::make_unique<EndMenuParams>(); }},\n";

    const std::string headerPath = "../src/generated/maps/NodeParamsMap.hpp"; // relative to test binary working dir (build directory)
    std::ifstream in(headerPath);
    REQUIRE(in.good());
    std::ostringstream oss; oss << in.rdbuf();
    std::string contents = oss.str();

    INFO("Looking for golden snippet in NodeParamsMap.hpp. If this fails due to intentional generator change, update kSnippet consciously.");
    REQUIRE(contents.find(kSnippet) != std::string::npos);
}

#include <catch2/catch_all.hpp>
#include <core/types/maps/NodeParamsMap.hpp>

// The generated map should expose factories for many ImGui blocks. We sanity-check
// a representative subset including: entries with single overload, multiple overloads,
// and menu bar related blocks used by the application's main menu.
// This gives us early detection if the code generator fails to emit or register
// these blocks (GEN rules) without needing to exhaustively enumerate everything.

TEST_CASE("Generated NodeParamsMap basic invariants", "[generated][params-map]") {
    // Acquire the map (header defines a function or variable depending on generation style).
    const auto &map = core::NODE_PARAMS_FACTORY;

    SECTION("Representative keys exist") {
        // Single-overload style
        REQUIRE(map.find("BeginMainMenuBar") != map.end());
        REQUIRE(map.find("EndMainMenuBar") != map.end());
        REQUIRE(map.find("BeginMenuBar") != map.end());
        REQUIRE(map.find("EndMenuBar") != map.end());
        // Typical widget
        REQUIRE(map.find("InputFloat3") != map.end());
        // Color edit (another family)
        REQUIRE(map.find("ColorEdit4") != map.end());
        // Popup
        REQUIRE(map.find("BeginPopup") != map.end());
        REQUIRE(map.find("EndPopup") != map.end());
        // Table API
        REQUIRE(map.find("TableNextRow") != map.end());
    }

    SECTION("Entries produce non-null params objects") {
        auto assertFactoryWorks = [&](const char* key) {
            auto it = map.find(key);
            REQUIRE(it != map.end());
            auto instance = it->second();
            REQUIRE(instance != nullptr);
        };
        assertFactoryWorks("BeginMainMenuBar");
        assertFactoryWorks("EndMainMenuBar");
        assertFactoryWorks("InputFloat3");
        assertFactoryWorks("ColorEdit4");
        assertFactoryWorks("BeginPopup");
        assertFactoryWorks("TableNextRow");
    }

    SECTION("Duplicate key scenario (multiple overloads)") {
        // Some ImGui functions appear multiple times with different generated param structs (e.g., MenuItem, Value, TreePush).
        // Our generation strategy currently represents them as repeated entries; in a std::unordered_map this collapses to the last one.
        // We at least ensure one callable factory remains present for such a key.
        auto it = map.find("MenuItem");
        REQUIRE(it != map.end());
        auto ptr = it->second();
        REQUIRE(ptr != nullptr);
    }
}

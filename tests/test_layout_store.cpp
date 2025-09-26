#include <catch2/catch_all.hpp>
#include "app/state/LayoutStore.hpp"
#include "TestHelpers.hpp"

// Implemented coverage:
//  - saveLayoutToFile writes a file (headless ImGui context)
//  - loadLayoutFromFile returns false on missing file
//  - loadLayoutFromFile succeeds after save
//  - resetLayoutToDefault does not crash (state reset smoke test)
// (Rules: TEST-01, TEST-03)

#include <imgui.h>
#include <filesystem>

namespace fs = std::filesystem;

using app::state::LayoutStore;

struct ImGuiContextScope {
    ImGuiContext* prev { nullptr };
    ImGuiContext* ctx { nullptr };
    ImGuiContextScope(){
        prev = ImGui::GetCurrentContext();
        IMGUI_CHECKVERSION();
        ctx = ImGui::CreateContext();
        ImGui::SetCurrentContext(ctx);
    }
    ~ImGuiContextScope(){
        ImGui::SetCurrentContext(prev);
        ImGui::DestroyContext(ctx);
    }
};

TEST_CASE("LayoutStore save/load cycle", "[layout]") {
    ImGuiContextScope scope; // create isolated context
    LayoutStore store(scope.ctx);
    auto tmp = testhelpers::uniqueTempFile("layout_", ".ini");
    REQUIRE_FALSE(fs::exists(tmp));
    REQUIRE(store.saveLayoutToFile(tmp.string()));
    REQUIRE(fs::exists(tmp));
    REQUIRE(store.loadLayoutFromFile(tmp.string()));
}

TEST_CASE("LayoutStore missing file load fails", "[layout]") {
    ImGuiContextScope scope;
    LayoutStore store(scope.ctx);
    auto missing = testhelpers::uniqueTempFile("missing_", ".ini");
    // Ensure file truly does not exist
    if (fs::exists(missing)) fs::remove(missing);
    REQUIRE_FALSE(store.loadLayoutFromFile(missing.string()));
}

TEST_CASE("LayoutStore resetLayoutToDefault smoke", "[layout]") {
    ImGuiContextScope scope;
    LayoutStore store(scope.ctx);
    // Save initial
    auto tmp = testhelpers::uniqueTempFile("layout_reset_", ".ini");
    REQUIRE(store.saveLayoutToFile(tmp.string()));
    // Perform reset (no direct observable state; ensure no crash and subsequent save still works)
    store.resetLayoutToDefault();
    REQUIRE(store.saveLayoutToFile(tmp.string()));
}

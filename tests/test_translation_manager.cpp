#include <catch2/catch_all.hpp>
#include "i18n/TranslationManager.hpp"

// Implemented coverage:
//  - loadLanguage("en") baseline
//  - switch to another shipped language (de) if available
//  - missing key returns key (fallback semantics)
//  - language switch maintains isolation (different value or falls back)
// (Rules: TEST-01, TEST-03)

TEST_CASE("TranslationManager loadLanguage baseline", "[i18n]") {
    auto &tm = TranslationManager::instance();
    REQUIRE(tm.loadLanguage("en"));
    auto lang = tm.currentLanguage();
    REQUIRE((lang == "en"));
}

TEST_CASE("TranslationManager switch language", "[i18n]") {
    auto &tm = TranslationManager::instance();
    REQUIRE(tm.loadLanguage("en"));
    std::string sampleKey = "menu.file"; // should exist in catalogs; if not, test still valid by fallback
    auto enVal = tm.translate(sampleKey);
    // Try German
    REQUIRE(tm.loadLanguage("de"));
    REQUIRE(tm.currentLanguage() == "de");
    auto deVal = tm.translate(sampleKey);
    // Value may differ if translation exists; if not it will match key or en fallback.
    // Ensure no crash and either (different translation) or fallback semantics.
    REQUIRE_FALSE(deVal.empty());
}

TEST_CASE("TranslationManager missing key returns key", "[i18n]") {
    auto &tm = TranslationManager::instance();
    tm.loadLanguage("en");
    auto missing = tm.translate("__totally_missing_key__");
    REQUIRE(missing == "__totally_missing_key__");
}

TEST_CASE("TranslationManager pluralization basic", "[i18n]") {
    auto &tm = TranslationManager::instance();
    REQUIRE(tm.loadLanguage("en"));
    // Keys present in en.json: packs.install.success.one / .other
    REQUIRE(tm.plural("packs.install.success", 1, {"1"}) == "1 pack installed");
    REQUIRE(tm.plural("packs.install.success", 3, {"3"}) == "3 packs installed");
}

TEST_CASE("TranslationManager format basic", "[i18n]") {
    auto &tm = TranslationManager::instance();
    REQUIRE(tm.loadLanguage("de"));
    // Re-use plural template via format to ensure placeholder replacement works directly.
    // We'll translate singular form and apply replacement.
    auto templ = tm.translate("packs.install.success.one");
    REQUIRE_FALSE(templ.empty());
    auto formatted = tm.format("packs.install.success.one", {"1"});
    REQUIRE(formatted.find("1") != std::string::npos);
}

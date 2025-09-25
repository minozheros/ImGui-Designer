#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include <mutex>
#include <optional>

// Lightweight translation manager supporting en + de baseline and extensible catalogs.
class TranslationManager {
public:
    static TranslationManager &instance();

    bool loadLanguage(const std::string &lang); // Attempts lang, falls back to en
    std::string translate(const std::string &key) const; // Returns key if missing
    std::string format(const std::string &key, const std::vector<std::string> &args) const;
    std::string plural(const std::string &baseKey, int count, const std::vector<std::string> &args = {} ) const;

    // Register additional JSON catalog file for a language (absolute or relative path)
    void addCatalogPath(const std::string &lang, const std::string &path);

    const std::string &currentLanguage() const { return currentLang_; }

private:
    TranslationManager() = default;
    bool reload(const std::string &lang);
    bool loadFileInto(const std::string &lang, const std::string &path, std::unordered_map<std::string, std::string> &into);
    static std::string selectPluralForm(const std::string &baseKey, int count);
    static std::string applyArgs(const std::string &templ, const std::vector<std::string> &args);

    std::string currentLang_ = "en";
    std::unordered_map<std::string, std::vector<std::string>> langFiles_; // lang -> file list
    std::unordered_map<std::string, std::string> activeMap_;              // merged map for current language
    mutable std::mutex mutex_;
};

// Convenience macros (avoid collisions with other TR macros if any later)
#define TR(key) TranslationManager::instance().translate(key)

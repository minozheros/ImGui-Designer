#include "i18n/TranslationManager.hpp"
#include <nlohmann/json.hpp>
#include <fstream>
#include <spdlog/spdlog.h>
#include <filesystem>

TranslationManager &TranslationManager::instance()
{
    static TranslationManager inst;
    return inst;
}

void TranslationManager::addCatalogPath(const std::string &lang, const std::string &path)
{
    std::scoped_lock lock(mutex_);
    langFiles_[lang].push_back(path);
    if (lang == currentLang_)
    {
        reload(lang);
    }
}

bool TranslationManager::loadLanguage(const std::string &lang)
{
    std::scoped_lock lock(mutex_);
    std::string tryLang = lang;
    if (!reload(tryLang))
    {
        spdlog::warn("Translation: failed to load language '{}' – falling back to 'en'", tryLang);
        tryLang = "en";
        if (!reload(tryLang))
        {
            spdlog::error("Translation: failed to load fallback language 'en'");
            return false;
        }
    }
    currentLang_ = tryLang;
    return true;
}

bool TranslationManager::reload(const std::string &lang)
{
    activeMap_.clear();
    // Merge all files registered for that lang
    auto it = langFiles_.find(lang);
    if (it == langFiles_.end())
    {
        // If no explicit file registered, try default i18n/<lang>.json
        std::filesystem::path p = std::filesystem::path("i18n") / (lang + ".json");
        if (!std::filesystem::exists(p))
        {
            return false;
        }
        std::unordered_map<std::string, std::string> tmp;
        if (!loadFileInto(lang, p.string(), tmp))
            return false;
        activeMap_ = std::move(tmp);
        return true;
    }
    std::unordered_map<std::string, std::string> merged;
    for (const auto &f : it->second)
    {
        std::unordered_map<std::string, std::string> tmp;
        if (loadFileInto(lang, f, tmp))
        {
            merged.insert(tmp.begin(), tmp.end()); // later files can override earlier ones
        }
        else
        {
            spdlog::warn("Translation: failed to load catalog '{}' for '{}'", f, lang);
        }
    }
    activeMap_ = std::move(merged);
    return !activeMap_.empty();
}

bool TranslationManager::loadFileInto(const std::string &lang, const std::string &path, std::unordered_map<std::string, std::string> &into)
{
    (void)lang;
    std::ifstream ifs(path);
    if (!ifs.is_open())
        return false;
    try
    {
        nlohmann::json j;
        ifs >> j;
        if (!j.is_object())
            return false;
        for (auto it = j.begin(); it != j.end(); ++it)
        {
            if (it.value().is_string())
                into[it.key()] = it.value().get<std::string>();
        }
        return true;
    }
    catch (const std::exception &e)
    {
        spdlog::error("Translation: exception parsing '{}' : {}", path, e.what());
        return false;
    }
}

std::string TranslationManager::translate(const std::string &key) const
{
    std::scoped_lock lock(mutex_);
    auto it = activeMap_.find(key);
    if (it != activeMap_.end())
        return it->second;
    if (currentLang_ != "en")
    {
        // Fallback attempt to English
        auto engFilesIt = langFiles_.find("en");
        if (engFilesIt != langFiles_.end())
        {
            for (const auto &f : engFilesIt->second)
            {
                std::ifstream ifs(f);
                if (ifs.is_open())
                {
                    try
                    {
                        nlohmann::json j;
                        ifs >> j;
                        if (j.contains(key) && j[key].is_string())
                            return j[key].get<std::string>();
                    }
                    catch (...)
                    {
                    }
                }
            }
        }
        else
        {
            // Try default en.json
            std::filesystem::path p = std::filesystem::path("i18n") / "en.json";
            if (std::filesystem::exists(p))
            {
                std::ifstream ifs(p);
                if (ifs.is_open())
                {
                    try
                    {
                        nlohmann::json j;
                        ifs >> j;
                        if (j.contains(key) && j[key].is_string())
                            return j[key].get<std::string>();
                    }
                    catch (...)
                    {
                    }
                }
            }
        }
    }
    // Return key as ultimate fallback
    return key;
}

std::string TranslationManager::applyArgs(const std::string &templ, const std::vector<std::string> &args)
{
    std::string out = templ;
    for (size_t i = 0; i < args.size(); ++i)
    {
        std::string needle = "{" + std::to_string(i) + "}";
        size_t pos = 0;
        while ((pos = out.find(needle, pos)) != std::string::npos)
        {
            out.replace(pos, needle.size(), args[i]);
            pos += args[i].size();
        }
    }
    return out;
}

std::string TranslationManager::format(const std::string &key, const std::vector<std::string> &args) const
{
    return applyArgs(translate(key), args);
}

std::string TranslationManager::selectPluralForm(const std::string &baseKey, int count)
{
    // English & German: singular when count == 1 else plural other
    if (count == 1)
        return baseKey + ".one";
    return baseKey + ".other";
}

std::string TranslationManager::plural(const std::string &baseKey, int count, const std::vector<std::string> &args) const
{
    auto key = selectPluralForm(baseKey, count);
    auto withCountArgs = args;
    if (withCountArgs.empty())
        withCountArgs.push_back(std::to_string(count));
    return applyArgs(translate(key), withCountArgs);
}

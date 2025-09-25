#pragma once
#include <string>
#include "i18n/TranslationManager.hpp"

// Placeholder for future integration: called when a pack is installed to register translation catalogs.
inline void registerPackTranslations(const std::string &language, const std::string &catalogPath)
{
    TranslationManager::instance().addCatalogPath(language, catalogPath);
}

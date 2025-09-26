
#pragma once
#include <nlohmann/json.hpp>
#include <fstream>
#include <string>
#include "spdlog/spdlog.h"

class Preferences
{
public:
    // Allow direct JSON-style access: prefs["main"]["window_width"]
    nlohmann::json &operator[](const std::string &key) { return data_[key]; }
    const nlohmann::json &operator[](const std::string &key) const { return data_.at(key); }

    Preferences(const std::string &path) : path_(path)
    {
        if (!std::filesystem::exists(path))
        {
            spdlog::error("Preferences file not found: {}", path);
            // Optionally: throw std::runtime_error("Config file not found");
            return;
        }
        load();
    }

    // Safe nested access: prefs.safe_get({"main", "window_x"}, 100)
    template <typename T>
    T safe_get(const std::vector<std::string> &keys, const T &default_value) const
    {
        const nlohmann::json *ptr = &data_;
        for (const auto &key : keys)
        {
            if (!ptr->contains(key))
                return default_value;
            ptr = &(*ptr)[key];
        }
        if (ptr->is_null())
            return default_value;
        // Enforce strict type matching to avoid implicit conversions (e.g. bool -> int)
        try {
            // For integral T we accept only true integer JSON types (explicitly reject booleans)
            if constexpr (std::is_same_v<T, int>) {
                if (!ptr->is_number_integer()) return default_value; // excludes bool already
            } else if constexpr (std::is_same_v<T, double> || std::is_same_v<T, float>) {
                // Accept any numeric (integer or floating) but not boolean
                if (!ptr->is_number()) return default_value;
            } else if constexpr (std::is_same_v<T, bool>) {
                if (!ptr->is_boolean()) return default_value;
            } else if constexpr (std::is_same_v<T, std::string>) {
                if (!ptr->is_string()) return default_value;
            }
            // Perform the extraction (will throw if incompatible)
            return ptr->get<T>();
        } catch (...) {
            return default_value;
        }
    }

    // Simple get with default: prefs.get("fps_limit", 30)
    template <typename T>
    T get(const std::string &key, const T &default_value) const
    {
        if (data_.contains(key))
        {
            return data_.at(key).get<T>();
        }
        return default_value;
    }

    // Simple get: prefs.get("fps_limit")
    template <typename T>
    T get(const std::string &key) const
    {
        if (data_.contains(key))
        {
            return data_.at(key).get<T>();
        }
        throw std::runtime_error("Key not found");
    }

    template <typename T>
    void set(const std::string &key, const T &value)
    {
        data_[key] = value;
    }

    void save() const
    {
        std::ofstream ofs(path_);
        ofs << data_.dump(4);
    }

    void load()
    {
        std::ifstream ifs(path_);
        if (ifs)
        {
            try
            {
                ifs >> data_;
                spdlog::info("Loaded preferences from {}", path_);
            }
            catch (const nlohmann::json::parse_error &)
            {
                // Malformed JSON, use empty/default config
                data_ = nlohmann::json::object();
            }
        }
    }

private:
    std::string path_;
    nlohmann::json data_;
};
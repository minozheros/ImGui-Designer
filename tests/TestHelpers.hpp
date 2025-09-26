#pragma once
#include <filesystem>
#include <string>
#include <cstdlib>
#include <fstream>

// Lightweight shared helpers for tests (avoid external deps). Aligns with TEST-01/TEST-03.
// Keep header-only for simplicity. Avoid heavy abstractions.

namespace testhelpers {
    namespace fs = std::filesystem;

    inline fs::path tempDir(const std::string &scope = "") {
        auto base = fs::temp_directory_path() / "imgui_designer_tests";
        if(!fs::exists(base)) fs::create_directories(base);
        if(!scope.empty()) {
            auto scoped = base / scope;
            fs::create_directories(scoped);
            return scoped;
        }
        return base;
    }

    inline fs::path uniqueTempFile(const std::string &prefix, const std::string &ext = ".tmp") {
        auto dir = tempDir("files");
        for(int i=0;i<10000;++i){
            auto cand = dir / (prefix + std::to_string(std::rand()) + ext);
            if(!fs::exists(cand)) return cand;
        }
        return dir / (prefix + "fallback" + ext);
    }

    inline void writeFile(const fs::path &p, const std::string &content = "") {
        auto parent = p.parent_path();
        if(!parent.empty() && !fs::exists(parent)) fs::create_directories(parent);
        std::ofstream o(p.string(), std::ios::binary);
        o << content;
    }

    inline void cleanupTempRoot() {
        auto root = tempDir();
        if(fs::exists(root)) {
            std::error_code ec; fs::remove_all(root, ec); (void)ec;
        }
    }
}

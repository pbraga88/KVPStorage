#pragma once

#include <cstdlib>
#include <filesystem>
#include <string>

inline std::string resolve_storage_path() {
    // 1. environment variable
    if (const char* env = std::getenv("KVP_STORAGE_PATH")) {
        return std::string(env);
    }

    // 2. Desktop fallback
    if (const char* home = std::getenv("HOME")) {
        return std::string(home) + "/.config/kvpstorage/kvpstorage.secure";
    }

    // 3. Embedded fallback
    return "/var/lib/kvpstorage/kvpstorage.secure";
}

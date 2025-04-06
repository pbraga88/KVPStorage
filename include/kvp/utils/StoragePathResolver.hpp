
/**
 * @brief Resolves the storage path for the KVP storage system.
 *
 * This function determines the appropriate storage path based on the following
 * priority order:
 * 
 * 1. If the environment variable `KVP_STORAGE_PATH` is set, its value is used
 *    as the storage path.
 * 2. If the `KVP_STORAGE_PATH` environment variable is not set, the function
 *    falls back to a default path under the user's home directory:
 *    `~/.config/kvpstorage/kvpstorage.secure`. This requires the `HOME`
 *    environment variable to be set.
 * 3. If neither of the above conditions are met, the function defaults to
 *    `/var/lib/kvpstorage/kvpstorage.secure`, which is suitable for embedded
 *    or system-wide storage.
 *
 * @return A string representing the resolved storage path.
 */
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


/**
 * @class KeyLoader
 * @brief Utility class for loading encryption and HMAC keys from files.
 *
 * This class provides functionality to load encryption and HMAC keys
 * from predefined file paths. The file paths can be resolved using
 * environment variables or default locations.
 */
#pragma once

#include <array>
#include <fstream>
#include <stdexcept>
#include <string>
#include <filesystem>
#include <cstdlib>

class KeyLoader {
public:
    static constexpr size_t KEY_SIZE = 32;
    using Key = std::array<uint8_t, KEY_SIZE>;

    /**
     * @brief Loads the encryption key from the specified file.
     *
     * This function attempts to load the encryption key from a file located at
     * the resolved key path. If the file cannot be opened or the key size is invalid,
     * an exception is thrown.
     *
     * @return The loaded encryption key.
     */
    static Key load_encryption_key() {
        return load_key(resolve_key_path() + "/kvpstorage.key");
    }

    /**
     * @brief Loads the HMAC key from the specified file.
     *
     * This function attempts to load the HMAC key from a file located at
     * the resolved key path. If the file cannot be opened or the key size is invalid,
     * an exception is thrown.
     *
     * @return The loaded HMAC key.
     */
    static Key load_hmac_key() {
        return load_key(resolve_key_path() + "/kvpstorage.hmac");
    }

private:
    /**
     * @brief Loads a key from the specified file path.
     *
     * This function reads the key from the given file path and returns it as a Key object.
     * If the file cannot be opened or the key size is invalid, an exception is thrown.
     *
     * @param path The path to the key file.
     * @return The loaded key.
     */
    static Key load_key(const std::string& path) {
        std::ifstream file(path, std::ios::binary);
        if (!file.is_open()) {
            throw std::runtime_error("Error opening file containing the key: " + path);
        }

        Key key;
        file.read(reinterpret_cast<char*>(key.data()), KEY_SIZE);
        if (file.gcount() != KEY_SIZE) {
            throw std::runtime_error("Invalid key size in file: " + path);
        }

        return key;
    }

    /**
     * @brief Resolves the key path based on environment variables or default locations.
     *
     * This function checks for the presence of the KVP_KEYS_PATH environment variable.
     * If it is not set, it falls back to the user's home directory or a default system path.
     *
     * @return The resolved key path as a string.
     */
    static std::string resolve_key_path() {
        if (const char* env = std::getenv("KVP_KEYS_PATH")) {
            return std::string(env);
        }

        if (const char* home = std::getenv("HOME")) {
            return std::string(home) + "/.config/kvpstorage/keys";
        }

        return "/etc/kvpstorage/keys";
    }
};

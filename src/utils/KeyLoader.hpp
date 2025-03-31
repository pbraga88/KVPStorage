#pragma once

#include <array>
#include <fstream>
#include <stdexcept>
#include <string>

class KeyLoader {
public:
    static constexpr size_t KEY_SIZE = 32;

    using Key = std::array<uint8_t, KEY_SIZE>;

    static Key load_key(const std::string& path) {
        std::ifstream file(path, std::ios::binary);
        if (!file.is_open()) {
            throw std::runtime_error("Error opening file containing the key: " + path);
        }

        Key key;
        file.read(reinterpret_cast<char*>(key.data()), KEY_SIZE);

        if (file.gcount() != KEY_SIZE) {
            throw std::runtime_error("Wrong size: " + path);
        }

        return key;
    }

    static Key load_encryption_key() {
        return load_key("keys/kvpstorage.key");
    }

    static Key load_hmac_key() {
        return load_key("keys/kvpstorage.hmac");
    }
};

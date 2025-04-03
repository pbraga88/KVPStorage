#include "storage/FileKVStorage.hpp"

#include <fstream>
#include <sodium.h>
#include <vector>
#include <stdexcept>

FileKVStorage::FileKVStorage(const std::string& path)
    : file_path_(path),
      encryption_key_(KeyLoader::load_encryption_key()),
      hmac_key_(KeyLoader::load_hmac_key()) {
    sodium_init();
    load_storage();
}

void FileKVStorage::set(const std::string& key, const std::string& value) {
    kv_store_[key] = value;
    save_storage();
}

std::optional<std::string> FileKVStorage::get(const std::string& key) {
    auto it = kv_store_.find(key);
    if (it != kv_store_.end())
        return it->second;
    return std::nullopt;
}

void FileKVStorage::del(const std::string& key) {
    kv_store_.erase(key);
    save_storage();
}

void FileKVStorage::load_storage() {
    std::filesystem::create_directories(std::filesystem::path(file_path_).parent_path());
    // std::ifstream file(file_path_, std::ios::binary);

    if (!std::filesystem::exists(file_path_)) {
        // Arquivo ainda não existe: primeira execução.
        kv_store_.clear();
        return;
    }
    std::ifstream file(file_path_, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open storage file.");
    }

    unsigned char nonce[crypto_secretbox_NONCEBYTES];
    file.read(reinterpret_cast<char*>(nonce), sizeof nonce);

    unsigned char hmac_stored[crypto_auth_hmacsha256_BYTES];
    file.read(reinterpret_cast<char*>(hmac_stored), sizeof hmac_stored);

    std::vector<unsigned char> ciphertext((std::istreambuf_iterator<char>(file)),
                                          std::istreambuf_iterator<char>());

    if (crypto_auth_hmacsha256_verify(hmac_stored, ciphertext.data(), ciphertext.size(), hmac_key_.data()) != 0) {
        throw std::runtime_error("HMAC signature not valid.");
    }

    std::vector<unsigned char> decrypted(ciphertext.size() - crypto_secretbox_MACBYTES);
    if (crypto_secretbox_open_easy(decrypted.data(), ciphertext.data(), ciphertext.size(), nonce, encryption_key_.data()) != 0) {
        throw std::runtime_error("File decrypt error.");
    }

    std::string json_str(decrypted.begin(), decrypted.end());
    auto json = nlohmann::json::parse(json_str);

    kv_store_.clear();
    for (auto& [k, v] : json.items()) {
        kv_store_[k] = v.get<std::string>();
    }
}

void FileKVStorage::save_storage() {
    nlohmann::json json(kv_store_);
    std::string plain_data = json.dump();

    unsigned char nonce[crypto_secretbox_NONCEBYTES];
    randombytes_buf(nonce, sizeof nonce);

    std::vector<unsigned char> ciphertext(plain_data.size() + crypto_secretbox_MACBYTES);
    crypto_secretbox_easy(ciphertext.data(),
                          reinterpret_cast<const unsigned char*>(plain_data.data()),
                          plain_data.size(),
                          nonce,
                          encryption_key_.data());

    unsigned char hmac[crypto_auth_hmacsha256_BYTES];
    crypto_auth_hmacsha256(hmac, ciphertext.data(), ciphertext.size(), hmac_key_.data());

    std::ofstream file(file_path_, std::ios::binary | std::ios::trunc);
    file.write(reinterpret_cast<char*>(nonce), sizeof nonce);
    file.write(reinterpret_cast<char*>(hmac), sizeof hmac);
    file.write(reinterpret_cast<char*>(ciphertext.data()), ciphertext.size());
}

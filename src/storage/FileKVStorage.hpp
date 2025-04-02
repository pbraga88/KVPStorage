#pragma once

#include "IKVStorage.hpp"
#include "utils/KeyLoader.hpp"
#include "third_party/nlohmann/json.hpp"

#include <map>
#include <optional>
#include <string>

class FileKVStorage : public IKVStorage {
public:
    explicit FileKVStorage(const std::string& path);

    void set(const std::string& key, const std::string& value) override;
    std::optional<std::string> get(const std::string& key) override;
    void del(const std::string& key) override;

private:
    std::string file_path_;
    KeyLoader::Key encryption_key_;
    KeyLoader::Key hmac_key_;
    std::map<std::string, std::string> kv_store_;

    void load_storage();
    void save_storage();
};

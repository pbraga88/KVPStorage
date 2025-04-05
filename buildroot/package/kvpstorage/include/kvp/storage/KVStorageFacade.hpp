#pragma once

#include <kvp/storage/IKVStorage.hpp>
#include <memory>
#include <optional>
#include <string>

class KVStorageFacade {
public:
    explicit KVStorageFacade(std::unique_ptr<IKVStorage> storage);

    void set(const std::string& key, const std::string& value);
    std::optional<std::string> get(const std::string& key);
    void del(const std::string& key);

private:
    std::unique_ptr<IKVStorage> storage_;
};

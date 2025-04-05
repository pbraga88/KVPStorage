/**
 * @brief A fake storage class for testing purposes.
 *
 * This class implements the IKVStorage interface and provides a simple in-memory
 * key-value store using a map. It is used for unit testing the KVStorageFacade
 * and CommandProcessor classes.
 */
#pragma once

#include "kvp/storage/IKVStorage.hpp"
#include <map>
#include <optional>
#include <string>

class FakeStorage : public IKVStorage {
public:
    void set(const std::string& key, const std::string& value) override {
        data_[key] = value;
    }

    std::optional<std::string> get(const std::string& key) override {
        auto it = data_.find(key);
        return it != data_.end() ? std::optional(it->second) : std::nullopt;
    }

    void del(const std::string& key) override {
        data_.erase(key);
    }

private:
    std::map<std::string, std::string> data_;
};

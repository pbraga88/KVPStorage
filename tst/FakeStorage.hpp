#pragma once

#include "storage/IKVStorage.hpp"
#include <map>
#include <optional>
#include <string>

// Implementação fake de IKVStorage (sem I/O, sem criptografia)
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

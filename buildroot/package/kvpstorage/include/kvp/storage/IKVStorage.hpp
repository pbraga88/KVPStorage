
/**
 * @class IKVStorage
 * @brief Interface for a key-value pair storage system.
 *
 * This interface defines the basic operations for a key-value storage system,
 * including setting, retrieving, and deleting key-value pairs.
 */
#pragma once

#include <optional>
#include <string>

class IKVStorage {
public:
    virtual ~IKVStorage() = default;

    virtual void set(const std::string& key, const std::string& value) = 0;
    virtual std::optional<std::string> get(const std::string& key) = 0;
    virtual void del(const std::string& key) = 0;
};


/**
 * @class KVStorageFacade
 * @brief A facade class for interacting with a key-value storage system.
 *
 * This class provides a simplified interface for performing basic operations
 * (set, get, delete) on a key-value storage system. It delegates the actual
 * storage operations to an implementation of the IKVStorage interface.
 */
#pragma once

#include <kvp/storage/IKVStorage.hpp>
#include <memory>
#include <optional>
#include <string>

class KVStorageFacade {
public:
    /**
     * @brief Constructs a KVStorageFacade object with the specified storage implementation.
     *
     * This constructor initializes the facade with a specific key-value storage implementation.
     *
     * @param storage A unique pointer to an IKVStorage implementation.
     */
    explicit KVStorageFacade(std::unique_ptr<IKVStorage> storage);

    /**
     * @brief Sets a key-value pair in the storage.
     *
     * This method stores the specified key and its associated value in the storage.
     * If the key already exists, its value will be updated to the new value.
     *
     * @param key The key to be stored or updated.
     * @param value The value to be associated with the key.
     */
    void set(const std::string& key, const std::string& value);
    
    /**
     * @brief Retrieves the value associated with a specified key.
     *
     * This method looks up the given key in the storage and returns its associated value.
     * If the key does not exist, an empty optional is returned.
     *
     * @param key The key whose associated value is to be retrieved.
     * @return An optional containing the value if found, or an empty optional if not found.
     */
    std::optional<std::string> get(const std::string& key);
    
    /**
     * @brief Deletes a key-value pair from the storage.
     *
     * This method removes the specified key and its associated value from the storage.
     * If the key does not exist, no action is taken.
     *
     * @param key The key to be deleted from the storage.
     */
    void del(const std::string& key);

private:
    std::unique_ptr<IKVStorage> storage_;
};

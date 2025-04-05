/**
 * @class KVStorageFacade
 * @brief A facade class that provides a simplified interface for key-value storage operations.
 * 
 * This class acts as a wrapper around an implementation of the IKVStorage interface,
 * providing methods to set, get, and delete key-value pairs. It abstracts the underlying
 * storage mechanism, allowing the user to interact with the storage in a consistent manner.
 * 
 * @note The ownership of the storage implementation is transferred to the KVStorageFacade
 *       upon construction.
 * 
 * @details
 * - `set`: Stores a key-value pair in the storage.
 * - `get`: Retrieves the value associated with a given key, if it exists.
 * - `del`: Deletes a key-value pair from the storage.
 * 
 * @see IKVStorage
 */
#include <kvp/storage/KVStorageFacade.hpp>

/**
 * @brief Constructs a KVStorageFacade object with the given storage implementation.
 * 
 * @param storage A unique pointer to an object implementing the IKVStorage interface.
 *                This object will be used to perform key-value storage operations.
 *                Ownership of the storage object is transferred to the KVStorageFacade.
 */
KVStorageFacade::KVStorageFacade(std::unique_ptr<IKVStorage> storage)
    : storage_(std::move(storage)) {}

/**
 * @brief Stores a key-value pair in the storage.
 * 
 * This method allows the user to store a value associated with a specific key
 * in the underlying storage system. If the key already exists, its value will
 * be updated.
 * 
 * @param key The key associated with the value to be stored.
 * @param value The value to be stored in the storage system.
 */
void KVStorageFacade::set(const std::string& key, const std::string& value) {
    storage_->set(key, value);
}

/**
 * @brief Retrieves the value associated with the given key from the storage.
 * 
 * This method attempts to fetch the value corresponding to the provided key
 * from the underlying storage. If the key exists, the value is returned
 * wrapped in a std::optional. If the key does not exist, an empty
 * std::optional is returned.
 * 
 * @param key The key whose associated value is to be retrieved.
 * @return std::optional<std::string> The value associated with the key, or
 *         an empty std::optional if the key does not exist.
 */
std::optional<std::string> KVStorageFacade::get(const std::string& key) {
    return storage_->get(key);
}

/**
 * @brief Deletes a key-value pair from the storage.
 * 
 * This method removes the entry associated with the specified key
 * from the underlying storage. If the key does not exist, the behavior
 * depends on the implementation of the underlying storage.
 * 
 * @param key The key of the key-value pair to be deleted.
 */
void KVStorageFacade::del(const std::string& key) {
    storage_->del(key);
}

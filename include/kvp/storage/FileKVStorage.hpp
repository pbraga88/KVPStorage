
/**
 * @class FileKVStorage
 * @brief A key-value storage implementation that persists data to a file.
 *
 * This class provides a file-based implementation of the IKVStorage interface.
 * It allows storing, retrieving, and deleting key-value pairs, with the data
 * being persisted to a file. The storage also supports encryption and HMAC
 * for secure data handling.
 */
#pragma once
#include <kvp/storage/IKVStorage.hpp>
#include <kvp/utils/KeyLoader.hpp>
#include <nlohmann/json.hpp>

#include <map>
#include <optional>
#include <string>

class FileKVStorage : public IKVStorage {
public:
    /**
     * @brief Constructs a FileKVStorage object with the specified file path.
     * 
     * This constructor initializes the key-value storage system by associating it
     * with a file located at the given path. The file is used to persistently store
     * key-value pairs.
     * 
     * @param path The file path where the key-value storage data will be stored or loaded from.
     */
    explicit FileKVStorage(const std::string& path);

    /**
     * @brief Stores a key-value pair in the storage.
     * 
     * This method associates the specified key with the given value in the storage.
     * If the key already exists, its value will be updated to the new value.
     * 
     * @param key The key to be stored or updated.
     * @param value The value to be associated with the key.
     */
    void set(const std::string& key, const std::string& value) override;

    /**
     * @brief Retrieves the value associated with a specified key.
     * 
     * This method looks up the given key in the storage and returns its associated value.
     * If the key does not exist, an empty optional is returned.
     * 
     * @param key The key whose associated value is to be retrieved.
     * @return An optional containing the value if found, or an empty optional if not found.
     */
    std::optional<std::string> get(const std::string& key) override;

    /**
     * @brief Deletes a key-value pair from the storage.
     * 
     * This method removes the specified key and its associated value from the storage.
     * If the key does not exist, no action is taken.
     * 
     * @param key The key to be deleted from the storage.
     */
    void del(const std::string& key) override;

private:
    std::string file_path_;
    KeyLoader::Key encryption_key_;
    KeyLoader::Key hmac_key_;
    std::map<std::string, std::string> kv_store_;

    /**
     * @brief Loads the key-value pair storage from the underlying file system.
     * 
     * This function is responsible for initializing the storage by reading
     * data from the associated file. It ensures that the storage is populated
     * with the key-value pairs previously saved. If the file does not exist
     * or is inaccessible, the function may handle the error or initialize
     * an empty storage, depending on the implementation.
     * 
     * @throws std::runtime_error If there is an error accessing or reading the file.
     */
    void load_storage();

    /**
     * @brief Saves the current key-value pair storage to the underlying file system.
     * 
     * This function is responsible for securely persisting the current state of the
     * key-value storage to the associated file. It ensures that all key-value
     * pairs are written to the file in a format that can be easily read back
     * during future loads. If there is an error during the write process,
     * appropriate error handling should be performed.
     */
    void save_storage();
};

#include <kvp/storage/KVStorageFacade.hpp>

KVStorageFacade::KVStorageFacade(std::unique_ptr<IKVStorage> storage)
    : storage_(std::move(storage)) {}

void KVStorageFacade::set(const std::string& key, const std::string& value) {
    storage_->set(key, value);
}

std::optional<std::string> KVStorageFacade::get(const std::string& key) {
    return storage_->get(key);
}

void KVStorageFacade::del(const std::string& key) {
    storage_->del(key);
}

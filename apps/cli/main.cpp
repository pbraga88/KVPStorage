#include <kvp/storage/FileKVStorage.hpp>
#include <kvp/storage/KVStorageFacade.hpp>
#include <kvp/commands/CommandProcessor.hpp>
#include <kvp/utils/StoragePathResolver.hpp>

#include "CLI.hpp"
#include <filesystem>
#include <iostream>

int main() {
    try {
        const std::string file_path = resolve_storage_path();
        auto storage = std::make_unique<FileKVStorage>(file_path);

        KVStorageFacade facade(std::move(storage));
        CommandProcessor processor(facade);
        CLI cli(processor);

        cli.run();
    } catch (const std::exception& e) {
        std::cerr << "[ERROR] " << e.what() << "\n";
        return 1;
    }

    return 0;
}

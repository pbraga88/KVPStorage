#include "storage/FileKVStorage.hpp"
#include "storage/KVStorageFacade.hpp"
#include "commands/CommandProcessor.hpp"
#include "cli/CLI.hpp"

#include <filesystem>
#include <iostream>

int main() {
    try {
        const std::string file_path = "kvstore.secure";

        auto storage = std::make_unique<FileKVStorage>(file_path);
        KVStorageFacade facade(std::move(storage));
        CommandProcessor processor(facade);
        CLI cli(processor);

        cli.run();
    } catch (const std::exception& e) {
        std::cerr << "[ERRO] " << e.what() << "\n";
        return 1;
    }

    return 0;
}

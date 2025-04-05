#pragma once

#include <kvp/storage/KVStorageFacade.hpp>
#include <string>
#include <vector>

class CommandProcessor {
public:
    explicit CommandProcessor(KVStorageFacade& storage);

    std::string handle_command(const std::string& input_line);

private:
    KVStorageFacade& storage_;

    std::vector<std::string> tokenize(const std::string& input);
};

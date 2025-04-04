#include "commands/CommandProcessor.hpp"
#include <sstream>
#include <algorithm>

CommandProcessor::CommandProcessor(KVStorageFacade& storage)
    : storage_(storage) {}

std::string CommandProcessor::handle_command(const std::string& input_line) {
    auto tokens = tokenize(input_line);
    if (tokens.empty()) return "";

    const std::string& cmd = tokens[0];

    if (cmd == "SET" && tokens.size() >= 3) {
        std::string key = tokens[1];
        std::string value = input_line.substr(input_line.find(key) + key.length() + 1);
        storage_.set(key, value);
        return "OK";
    }
    else if (cmd == "GET" && tokens.size() == 2) {
        auto result = storage_.get(tokens[1]);
        return result.value_or("");
    }
    else if (cmd == "DELETE" && tokens.size() == 2) {
        storage_.del(tokens[1]);
        return "OK";
    }

    return "Comando inválido";
}

std::vector<std::string> CommandProcessor::tokenize(const std::string& input) {
    std::istringstream iss(input);
    std::vector<std::string> tokens;
    std::string token;
    while (iss >> token) {
        tokens.push_back(token);
    }
    return tokens;
}

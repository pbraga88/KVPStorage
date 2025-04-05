/**
 * @class CommandProcessor
 * @brief Handles the processing of commands and interacts with the key-value storage.
 *
 * The CommandProcessor class is responsible for parsing input commands, delegating
 * operations to the KVStorageFacade, and returning the results as strings.
 */
#pragma once

#include <kvp/storage/KVStorageFacade.hpp>
#include <string>
#include <vector>

class CommandProcessor {
public:
    /**
     * @brief Constructs a CommandProcessor with a reference to a KVStorageFacade.
     * @param storage A reference to the KVStorageFacade instance used for storage operations.
     */
    explicit CommandProcessor(KVStorageFacade& storage);

    /**
     * @brief Processes a command input line and returns the result.
     * @param input_line The input command line to be processed.
     * @return A string containing the result of the command execution.
     */
    std::string handle_command(const std::string& input_line);

private:
    KVStorageFacade& storage_;
    
    /**
     * @brief Tokenizes an input string into a vector of strings.
     * @param input The input string to be tokenized.
     * @return A vector of strings representing the tokens.
     */
    std::vector<std::string> tokenize(const std::string& input);
};

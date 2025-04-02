#include "cli/CLI.hpp"
#include <iostream>
#include <string>

CLI::CLI(CommandProcessor& processor)
    : processor_(processor) {}

void CLI::run() {
    std::string line;
    std::cout << "> ";
    while (std::getline(std::cin, line)) {
        if (line == "exit") break;

        std::string result = processor_.handle_command(line);
        if (!result.empty()) {
            std::cout << result << "\n";
        }

        std::cout << "> ";
    }
    std::cout << "Bye!\n";
}

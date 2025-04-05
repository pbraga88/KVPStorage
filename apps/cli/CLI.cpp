#include "CLI.hpp"
#include <string>

CLI::CLI(CommandProcessor& processor, std::istream& in, std::ostream& out)
    : processor_(processor), in_(in), out_(out) {}

void CLI::run() {
    std::string line;
    out_ << "> ";
    while (std::getline(in_, line)) {
        if (line == "exit") break;

        std::string result = processor_.handle_command(line);
        if (!result.empty()) {
            out_ << result << "\n";
        }

        out_ << "> ";
    }
    out_ << "Bye!\n";
}

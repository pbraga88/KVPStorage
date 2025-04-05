#pragma once

#include <kvp/commands/CommandProcessor.hpp>
#include <istream>
#include <ostream>
#include <iostream>

class CLI {
public:
    CLI(CommandProcessor& processor, std::istream& in = std::cin, std::ostream& out = std::cout);

    void run();

private:
    CommandProcessor& processor_;
    std::istream& in_;
    std::ostream& out_;
};

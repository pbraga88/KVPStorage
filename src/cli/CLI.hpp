#pragma once

#include "commands/CommandProcessor.hpp"

class CLI {
public:
    explicit CLI(CommandProcessor& processor);
    void run();  // Inicia o loop de entrada interativa

private:
    CommandProcessor& processor_;
};

/**
 * @class CLI
 * @brief A command-line interface (CLI) class for interacting with the CommandProcessor.
 *
 * This class provides a simple interface for reading commands from an input stream,
 * processing them using a CommandProcessor, and outputting the results to an output stream.
 *
 * @note The default input and output streams are set to `std::cin` and `std::cout`, respectively.
 */
 
 #pragma once

 #include <kvp/commands/CommandProcessor.hpp>
 #include <istream>
 #include <ostream>
 #include <iostream>
 
 class CLI {
 public:
     /**
      * @brief Constructs a CLI (Command Line Interface) object.
      * 
      * @param processor Reference to a CommandProcessor object used to handle commands.
      * @param in Input stream for reading user input (default is std::cin).
      * @param out Output stream for writing responses or messages (default is std::cout).
      */
     CLI(CommandProcessor& processor, std::istream& in = std::cin, std::ostream& out = std::cout);
 
     /**
      * @brief Executes the main logic of the CLI application.
      * 
      * This function is responsible for running the command-line interface,
      * processing user input, and performing the necessary operations based
      * on the provided commands and arguments.
      */
     void run();
 
 private:
     CommandProcessor& processor_;
     std::istream& in_;
     std::ostream& out_;
 };
 
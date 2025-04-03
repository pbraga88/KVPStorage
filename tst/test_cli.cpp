#include "gtest/gtest.h"
#include "cli/CLI.hpp"
#include "storage/KVStorageFacade.hpp"
#include "FakeStorage.hpp"

#include <sstream>

TEST(CliTest, SimpleSession) {
    auto fake = std::make_unique<FakeStorage>();
    KVStorageFacade facade(std::move(fake));
    CommandProcessor processor(facade);

    std::istringstream input(
        "SET foo bar\n"
        "GET foo\n"
        "DELETE foo\n"
        "GET foo\n"
        "exit\n"
    );

    std::ostringstream output;
    CLI cli(processor, input, output);
    cli.run();

    std::string result = output.str();

    // Verificações básicas
    EXPECT_NE(result.find("OK"), std::string::npos);
    EXPECT_NE(result.find("bar"), std::string::npos);
    EXPECT_NE(result.find("Bye!"), std::string::npos);
}

TEST(CliTest, InvalidCommand) {
    auto fake = std::make_unique<FakeStorage>();
    KVStorageFacade facade(std::move(fake));
    CommandProcessor processor(facade);

    std::istringstream input(
        "SET foo\n"
        "exit\n"
    );

    std::ostringstream output;
    CLI cli(processor, input, output);
    cli.run();

    std::string result = output.str();

    // Verificações básicas
    EXPECT_NE(result.find("Comando inválido"), std::string::npos);
}

TEST(CliTest, MultipleCommands) {
    auto fake = std::make_unique<FakeStorage>();
    KVStorageFacade facade(std::move(fake));
    CommandProcessor processor(facade);

    std::istringstream input(
        "SET key1 value1\n"
        "SET key2 value2\n"
        "GET key1\n"
        "GET key2\n"
        "DELETE key1\n"
        "GET key1\n"
        "exit\n"
    );

    std::ostringstream output;
    CLI cli(processor, input, output);
    cli.run();

    std::string result = output.str();

    // Verificações básicas
    EXPECT_NE(result.find("OK"), std::string::npos);
    EXPECT_NE(result.find("value1"), std::string::npos);
    EXPECT_NE(result.find("value2"), std::string::npos);
    EXPECT_NE(result.find("Bye!"), std::string::npos);
}

TEST(CliTest, EmptyInput) {
    auto fake = std::make_unique<FakeStorage>();
    KVStorageFacade facade(std::move(fake));
    CommandProcessor processor(facade);

    std::istringstream input(
        "\n"
        "exit\n"
    );

    std::ostringstream output;
    CLI cli(processor, input, output);
    cli.run();

    std::string result = output.str();

    // Verificações básicas
    EXPECT_NE(result.find("Bye!"), std::string::npos);
}

TEST(CliTest, SpecialCharacters) {
    auto fake = std::make_unique<FakeStorage>();
    KVStorageFacade facade(std::move(fake));
    CommandProcessor processor(facade);

    std::istringstream input(
        "SET key !@#$%^&*()\n"
        "GET key\n"
        "exit\n"
    );

    std::ostringstream output;
    CLI cli(processor, input, output);
    cli.run();

    std::string result = output.str();

    // Verificações básicas
    EXPECT_NE(result.find("OK"), std::string::npos);
    EXPECT_NE(result.find("!@#$%^&*()"), std::string::npos);
}
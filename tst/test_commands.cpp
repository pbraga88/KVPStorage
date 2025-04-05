#include "gtest/gtest.h"
#include "kvp/storage/KVStorageFacade.hpp"
#include "kvp/commands/CommandProcessor.hpp"
#include "FakeStorage.hpp"

class CommandProcessorTest : public ::testing::Test {
protected:
    std::unique_ptr<FakeStorage> fake;
    std::unique_ptr<KVStorageFacade> facade;
    std::unique_ptr<CommandProcessor> processor;

    void SetUp() override {
        fake = std::make_unique<FakeStorage>();
        facade = std::make_unique<KVStorageFacade>(std::move(fake));
        processor = std::make_unique<CommandProcessor>(*facade);
    }
};

TEST_F(CommandProcessorTest, SetGetDeleteMultiple) {
    EXPECT_EQ(processor->handle_command("SET language C++"), "OK");
    EXPECT_EQ(processor->handle_command("SET version 20"), "OK");
    EXPECT_EQ(processor->handle_command("SET library STL"), "OK");

    EXPECT_EQ(processor->handle_command("GET language"), "C++");
    EXPECT_EQ(processor->handle_command("GET version"), "20");
    EXPECT_EQ(processor->handle_command("GET library"), "STL");

    EXPECT_EQ(processor->handle_command("DELETE language"), "OK");
    EXPECT_EQ(processor->handle_command("GET language"), "");
}

TEST_F(CommandProcessorTest, BasicSetGetDelete) {
    EXPECT_EQ(processor->handle_command("SET device TestDevice_001"), "OK");
    EXPECT_EQ(processor->handle_command("GET device"), "TestDevice_001");
    EXPECT_EQ(processor->handle_command("DELETE device"), "OK");
    EXPECT_EQ(processor->handle_command("GET device"), "");
}

TEST_F(CommandProcessorTest, SetGetDeleteNonExistent) {
    EXPECT_EQ(processor->handle_command("GET non_existent_key"), "");
    EXPECT_EQ(processor->handle_command("DELETE non_existent_key"), "OK");
    EXPECT_EQ(processor->handle_command("GET non_existent_key"), "");
}

TEST_F(CommandProcessorTest, SetGetDeleteEmptyKey) {
    EXPECT_EQ(processor->handle_command("SET "), "Invalid Command");
    EXPECT_EQ(processor->handle_command("GET "), "Invalid Command");
    EXPECT_EQ(processor->handle_command("DELETE "), "Invalid Command");
}

TEST_F(CommandProcessorTest, SetGetDeleteEmptyValue) {
    EXPECT_EQ(processor->handle_command("SET empty_key "), "Invalid Command");
    EXPECT_EQ(processor->handle_command("GET empty_key"), "");
    EXPECT_EQ(processor->handle_command("DELETE empty_key"), "OK");
    EXPECT_EQ(processor->handle_command("GET empty_key"), "");
}

TEST_F(CommandProcessorTest, SetGetDeleteSpecialChars) {
    EXPECT_EQ(processor->handle_command("SET special_key !@#$%^&*()"), "OK");
    EXPECT_EQ(processor->handle_command("GET special_key"), "!@#$%^&*()");
    EXPECT_EQ(processor->handle_command("DELETE special_key"), "OK");
    EXPECT_EQ(processor->handle_command("GET special_key"), "");
}

TEST_F(CommandProcessorTest, SetGetDeleteLongKeyValue) {
    std::string long_key(1000, 'a');
    std::string long_value(1000, 'b');

    EXPECT_EQ(processor->handle_command("SET " + long_key + " " + long_value), "OK");
    EXPECT_EQ(processor->handle_command("GET " + long_key), long_value);
    EXPECT_EQ(processor->handle_command("DELETE " + long_key), "OK");
    EXPECT_EQ(processor->handle_command("GET " + long_key), "");
}

TEST_F(CommandProcessorTest, SetGetDeleteWithSpaces) {
    EXPECT_EQ(processor->handle_command("SET key with spaces value with spaces"), "Invalid Command");
    EXPECT_EQ(processor->handle_command("GET key with spaces"), "Invalid Command");
    EXPECT_EQ(processor->handle_command("DELETE key with spaces"), "Invalid Command");
    EXPECT_EQ(processor->handle_command("GET key with spaces"), "Invalid Command");
}

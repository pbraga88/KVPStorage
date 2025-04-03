#include "gtest/gtest.h"
#include "storage/KVStorageFacade.hpp"
#include "commands/CommandProcessor.hpp"
#include "FakeStorage.hpp"

TEST(CommandProcessorTest, BasicSetGetDelete) {
    auto fake = std::make_unique<FakeStorage>();
    KVStorageFacade facade(std::move(fake));
    CommandProcessor processor(facade);

    // SET
    std::string result = processor.handle_command("SET device TestDevice_001");
    EXPECT_EQ(result, "OK");

    // GET
    result = processor.handle_command("GET device");
    EXPECT_EQ(result, "TestDevice_001");

    // DELETE
    result = processor.handle_command("DELETE device");
    EXPECT_EQ(result, "OK");

    // GET novamente (espera retorno vazio)
    result = processor.handle_command("GET device");
    EXPECT_EQ(result, "");
}

TEST(CommandProcessorTest, InvalidCommands) {
    auto fake = std::make_unique<FakeStorage>();
    KVStorageFacade facade(std::move(fake));
    CommandProcessor processor(facade);

    EXPECT_EQ(processor.handle_command("SET onlykey"), "Comando inválido");
    EXPECT_EQ(processor.handle_command("GET"), "Comando inválido");
    EXPECT_EQ(processor.handle_command("DELETE"), "Comando inválido");
    EXPECT_EQ(processor.handle_command("RANDOM cmd"), "Comando inválido");
}

TEST(CommandProcessorTest, SetGetDeleteMultiple) {
    auto fake = std::make_unique<FakeStorage>();
    KVStorageFacade facade(std::move(fake));
    CommandProcessor processor(facade);

    // SET
    EXPECT_EQ(processor.handle_command("SET language C++"), "OK");
    EXPECT_EQ(processor.handle_command("SET version 20"), "OK");
    EXPECT_EQ(processor.handle_command("SET library STL"), "OK");

    // GET
    EXPECT_EQ(processor.handle_command("GET language"), "C++");
    EXPECT_EQ(processor.handle_command("GET version"), "20");
    EXPECT_EQ(processor.handle_command("GET library"), "STL");

    // DELETE
    EXPECT_EQ(processor.handle_command("DELETE language"), "OK");
    EXPECT_EQ(processor.handle_command("GET language"), "");
}

TEST(CommandProcessorTest, GetNonExistentKey) {
    auto fake = std::make_unique<FakeStorage>();
    KVStorageFacade facade(std::move(fake));
    CommandProcessor processor(facade);

    EXPECT_EQ(processor.handle_command("GET non_existent_key"), "");
}

TEST(CommandProcessorTest, DeleteNonExistentKey) {
    auto fake = std::make_unique<FakeStorage>();
    KVStorageFacade facade(std::move(fake));
    CommandProcessor processor(facade);

    EXPECT_EQ(processor.handle_command("DELETE non_existent_key"), "OK");
    EXPECT_EQ(processor.handle_command("GET non_existent_key"), "");
}

// TEST(CommandProcessorTest, SetEmptyKey) {
//     auto fake = std::make_unique<FakeStorage>();
//     KVStorageFacade facade(std::move(fake));
//     CommandProcessor processor(facade);

//     EXPECT_EQ(processor.handle_command("SET  value"), "OK");
//     EXPECT_EQ(processor.handle_command("GET "), "value");
// }

// TEST(CommandProcessorTest, SetEmptyValue) {
//     auto fake = std::make_unique<FakeStorage>();
//     KVStorageFacade facade(std::move(fake));
//     CommandProcessor processor(facade);

//     EXPECT_EQ(processor.handle_command("SET key "), "OK");
//     EXPECT_EQ(processor.handle_command("GET key"), "");
// }

// TEST(CommandProcessorTest, SetKeyWithSpaces) {
//     auto fake = std::make_unique<FakeStorage>();
//     KVStorageFacade facade(std::move(fake));
//     CommandProcessor processor(facade);

//     EXPECT_EQ(processor.handle_command("SET key with spaces value"), "OK");
//     EXPECT_EQ(processor.handle_command("GET key with spaces"), "value");
// }
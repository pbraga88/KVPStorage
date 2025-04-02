#include "gtest/gtest.h"
#include "storage/FileKVStorage.hpp"
#include "utils/KeyLoader.hpp"

#include <filesystem>
#include <fstream>

class KVStorageTest : public ::testing::Test {
protected:
    std::string test_file = "test_kvstore.secure";

    void SetUp() override {
        std::filesystem::remove(test_file);
    }

    void TearDown() override {
        std::filesystem::remove(test_file);
    }
};

TEST_F(KVStorageTest, SetGetDeleteKey) {
    FileKVStorage storage(test_file);

    // SET
    storage.set("name", "TestUser");

    // GET
    auto result = storage.get("name");
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result.value(), "TestUser");

    // DELETE
    storage.del("name");
    result = storage.get("name");
    EXPECT_FALSE(result.has_value());
}

#include "gtest/gtest.h"
#include "kvp/storage/KVStorageFacade.hpp"
#include "FakeStorage.hpp"

TEST(FacadeWithFakeTest, SetGetDelete) {
    auto fake = std::make_unique<FakeStorage>();
    KVStorageFacade facade(std::move(fake));

    facade.set("language", "C++");
    auto val = facade.get("language");
    ASSERT_TRUE(val.has_value());
    EXPECT_EQ(val.value(), "C++");

    facade.del("language");
    val = facade.get("language");
    EXPECT_FALSE(val.has_value());
}

TEST(FacadeWithFakeTest, SetGetDeleteMultiple) {
    auto fake = std::make_unique<FakeStorage>();
    KVStorageFacade facade(std::move(fake));

    facade.set("language", "C++");
    facade.set("version", "20");
    facade.set("library", "STL");

    auto lang = facade.get("language");
    ASSERT_TRUE(lang.has_value());
    EXPECT_EQ(lang.value(), "C++");

    auto ver = facade.get("version");
    ASSERT_TRUE(ver.has_value());
    EXPECT_EQ(ver.value(), "20");

    auto lib = facade.get("library");
    ASSERT_TRUE(lib.has_value());
    EXPECT_EQ(lib.value(), "STL");

    facade.del("language");
    lang = facade.get("language");
    EXPECT_FALSE(lang.has_value());
}

TEST(FacadeWithFakeTest, GetNonExistentKey) {
    auto fake = std::make_unique<FakeStorage>();
    KVStorageFacade facade(std::move(fake));

    auto val = facade.get("non_existent_key");
    EXPECT_FALSE(val.has_value());
}

TEST(FacadeWithFakeTest, DeleteNonExistentKey) {
    auto fake = std::make_unique<FakeStorage>();
    KVStorageFacade facade(std::move(fake));

    facade.del("non_existent_key");
    auto val = facade.get("non_existent_key");
    EXPECT_FALSE(val.has_value());
}

TEST(FacadeWithFakeTest, SetEmptyKey) {
    auto fake = std::make_unique<FakeStorage>();
    KVStorageFacade facade(std::move(fake));

    facade.set("", "value");
    auto val = facade.get("");
    ASSERT_TRUE(val.has_value());
    EXPECT_EQ(val.value(), "value");
}

TEST(FacadeWithFakeTest, SetEmptyValue) {
    auto fake = std::make_unique<FakeStorage>();
    KVStorageFacade facade(std::move(fake));

    facade.set("key", "");
    auto val = facade.get("key");
    ASSERT_TRUE(val.has_value());
    EXPECT_EQ(val.value(), "");
}

TEST(FacadeWithFakeTest, SetAndGetSpecialCharacters) {
    auto fake = std::make_unique<FakeStorage>();
    KVStorageFacade facade(std::move(fake));

    facade.set("key", "!@#$%^&*()_+");
    auto val = facade.get("key");
    ASSERT_TRUE(val.has_value());
    EXPECT_EQ(val.value(), "!@#$%^&*()_+");
}

TEST(FacadeWithFakeTest, SetAndGetLongString) {
    auto fake = std::make_unique<FakeStorage>();
    KVStorageFacade facade(std::move(fake));

    std::string long_value(1000, 'a');
    facade.set("long_key", long_value);
    auto val = facade.get("long_key");
    ASSERT_TRUE(val.has_value());
    EXPECT_EQ(val.value(), long_value);
}
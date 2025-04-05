# tst/CMakeLists.txt

include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)

FetchContent_MakeAvailable(googletest)

file(GLOB TEST_SOURCES CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/test_*.cpp
    ${CMAKE_SOURCE_DIR}/apps/cli/CLI.cpp
)

add_executable(unit_tests ${TEST_SOURCES})

target_include_directories(unit_tests PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/apps/cli
    ${CMAKE_SOURCE_DIR}/third_party
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(unit_tests
    gtest_main    
    kvp
)

include(GoogleTest)
gtest_discover_tests(unit_tests)

cmake_minimum_required(VERSION 3.14)
project(KVPStorage)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable CTest for gtest_discover_tests
enable_testing()

# Add subprojects
add_subdirectory(libkvp)
add_subdirectory(apps/cli)
add_subdirectory(tst)

add_custom_target(run_tests
    COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
    DEPENDS unit_tests
)

add_custom_target(default ALL DEPENDS run_tests)
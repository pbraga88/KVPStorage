cmake_minimum_required(VERSION 3.14)
project(KVPStorage)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(src)

enable_testing()
add_subdirectory(tst)

add_custom_target(run_tests
    COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
    DEPENDS unit_tests
)

add_custom_target(default ALL DEPENDS run_tests)

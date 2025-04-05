include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
FetchContent_MakeAvailable(googletest)

file(GLOB TEST_SOURCES CONFIGURE_DEPENDS *.cpp)
add_executable(unit_tests ${TEST_SOURCES})

target_link_libraries(unit_tests
  gtest_main
  kvpstorage
)

include(GoogleTest)
gtest_discover_tests(unit_tests)

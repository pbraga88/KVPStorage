include(FetchContent)

# Baixa o GoogleTest se necessário
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
FetchContent_MakeAvailable(googletest)

# Adiciona os testes
file(GLOB TEST_SOURCES CONFIGURE_DEPENDS *.cpp)

add_executable(unit_tests ${TEST_SOURCES})

target_link_libraries(unit_tests
  gtest_main
  kvpstorage
)

add_custom_command(TARGET unit_tests POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_SOURCE_DIR}/keys/kvpstorage.key
        ${CMAKE_BINARY_DIR}/keys/kvpstorage.key
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_SOURCE_DIR}/keys/kvpstorage.hmac
        ${CMAKE_BINARY_DIR}/keys/kvpstorage.hmac
)

include(GoogleTest)
gtest_discover_tests(unit_tests)

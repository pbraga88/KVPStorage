cmake_minimum_required(VERSION 3.14)
project(KVPStorage)

set(CMAKE_CXX_STANDARD 17)

# Inclui a pasta src como biblioteca
add_subdirectory(src)

# Ativa suporte a testes
enable_testing()
add_subdirectory(tst)

# Roda os testes automaticamente ao executar `make`
add_custom_target(run_tests
    COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
    DEPENDS unit_tests
)

# Define 'run_tests' como alvo padrão
add_custom_target(default ALL DEPENDS run_tests)

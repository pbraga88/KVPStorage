# apps/cli/CMakeLists.txt

file(GLOB_RECURSE CLI_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
)

add_executable(kvpstorage_cli ${CLI_SOURCES})

target_link_libraries(kvpstorage_cli PRIVATE kvp)

target_include_directories(kvpstorage_cli
    PRIVATE
        ${CMAKE_SOURCE_DIR}/include
)

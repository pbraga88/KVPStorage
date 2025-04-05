# libkvp/CMakeLists.txt

file(GLOB_RECURSE LIBKVP_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/commands/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/storage/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/utils/*.cpp"
)

add_library(kvp STATIC ${LIBKVP_SOURCES})

target_include_directories(kvp
    PUBLIC
        ${CMAKE_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/third_party
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

find_package(PkgConfig REQUIRED)
pkg_check_modules(SODIUM REQUIRED libsodium)

target_include_directories(kvp PRIVATE ${SODIUM_INCLUDE_DIRS})
target_link_libraries(kvp PRIVATE ${SODIUM_LIBRARIES})

target_compile_features(kvp PUBLIC cxx_std_17)

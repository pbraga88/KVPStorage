file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS
    *.cpp
)

add_library(kvpstorage STATIC ${SRC_FILES})
target_include_directories(kvpstorage PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(kvpstorage sodium)

add_executable(kvpstorage_host ../src/main.cpp)
target_link_libraries(kvpstorage_host kvpstorage sodium)

# Define onde colocar o binário final
set_target_properties(kvpstorage_host PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
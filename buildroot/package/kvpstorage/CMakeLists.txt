cmake_minimum_required(VERSION 3.14)
project(KVPStorage)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(libkvp)
add_subdirectory(apps/cli)
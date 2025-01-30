cmake_minimum_required(VERSION 3.22)
project(PluginSystem)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

option(PLUGIN_SYSTEM_WITH_SAMPLE "build with sample" ON)

add_subdirectory(sdk)
add_subdirectory(lib)

if(PLUGIN_SYSTEM_WITH_SAMPLE)
    add_subdirectory(sample)
endif()
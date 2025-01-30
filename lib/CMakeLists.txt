file(GLOB_RECURSE PLUGINSYS_SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

add_library(PluginSystemLib_static STATIC ${PLUGINSYS_SRC_FILES})
target_include_directories(PluginSystemLib_static PUBLIC inc/)

target_include_directories(PluginSystemLib_static
        PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/inc>
        $<INSTALL_INTERFACE:$<INSTALL_PREFIX>/${CMAKE_INSTALL_INCLUDEDIR}>
        )

if(WIN32)
    target_compile_definitions(PluginSystemLib_static PRIVATE WIN32_LEAN_AND_MEAN)
endif()

if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 9.0)
    target_link_libraries(PluginSystemLib_static PluginSystemInfrastructures stdc++fs)
else()
    target_link_libraries(PluginSystemLib_static PluginSystemInfrastructures)
endif()


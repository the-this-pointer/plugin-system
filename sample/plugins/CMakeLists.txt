file(GLOB_RECURSE ALL_PLUGIN_FILES "*.cpp")

foreach(PLUGIN_FILE ${ALL_PLUGIN_FILES})
    get_filename_component(PLUGIN_FILE_NAME ${PLUGIN_FILE} NAME)
    string(REPLACE ".cpp" "" PLUGIN_TARGET ${PLUGIN_FILE_NAME})
    # message("  - ${PLUGIN_FILE} --> ${PLUGIN_TARGET}")

    add_library(${PLUGIN_TARGET}_plugin ${PLUGIN_FILE})
    target_compile_definitions(${PLUGIN_TARGET}_plugin PRIVATE MAKEDLL)

    set_target_properties(${PLUGIN_TARGET}_plugin PROPERTIES LINK_SEARCH_START_STATIC ON)
    set_target_properties(${PLUGIN_TARGET}_plugin PROPERTIES LINK_SEARCH_END_STATIC ON)

    set_target_properties(${PLUGIN_TARGET}_plugin PROPERTIES PREFIX "")
    set_target_properties(${PLUGIN_TARGET}_plugin PROPERTIES OUTPUT_NAME ${PLUGIN_TARGET}Plugin)

    set_target_properties(${PLUGIN_TARGET}_plugin
            PROPERTIES
            LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/plugins
            RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/plugins)

    target_link_libraries(${PLUGIN_TARGET}_plugin PRIVATE PluginSystemInfrastructures -static-libgcc -static-libstdc++ -static)
endforeach(PLUGIN_FILE ${ALL_PLUGIN_FILES})

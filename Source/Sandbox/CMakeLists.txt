set (CURR_APP_NAME Sandbox)

if(APPLE)
    add_executable(${CURR_APP_NAME} MACOSX_BUNDLE)
    add_subdirectory(Entry/OSX)
    set(freight_lib_name libFreight.a)
elseif(WIN32)
    add_executable(${CURR_APP_NAME})
    add_subdirectory(Entry/glfw)
    set(freight_lib_name Freight.lib)
endif()

target_sources(${CURR_APP_NAME}
    PRIVATE
        SandboxApp.cpp
        SandboxApp.hpp
)

add_dependencies(${CURR_APP_NAME} Freight)

set_target_properties(${CURR_APP_NAME} PROPERTIES 
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/Sandbox"
)

target_link_libraries(${CURR_APP_NAME}
    debug     ${CMAKE_BINARY_DIR}/lib/Freight/Debug/${freight_lib_name}
    optimized ${CMAKE_BINARY_DIR}/lib/Freight/Release/${freight_lib_name}
)


my_target_source_group(${CURR_APP_NAME})

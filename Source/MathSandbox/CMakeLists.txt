set (CURR_APP_NAME MathSandbox)

add_executable(${CURR_APP_NAME})
set(freight_lib_name Freight.lib)

target_sources(${CURR_APP_NAME}
    PRIVATE
        main.cpp
)

add_dependencies(${CURR_APP_NAME} Freight)

set_target_properties(${CURR_APP_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/${CURR_APP_NAME}"
)

target_link_libraries(${CURR_APP_NAME}
    debug     ${CMAKE_BINARY_DIR}/lib/Freight/Debug/${freight_lib_name}
    optimized ${CMAKE_BINARY_DIR}/lib/Freight/Release/${freight_lib_name}
)

my_target_source_group(${CURR_APP_NAME})

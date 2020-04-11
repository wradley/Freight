set (CURR_APP_NAME FreightTests)
add_executable(${CURR_APP_NAME})

target_sources(${CURR_APP_NAME}
    PRIVATE
        main.cpp
        Vector.cpp
)

set_target_properties(${CURR_APP_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/${CURR_APP_NAME}"
)

add_dependencies(${CURR_APP_NAME} Freight)
my_target_source_group(${CURR_APP_NAME})

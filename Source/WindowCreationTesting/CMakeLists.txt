
if (NOT WIN32)
    return ()
endif()

set (CURR_APP_NAME WindowCreationTesting)

add_executable(${CURR_APP_NAME})
set(freight_lib_name Freight.lib)

target_sources(${CURR_APP_NAME}
    PRIVATE
        WindowCreationTesting.cpp
        WindowCreationTesting.hpp
)


add_dependencies(${CURR_APP_NAME} Freight)

set_target_properties(${CURR_APP_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/${CURR_APP_NAME}"
)

target_link_libraries(${CURR_APP_NAME}
    debug     ${GLFW_DBG_LIB}
    optimized ${GLFW_REL_LIB}
    debug     ${CMAKE_BINARY_DIR}/lib/Freight/Debug/${freight_lib_name}
    optimized ${CMAKE_BINARY_DIR}/lib/Freight/Release/${freight_lib_name}
)

target_include_directories(${CURR_APP_NAME} PRIVATE
    "${GLAD_INCLUDE}"
)

set(WINDOWCREATIONTESING_PATH_TO_ASSETS "" CACHE PATH "Path to WinSandbox asset dir")
add_compile_definitions(WINDOWCREATIONTESING_PATH_TO_ASSETS="${WINDOWCREATIONTESING_PATH_TO_ASSETS}")

my_target_source_group(${CURR_APP_NAME})

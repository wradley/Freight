
if (NOT WIN32)
    return ()
endif()

set (CURR_APP_NAME WinSandbox)

add_executable(${CURR_APP_NAME})
#add_subdirectory(Entry/glfw)
set(freight_lib_name Freight.lib)

target_sources(${CURR_APP_NAME}
    PRIVATE
        GraphicsSystem.hpp
        GraphicsSystem.cpp
        LevelLoader.cpp
        LevelLoader.hpp
        Main.cpp
)

add_dependencies(${CURR_APP_NAME} Freight)

set_target_properties(${CURR_APP_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/${CURR_APP_NAME}"
)

# grab opengl stuff
set(GLFW_DBG_LIB "" CACHE FILEPATH "GLFW Debug Library")
set(GLFW_REL_LIB "" CACHE FILEPATH "GLFW Release Library")
set(GLFW_INCLUDE "" CACHE PATH "GLFW Include Directory")
set(GLAD_SRC_FILE "" CACHE FILEPATH "GLAD Source File")
set(GLAD_INCLUDE "" CACHE PATH "GLAD Include Directory")
set(JSON_INCLUDE "" CACHE PATH "JSON Lib Include Directory")

target_include_directories(${CURR_APP_NAME} PRIVATE
    "${GLFW_INCLUDE}"
    "${GLAD_INCLUDE}"
    "${JSON_INCLUDE}"
)

target_link_libraries(${CURR_APP_NAME}
    debug     ${GLFW_DBG_LIB}
    optimized ${GLFW_REL_LIB}
    debug     ${CMAKE_BINARY_DIR}/lib/Freight/Debug/${freight_lib_name}
    optimized ${CMAKE_BINARY_DIR}/lib/Freight/Release/${freight_lib_name}
)

target_sources(${CURR_APP_NAME} PRIVATE
    ${GLAD_SRC_FILE}
)

my_target_source_group(${CURR_APP_NAME})

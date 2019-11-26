
if (NOT WIN32)
    return ()
endif()

set (CURR_APP_NAME WinSandbox)

add_executable(${CURR_APP_NAME})
#add_subdirectory(Entry/glfw)
set(freight_lib_name Freight.lib)

target_sources(${CURR_APP_NAME}
    PRIVATE
        GamePadController.cpp
        GamePadController.hpp
        GraphicsResourceManager.cpp
        GraphicsResourceManager.hpp
        GraphicsSystem.hpp
        GraphicsSystem.cpp
        LevelLoader.cpp
        LevelLoader.hpp
        LoadEvents.cpp
        LoadEvents.hpp
        Main.cpp
        PlayerControllerSystem.hpp
        PlayerControllerSystem.cpp
        stb_image.h
        WinSandbox.cpp
        WinSandbox.hpp
)

add_subdirectory(Physics)

add_dependencies(${CURR_APP_NAME} Freight)

set_target_properties(${CURR_APP_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/${CURR_APP_NAME}"
)

# libs
set(GLFW_DBG_LIB "" CACHE FILEPATH "GLFW Debug Library")
set(GLFW_REL_LIB "" CACHE FILEPATH "GLFW Release Library")
set(GLFW_INCLUDE "" CACHE PATH "GLFW Include Directory")
set(GLAD_SRC_FILE "" CACHE FILEPATH "GLAD Source File")
set(GLAD_INCLUDE "" CACHE PATH "GLAD Include Directory")
set(JSON_INCLUDE "" CACHE PATH "JSON Lib Include Directory")
set(ASSIMP_DBG_LIB "" CACHE FILEPATH "Assimp Debug Library")
set(ASSIMP_REL_LIB "" CACHE FILEPATH "Assimp Release Library")
set(ASSIMP_INCLUDE "" CACHE PATH "Assimp Include Directory")
set(ZLIB_DBG_LIB "" CACHE FILEPATH "Assimp Contrib zLib Debug Library")
set(ZLIB_REL_LIB "" CACHE FILEPATH "Assimp Contrib zLib Release Library")
set(IRRXML_DBG_LIB "" CACHE FILEPATH "Assimp Contrib Debug irrXML Library")
set(IRRXML_REL_LIB "" CACHE FILEPATH "Assimp Contrib Release irrXML Library")

set(WINSANDBOX_PATH_TO_ASSETS "" CACHE PATH "Path to WinSandbox asset dir")
add_compile_definitions(WINSANDBOX_PATH_TO_ASSETS=${WINSANDBOX_PATH_TO_ASSETS})

target_include_directories(${CURR_APP_NAME} PRIVATE
    "${GLFW_INCLUDE}"
    "${GLAD_INCLUDE}"
    "${JSON_INCLUDE}"
    "${ASSIMP_INCLUDE}"
)

message(${IRRXML_DBG_LIB})

target_link_libraries(${CURR_APP_NAME}
    debug     ${GLFW_DBG_LIB}
    optimized ${GLFW_REL_LIB}
    debug     ${ZLIB_DBG_LIB}
    optimized ${ZLIB_REL_LIB}
    debug     ${IRRXML_DBG_LIB}
    optimized ${IRRXML_REL_LIB}
    debug     ${ASSIMP_DBG_LIB}
    optimized ${ASSIMP_REL_LIB}
    debug     ${CMAKE_BINARY_DIR}/lib/Freight/Debug/${freight_lib_name}
    optimized ${CMAKE_BINARY_DIR}/lib/Freight/Release/${freight_lib_name}
)

target_sources(${CURR_APP_NAME} PRIVATE
    ${GLAD_SRC_FILE}
)

my_target_source_group(${CURR_APP_NAME})

if (WIN32)
    target_sources(Freight
        PRIVATE
            Win32.cpp
    )

    # libs
    set(GLFW_DBG_LIB "" CACHE FILEPATH "GLFW Debug Library")
    set(GLFW_REL_LIB "" CACHE FILEPATH "GLFW Release Library")
    set(GLFW_INCLUDE "" CACHE PATH "GLFW Include Directory")
    set(GLAD_SRC_FILE "" CACHE FILEPATH "GLAD Source File")
    set(GLAD_INCLUDE "" CACHE PATH "GLAD Include Directory")
    set(STBI_INCLUDE "" CACHE PATH "STB Image Include Directory")

    target_include_directories(Freight PRIVATE
        "${GLFW_INCLUDE}"
        "${GLAD_INCLUDE}"
        "${STBI_INCLUDE}"
    )

    target_link_libraries(Freight
        debug     ${GLFW_DBG_LIB}
        optimized ${GLFW_REL_LIB}
    )

    target_sources(Freight PRIVATE
        ${GLAD_SRC_FILE}
    )

endif()


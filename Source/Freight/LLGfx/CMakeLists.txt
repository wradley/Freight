target_sources(Freight PRIVATE
    BufferDescriptor.hpp
    CommandQueue.hpp
    Device.hpp
    InputLayoutDescriptor.hpp
    PipelineDescriptor.hpp
    ShaderDescriptor.hpp
    ShaderSignatureDescriptor.cpp
    ShaderSignatureDescriptor.hpp
    Types.hpp
)

if(WIN32)
    add_subdirectory(OpenGL)

    set(GLFW_DBG_LIB "" CACHE FILEPATH "GLFW Debug Library")
    set(GLFW_REL_LIB "" CACHE FILEPATH "GLFW Release Library")
    set(GLFW_INCLUDE "" CACHE PATH "GLFW Include Directory")
    set(GLAD_SRC_FILE "" CACHE FILEPATH "GLAD Source File")
    set(GLAD_INCLUDE "" CACHE PATH "GLAD Include Directory")

    target_include_directories(Freight PRIVATE
        "${GLFW_INCLUDE}"
        "${GLAD_INCLUDE}"
    )

    target_link_libraries(Freight
        debug     ${GLFW_DBG_LIB}
        optimized ${GLFW_REL_LIB}
    )

    target_sources(Freight PRIVATE
        ${GLAD_SRC_FILE}
    )
endif()
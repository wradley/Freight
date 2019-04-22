add_library(Renderer)
set_target_properties(Renderer PROPERTIES LINKER_LANGUAGE CXX)

target_sources(Renderer
    PRIVATE
        Renderer.cpp
        Renderer.hpp
)

add_subdirectory(2D)
add_subdirectory(3D)

# file(GLOB_RECURSE RENDERER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*)
# source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} PREFIX "Source" FILES ${RENDERER_FILES})
my_target_source_group(Renderer)
set_target_properties(Renderer PROPERTIES FOLDER SharedModules)

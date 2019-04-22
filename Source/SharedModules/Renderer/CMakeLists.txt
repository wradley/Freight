add_library(Renderer)
set_target_properties(Renderer PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(Renderer PROPERTIES FOLDER SharedModules)
set_target_properties(Renderer PROPERTIES CXX_STANDARD 17)

target_sources(Renderer
    PRIVATE
        Renderer.cpp
        Renderer.hpp
)

my_target_source_group(Renderer)
add_subdirectory(2D)
add_subdirectory(3D)

add_library(Freight)
set_target_properties(Freight PROPERTIES LINKER_LANGUAGE CXX)
# set_target_properties(Freight PROPERTIES CXX_STANDARD 17)

target_sources(Freight
    PRIVATE
        Freight.cpp
        Freight.hpp
        Error.hpp
)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Includes)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Log)

my_target_source_group(Freight)

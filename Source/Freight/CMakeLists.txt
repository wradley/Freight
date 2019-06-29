add_library(Freight)

set_target_properties(Freight PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(Freight PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib/Freight")

target_sources(Freight
    PRIVATE
        Freight.cpp
        Freight.hpp

        Include/Freight.hpp

        Math/Transform.cpp
        Math/Transform.hpp

        Tasks/Task.cpp
        Tasks/Task.hpp
)

my_target_source_group(Freight)
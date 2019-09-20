add_library(Freight)

set_target_properties(Freight PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(Freight PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib/Freight")

target_sources(Freight
    PRIVATE

        Include/Freight.hpp
        Include/Math.hpp

        Log/Log.cpp
        Log/Log.hpp

        Math/Conversion.cpp
        Math/Conversion.hpp
        Math/Matrix.hpp
        Math/Precision.hpp
        Math/Quaternion.hpp
        Math/Transform.cpp
        Math/Transform.hpp
        Math/Vector.hpp

        Tasks/Task.cpp
        Tasks/Task.hpp

        Defines.hpp
        Freight.cpp
        Freight.hpp
)

#add_subdirectory(LLGfx)

my_target_source_group(Freight)

add_library(Freight)

set_target_properties(Freight PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(Freight PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib/Freight")

target_sources(Freight
    PRIVATE

        Log/Log.cpp
        Log/Log.hpp

        Math/Conversion.cpp
        Math/Conversion.hpp
        Math/Matrix.hpp
        Math/Quaternion.hpp
        Math/Transform.cpp
        Math/Transform.hpp
        Math/Vector.hpp

        Tasks/Task.cpp
        Tasks/Task.hpp

        Testing/Test.hpp
        Testing/TestResult.hpp
        Testing/TestStage.hpp
        Testing/TestUtil.hpp

        Defines.hpp
        Freight.cpp
        Freight.hpp
        String.hpp
)

add_subdirectory(Events)
add_subdirectory(FileSystem)
add_subdirectory(Include)
#add_subdirectory(LLGfx)

my_target_source_group(Freight)

if(WIN32)
    add_executable(Sandbox WIN32)
endif()
# set_target_properties(Sandbox PROPERTIES CXX_STANDARD 17)
# target_include_directories(Sandbox PRIVATE "${PROJECT_SOURCE_DIR}/Source")

target_sources(Sandbox
    PRIVATE
        Entry.cpp
        SandboxApp.cpp
        SandboxApp.hpp
)

target_link_libraries(Sandbox
    debug
        ${CMAKE_SOURCE_DIR}/lib/Debug/Freight.lib
    optimized
        ${CMAKE_SOURCE_DIR}/lib/Release/Freight.lib
)

my_target_source_group(Sandbox)

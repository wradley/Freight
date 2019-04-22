add_executable(Sandbox)
set_target_properties(Sandbox PROPERTIES CXX_STANDARD 17)
target_include_directories(Sandbox PRIVATE "${PROJECT_SOURCE_DIR}/Source")

target_sources(Sandbox
    PRIVATE
        Entry.cpp
        SandboxApp.cpp
        SandboxApp.hpp
)

my_target_source_group(Sandbox)

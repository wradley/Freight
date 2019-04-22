# include_directories("${PROJECT_SOURCE_DIR}/Application")

set(SANDBOX_SOURCES
    Entry.cpp
    SandboxApp.cpp
    SandboxApp.hpp
)

add_executable(Sandbox ${SANDBOX_SOURCES})
target_include_directories(Sandbox PRIVATE "${PROJECT_SOURCE_DIR}/Source")

my_target_source_group(Sandbox)

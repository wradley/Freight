cmake_minimum_required(VERSION 3.14)
project(ProjectFreight)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CONFIGURATION_TYPES "Debug;Release")

macro(my_target_source_group target_name)
    file(GLOB_RECURSE ${target_name}_source_files ${CMAKE_CURRENT_SOURCE_DIR}/*)
    source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} PREFIX "Source" FILES ${${target_name}_source_files})
endmacro()

include_directories(Source/Freight/Include)
add_subdirectory(Source/Freight)
#add_subdirectory(Source/Sandbox)
add_subdirectory(Source/WinSandbox)
# add_subdirectory(Source/MathSandbox)
add_subdirectory(Testing/Freight)
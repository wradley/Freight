cmake_minimum_required(VERSION 3.14)
project(Freight)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
# set_property(GLOBAL PROPERTY CXX_EXTENSIONS NO)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

include_directories("Source/Freight/Includes")

macro(my_target_source_group target_name)
    file(GLOB_RECURSE ${target_name}_source_files ${CMAKE_CURRENT_SOURCE_DIR}/*)
    source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} PREFIX "Source" FILES ${${target_name}_source_files})
endmacro()


add_subdirectory(Source)
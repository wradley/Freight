cmake_minimum_required(VERSION 3.14)
project(Freight)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY CXX_STANDARD 17)


macro(my_target_source_group target_name)
    file(GLOB_RECURSE ${target_name}_source_files ${CMAKE_CURRENT_SOURCE_DIR}/*)
    source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} PREFIX "Source" FILES ${${target_name}_source_files})
endmacro()


add_subdirectory(Source)



# file(GLOB_RECURSE ALL_SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/Source/*)
# source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${ALL_SOURCE_FILES})

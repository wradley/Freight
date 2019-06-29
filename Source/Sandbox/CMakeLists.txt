add_executable(Sandbox)
add_dependencies(Sandbox Freight)

target_sources(Sandbox
PRIVATE
    SandboxApp.cpp   
    SandboxApp.hpp
)

set_target_properties(Sandbox PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/Sandbox")

target_link_libraries(Sandbox 
    debug     "${CMAKE_BINARY_DIR}/lib/Freight/Debug/Freight.lib"
    optimized "${CMAKE_BINARY_DIR}/lib/Freight/Release/Freight.lib"
)


my_target_source_group(Sandbox)
add_executable(Sandbox)
add_dependencies(Sandbox Freight)

target_sources(Sandbox
PRIVATE
    SandboxApp.cpp
    SandboxApp.hpp
)

set_target_properties(Sandbox PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/Sandbox")

if(WIN32)
    set(freight_lib_name Freight.lib)
elseif(APPLE)
    set(freight_lib_name libFreight.a)
endif()

target_link_libraries(Sandbox
    debug     "${CMAKE_BINARY_DIR}/lib/Freight/Debug/${freight_lib_name}"
    optimized "${CMAKE_BINARY_DIR}/lib/Freight/Release/${freight_lib_name}"
)


my_target_source_group(Sandbox)

if(APPLE)
    add_executable(Sandbox MACOSX_BUNDLE "")

    target_sources(Sandbox
        PRIVATE
            Entry/OSX/AppDelegate.h
            Entry/OSX/AppDelegate.m
            Entry/OSX/GameViewController.h
            Entry/OSX/GameViewController.m
            Entry/OSX/main.m
            Entry/OSX/Main.storyboard
            Entry/OSX/Renderer.h
            Entry/OSX/Renderer.mm
            Entry/OSX/Shaders.metal
            Entry/OSX/ShaderTypes.h
    )
    set(freight_lib_name libFreight.a)

    find_library(cocoa_lib Cocoa)
    find_library(metal_lib Metal)
    find_library(metal_kit_lib MetalKit)
    find_library(model_io_lib ModelIO)
    target_link_libraries(Sandbox
        general ${cocoa_lib}
        general ${metal_lib}
        general ${metal_kit_lib}
        general ${model_io_lib}
    )

    set_target_properties(Sandbox PROPERTIES 
        MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/Entry/OSX/plist.in
        XCODE_ATTRIBUTE_CLANG_ENABLE_OBJC_ARC YES
    )

    set_source_files_properties(
        ${CMAKE_CURRENT_SOURCE_DIR}/Entry/OSX/Main.storyboard
        ${CMAKE_CURRENT_SOURCE_DIR}/Entry/OSX/Shaders.metal
        PROPERTIES
        MACOSX_PACKAGE_LOCATION Resources
    )
    set_source_files_properties(
        ${CMAKE_CURRENT_SOURCE_DIR}/Entry/OSX/Shaders.metal 
        PROPERTIES
        LANGUAGE METAL
    )
elseif(WIN32)
    add_executable(Sandbox)
    set(freight_lib_name Freight.lib)
endif()

add_dependencies(Sandbox Freight)

target_sources(Sandbox
    PRIVATE
        SandboxApp.cpp
        SandboxApp.hpp
)

set_target_properties(Sandbox PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/Sandbox")

target_link_libraries(Sandbox
    debug     ${CMAKE_BINARY_DIR}/lib/Freight/Debug/${freight_lib_name}
    optimized ${CMAKE_BINARY_DIR}/lib/Freight/Release/${freight_lib_name}
)


my_target_source_group(Sandbox)

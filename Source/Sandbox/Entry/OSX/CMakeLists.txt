target_sources(${CURR_APP_NAME} PRIVATE
    AppDelegate.h
    AppDelegate.m
    GameViewController.h
    GameViewController.m
    main.m
    Main.storyboard
    Renderer.h
    Renderer.mm
    Shaders.metal
    ShaderTypes.h
)

find_library(cocoa_lib Cocoa)
find_library(metal_lib Metal)
find_library(metal_kit_lib MetalKit)
find_library(model_io_lib ModelIO)
target_link_libraries(${CURR_APP_NAME}
    general ${cocoa_lib}
    general ${metal_lib}
    general ${metal_kit_lib}
    general ${model_io_lib}
)

set_target_properties(${CURR_APP_NAME} PROPERTIES 
    MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/plist.in
    XCODE_ATTRIBUTE_CLANG_ENABLE_OBJC_ARC YES
)

set_source_files_properties(
    ${CMAKE_CURRENT_SOURCE_DIR}/Main.storyboard
    ${CMAKE_CURRENT_SOURCE_DIR}/Shaders.metal
    PROPERTIES
    MACOSX_PACKAGE_LOCATION Resources
)

set_source_files_properties(
    ${CMAKE_CURRENT_SOURCE_DIR}/Shaders.metal 
    PROPERTIES
    LANGUAGE METAL
)
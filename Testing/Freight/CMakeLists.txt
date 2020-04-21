set (CURR_APP_NAME FreightTests)
add_executable(${CURR_APP_NAME})

target_sources(${CURR_APP_NAME}
    PRIVATE
        main.cpp

        Math/TestMat2x2.cpp
        Math/TestQuaternion.cpp
        Math/TestVec2.cpp
        Math/TestVec3.cpp
        Math/TestVec4.cpp
)

set_target_properties(${CURR_APP_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/${CURR_APP_NAME}"
)

add_dependencies(${CURR_APP_NAME} Freight)

if(APPLE)
    set(FR_LIB_NAME "libFreight.a")
elseif(WIN32)
    set(FR_LIB_NAME "Freight.lib")
endif()

target_link_libraries(${CURR_APP_NAME}
    debug     "${CMAKE_BINARY_DIR}/lib/Freight/Debug/${FR_LIB_NAME}"
    optimized "${CMAKE_BINARY_DIR}/lib/Freight/Release/${FR_LIB_NAME}"
)

my_target_source_group(${CURR_APP_NAME})

target_sources(${CURR_APP_NAME} PRIVATE
    main.cpp
)


target_include_directories(${CURR_APP_NAME} PRIVATE
    "${GLFW_INCLUDE}"
    "${GLAD_INCLUDE}"
)

target_link_libraries(${CURR_APP_NAME}
    debug     ${GLFW_DBG_LIB}
    optimized ${GLFW_REL_LIB}
)
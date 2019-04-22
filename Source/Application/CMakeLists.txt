
set(APPLICATION_SOURCES
    Application.hpp
    Error.hpp
)

add_library(Application ${APPLICATION_SOURCES})

set_target_properties(Application PROPERTIES LINKER_LANGUAGE CXX)

my_target_source_group(Application)

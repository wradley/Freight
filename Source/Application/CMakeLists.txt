add_library(Application)
set_target_properties(Application PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(Application PROPERTIES CXX_STANDARD 17)

target_sources(Application
    PRIVATE
        Application.hpp
        Error.hpp
)

my_target_source_group(Application)

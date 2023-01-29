add_library(core 
    STATIC 
        src/supertyper.cpp
        src/buffer.cpp
        src/file_parser.cpp
        src/word_shuffler.cpp
    )

target_include_directories(core 
    PUBLIC
        include
    )

target_link_libraries(core cxxcurses::cxxcurses)

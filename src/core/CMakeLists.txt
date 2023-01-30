add_library(core 
    STATIC 
        src/supertyper.cpp
        src/buffer.cpp
        src/file_parser.cpp
        src/word_shuffler.cpp
        src/state.cpp
        src/menu_state.cpp
        src/game_state.cpp
        src/scoreboard_state.cpp
        src/quit_state.cpp
        src/file_browser_state.cpp
    )

target_include_directories(core 
    PUBLIC
        include
    )

target_link_libraries(core cxxcurses::cxxcurses)

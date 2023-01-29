#include "game_state.h"
#include "menu_state.h"
#include "supertyper.h"

#include "cxxcurses/print.hpp"
#include "cxxcurses/terminal/terminal.hpp"

#include <cstdlib>
#include <memory>

int main()
{
    cxxcurses::terminal init;

    st::Supertyper app{};

    app.update();

    return 0;
}


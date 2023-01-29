#include "supertyper.h"

#include "cxxcurses/print.hpp"
#include "cxxcurses/terminal/terminal.hpp"

#include <cstdlib>

int main()
{
    cxxcurses::terminal init;

    st::Supertyper app;

    app.update();

    return 0;
}


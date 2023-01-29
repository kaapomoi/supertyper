#include "menu_state.h"

#include "game_state.h"
#include "supertyper.h"

#include "cxxcurses/print.hpp"

namespace st {

Menu_state::Menu_state(Supertyper& context) noexcept
    : State{context}
    , m_menu_window{cc::widget::window{{20, m_dims.second / 2 - (m_box_width / 2), 3, m_box_width},
                                       cc::terminal::main_win}}

{
}

void Menu_state::run() noexcept
{
    m_menu_window << cc::format(1)("{wB}", "Super Typer");

    auto const c = m_menu_window.get_char();

    m_context.change_state(std::make_shared<Game_state>(m_context));
}

} // namespace st

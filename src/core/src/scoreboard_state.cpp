#include "scoreboard_state.h"

#include "menu_state.h"
#include "supertyper.h"

#include "cxxcurses/print.hpp"

#include <memory>

namespace st {

Scoreboard_state::Scoreboard_state(Supertyper& context, std::uint32_t const score) noexcept
    : State{context}
    , m_score{score}
    , m_score_window{cc::widget::window{
          {10, (m_dims.second / 2) - (m_box_width / 2), 10, m_box_width}, cc::terminal::main_win}}
{
}

void Scoreboard_state::run() noexcept
{
    m_score_window << cc::format(2)("WPM: {p}", std::to_string(m_score));

    static_cast<void>(m_score_window.get_char());
    m_context.change_state(std::make_shared<Menu_state>(m_context));
}

} // namespace st

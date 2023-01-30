#include "menu_state.h"

#include "file_browser_state.h"
#include "game_state.h"
#include "quit_state.h"
#include "supertyper.h"

#include "cxxcurses/print.hpp"

#include <algorithm>
#include <cstdint>

namespace st {

Menu_state::Menu_state(Supertyper& context) noexcept
    : State{context}
    , m_title_window{cc::widget::window{{7, m_dims.second / 2 - (m_box_width / 2), 3, m_box_width},
                                        cc::terminal::main_win}}
    , m_menu_window{cc::widget::window{{10, m_dims.second / 2 - (m_box_width / 2), 6, m_box_width},
                                       m_title_window}}

{
}

void Menu_state::run() noexcept
{
    cc::cursor::set_visibility(cc::cursor::visibility::invisible);
    m_title_window << cc::format(1)("{wB}", m_context.get_words_file());

    static constexpr std::uint32_t pad{1};

    while (m_keep_running) {
        for (auto const& [opt, str] : m_menu_options) {
            std::string format{"{bN}"};
            if (m_choice == static_cast<std::uint32_t>(opt)) {
                format = "{wB}";
            }
            m_menu_window << cc::format(static_cast<std::uint32_t>(opt) + pad, m_box_pad)(format,
                                                                                          str);
        }

        handle_menu(m_menu_window.get_char());
    }
}

void Menu_state::handle_menu(std::uint32_t const c) noexcept
{
    auto clamp = [](std::uint32_t& value) {
        value = std::min(value, static_cast<std::uint32_t>(Menu_option::quit));
        value = std::max(value, static_cast<std::uint32_t>(Menu_option::play));
    };

    switch (c) {
    case KEY_UP:
    case 'k':
        m_choice--;
        clamp(m_choice);
        break;
    case KEY_DOWN:
    case 'j':
        m_choice++;
        clamp(m_choice);
        break;
    case 10:
        /// End state, confirm choice
        handle_menu_choices();
        break;
    }
}

void Menu_state::handle_menu_choices() noexcept
{
    switch (Menu_option{m_choice}) {
    case Menu_option::play:
        m_context.change_state(std::make_shared<Game_state>(m_context));
        m_keep_running = false;
        break;
    case Menu_option::words:
        m_context.change_state(std::make_shared<File_browser_state>(m_context));
        m_keep_running = false;
        break;
    case Menu_option::about:
        break;
    case Menu_option::quit:
        m_context.change_state(std::make_shared<Quit_state>(m_context));
        m_keep_running = false;
        break;
    }
}


} // namespace st

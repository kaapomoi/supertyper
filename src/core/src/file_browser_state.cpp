#include "file_browser_state.h"

#include "menu_state.h"
#include "supertyper.h"

#include <algorithm>
#include <cstdint>
#include <filesystem>
#include <regex>

namespace st {

File_browser_state::File_browser_state(Supertyper& context) noexcept
    : State{context}
    , m_file_browser_window{cc::widget::window{
          {10, (m_dims.second / 2) - (m_box_width / 2), 10, m_box_width}, cc::terminal::main_win}}
{
}

void File_browser_state::run() noexcept
{
    std::string const path{"../words"};

    std::regex const file_extension_regex{"\\.st$", std::regex_constants::ECMAScript
                                                        | std::regex_constants::icase};

    for (const auto& entry : std::filesystem::directory_iterator(path)) {
        std::string const filepath{entry.path()};

        if (std::regex_search(filepath, file_extension_regex)) {
            m_word_files.push_back(filepath);
        }
    }

    while (m_keep_running) {
        for (std::size_t i = 0; i < m_word_files.size(); i++) {
            std::string const filepath{m_word_files.at(i)};

            if (std::regex_search(filepath, file_extension_regex)) {
                std::string format{"{bN}"};

                if (m_choice == i) {
                    format = "{wB}";
                }

                m_file_browser_window << cc::format(i + 1, m_box_pad)(format, filepath);
            }
        }

        handle_input(m_file_browser_window.get_char());
    }
}

void File_browser_state::handle_input(std::int32_t const c) noexcept
{
    auto clamp = [](std::uint32_t& value, std::uint32_t const min, std::uint32_t const max) {
        value = std::min(value, max);
        value = std::max(value, min);
    };

    switch (c) {
    case KEY_UP:
    case 'k':
        m_choice--;
        clamp(m_choice, 0, m_word_files.size() - 1);
        break;
    case KEY_DOWN:
    case 'j':
        m_choice++;
        clamp(m_choice, 0, m_word_files.size() - 1);
        break;
    case 10:
        /// End state, confirm choice
        handle_menu_choices();
        break;
    }
}

void File_browser_state::handle_menu_choices() noexcept
{
    m_context.set_words_file(m_word_files.at(m_choice));

    m_context.change_state(std::make_shared<Menu_state>(m_context));
    m_keep_running = false;
}

} // namespace st

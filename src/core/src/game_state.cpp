#include "game_state.h"

#include "scoreboard_state.h"
#include "supertyper.h"

#include "cxxcurses/terminal/terminal.hpp"

#include <curses.h>

#include <memory>

namespace st {

Game_state::Game_state(Supertyper& context) noexcept
    : State{context}
    , m_word_window{cc::widget::window{
          {10, (m_dims.second / 2) - (m_box_width / 2), 10, m_box_width}, cc::terminal::main_win}}
    , m_type_window{cc::widget::window{{7, m_dims.second / 2 - (m_box_width / 2), 3, m_box_width},
                                       m_word_window}}

{
}

void Game_state::run() noexcept
{
    cc::cursor::set_visibility(cc::cursor::visibility::normal);
    cc::terminal::main_win << cc::format(1)("{wB}", "Super Typer");
    cc::terminal::main_win << cc::format(2)("{b}", m_context.get_words_file());

    m_file_parser.parse(m_context.get_words_file());
    m_words = m_file_parser.get_lines();
    m_word_shuffler.shuffle(m_words);

    // Updates type_window as well.
    m_word_window.draw();

    std::int32_t c{0};
    if (m_words.size() > 10) {
        m_words.resize(10);
    }

    std::size_t total_characters_in_words =
        std::accumulate(m_words.cbegin(), m_words.cend(), 0,
                        [](std::size_t sum, std::string const& str) { return sum + str.size(); });

    float const chars_per_word_average =
        total_characters_in_words / static_cast<float>(m_words.size());

    while (true) {
        std::string const word{m_words.back()};
        Buffer const word_buffer{word};

        auto incorrect_letter_indices = m_typing_buffer.check(word_buffer);
        std::string incorrect_letters;
        for (std::size_t i = 0; i < incorrect_letter_indices.size(); i++) {
            incorrect_letters.push_back(m_typing_buffer.data().at(incorrect_letter_indices.at(i)));
        }

        /// Print target word
        for (std::size_t i = 0; i < word.size(); i++) {
            std::string color;
            if (std::find(incorrect_letter_indices.begin(), incorrect_letter_indices.end(), i)
                != incorrect_letter_indices.end()) {
                color = "{r}";
            }
            else {
                if (i < m_typing_buffer.size()) {
                    color = "{g}";
                }
                else {
                    color = "{w}";
                }
            }
            m_word_window << cc::format(1, i + m_box_pad)(color, word.at(i));
        }

        if (m_typing_buffer.size() > word.size()) {
            for (std::size_t i = word.size(); i < m_typing_buffer.size(); i++) {
                m_word_window << cc::format(1, i + m_box_pad)("{r}", m_typing_buffer.data().at(i));
            }
        }

        /// Print upcoming words
        for (std::size_t i = 0; i < 7; i++) {
            if (m_words.size() >= i + 1) {
                m_word_window << cc::format(i + m_box_pad, 2)("{b}", *(m_words.end() - 2 - i));
            }
        }

        m_type_window << cc::format(1, 2)("{w}", m_typing_buffer.data());
        m_type_window << cc::format(1, m_box_width - (m_box_pad * 2))("{w}", m_score);
        m_type_window.move_cursor(1, m_typing_buffer.size() + m_box_pad);

        c = m_type_window.get_char();
        if (c == 127) {
            if (m_typing_buffer.size() > 0) {
                m_typing_buffer.rm_back();
                m_type_window.draw();
                m_word_window.draw();
            }
        }
        else if (c == ' ' || c == 10) {
            if (m_typing_buffer.check(word_buffer).empty()
                && m_typing_buffer.size() == word.size()) {
                m_score += m_typing_buffer.clear();

                m_words.pop_back();

                m_word_window.draw();
                m_type_window.draw();
                /// Handle finish
                if (m_words.empty()) {
                    m_stop_time = std::chrono::steady_clock::now();
                    auto const time_delta = m_stop_time - m_start_time;
                    m_time_spent_seconds =
                        std::chrono::duration_cast<std::chrono::seconds>(time_delta).count();

                    m_score = (m_score * 60) / m_time_spent_seconds;

                    m_game_started = false;

                    m_word_window.draw();
                    m_type_window.draw();
                    wclear(cc::terminal::main_win.get());
                    cc::terminal::main_win.draw();

                    m_context.change_state(std::make_shared<Scoreboard_state>(m_context, m_score));
                    break;
                }
            }
        }
        else {
            if (!m_game_started) {
                m_start_time = std::chrono::steady_clock::now();
            }
            m_game_started = true;
            m_typing_buffer.append(c);
        }
    }
}

} // namespace st

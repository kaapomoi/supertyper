#include "supertyper.h"

#include "cxxcurses/print.hpp"
#include "cxxcurses/terminal/cursor.hpp"
#include "cxxcurses/terminal/terminal.hpp"
#include "cxxcurses/widget/window.hpp"

#include <curses.h>

#include <algorithm>
#include <chrono>
#include <iostream>
#include <numeric>
#include <regex>
#include <string>

namespace st {

Supertyper::Supertyper() noexcept
    : m_dims{cc::terminal::main_win.max_yx()}
    , m_word_window{cc::widget::window{
          {10, (m_dims.second / 2) - (m_box_width / 2), 10, m_box_width}, cc::terminal::main_win}}
    , m_type_window{cc::widget::window{{20, m_dims.second / 2 - (m_box_width / 2), 3, m_box_width},
                                       m_word_window}}
{
    cc::cursor::set_visibility(cc::cursor::visibility::normal);
    cc::terminal::main_win << cc::format(0)("{wB}", "Super Typer");
    m_file_parser.parse("words.txt");
    m_words = m_file_parser.get_lines();
    m_word_shuffler.shuffle(m_words);
}

Supertyper::~Supertyper() noexcept {}

void Supertyper::update() noexcept
{
    std::int32_t c{0};
    m_words.resize(10);

    std::size_t total_characters_in_words =
        std::accumulate(m_words.cbegin(), m_words.cend(), 0,
                        [](std::size_t sum, std::string const& str) { return sum + str.size(); });

    float const chars_per_word_average =
        total_characters_in_words / static_cast<float>(m_words.size());

    while (c != 27) {
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
                    color = "{b}";
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
        else if (c == 10) {
            if (m_typing_buffer.check(word_buffer).empty()
                && m_typing_buffer.size() == word.size()) {
                m_score += m_typing_buffer.clear();

                m_words.pop_back();

                /// Handle finish
                if (m_words.empty()) {
                    m_stop_time = std::chrono::steady_clock::now();
                    auto const time_delta = m_stop_time - m_start_time;
                    m_time_spent_seconds =
                        std::chrono::duration_cast<std::chrono::seconds>(time_delta).count();

                    m_score = ((m_score * 60) / chars_per_word_average) / m_time_spent_seconds;

                    m_game_started = false;
                }

                m_word_window.draw();
                m_type_window.draw();
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

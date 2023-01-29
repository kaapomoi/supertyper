#ifndef SUPERTYPER_SUPERTYPER_H
#define SUPERTYPER_SUPERTYPER_H

#include "buffer.h"
#include "file_parser.h"
#include "word_shuffler.h"

#include "cxxcurses/cxxcurses.hpp"
#include "cxxcurses/widget/window.hpp"

#include <chrono>
#include <cstdint>
#include <string>

namespace st {
namespace cc = cxxcurses;

class Supertyper {
public:
    Supertyper() noexcept;
    ~Supertyper() noexcept;

    void update() noexcept;

private:
    std::vector<std::string> m_words;

    Buffer m_typing_buffer;
    File_parser m_file_parser;
    Word_shuffler m_word_shuffler;

    std::int32_t m_score{0};
    std::pair<std::int32_t, std::int32_t> m_dims;

    std::chrono::steady_clock::time_point m_start_time;
    std::chrono::steady_clock::time_point m_stop_time;
    std::int32_t m_time_spent_seconds{0};

    bool m_game_started{false};

    cc::widget::window m_word_window;
    cc::widget::window m_type_window;

    static constexpr std::int32_t m_box_width{40};
    static constexpr std::int32_t m_box_pad{2};
};

} // namespace st

#endif

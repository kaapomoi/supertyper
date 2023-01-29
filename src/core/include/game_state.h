#ifndef SUPERTYPER_GAME_STATE_H
#define SUPERTYPER_GAME_STATE_H

#include "state.h"

#include "cxxcurses/cxxcurses.hpp"

#include <chrono>
#include <cstdint>
#include <memory>
#include <random>
#include <stack>
#include <string>
#include <vector>

namespace st {

class Game_state : public State {
public:
    Game_state(Supertyper& context) noexcept;
    ~Game_state() noexcept override = default;

    void run() noexcept final;

private:
    std::vector<std::string> m_words;

    Buffer m_typing_buffer;
    File_parser m_file_parser;
    Word_shuffler m_word_shuffler;

    std::int32_t m_score{0};

    std::chrono::steady_clock::time_point m_start_time;
    std::chrono::steady_clock::time_point m_stop_time;
    std::int32_t m_time_spent_seconds{0};

    bool m_game_started{false};

    cc::widget::window m_word_window;
    cc::widget::window m_type_window;
};

} // namespace st

#endif

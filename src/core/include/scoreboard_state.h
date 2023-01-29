#ifndef SUPERTYPER_SCOREBOARD_STATE_H
#define SUPERTYPER_SCOREBOARD_STATE_H

#include "state.h"

namespace st {

class Scoreboard_state : public State {
public:
    Scoreboard_state(Supertyper& context, std::uint32_t const score) noexcept;
    ~Scoreboard_state() noexcept = default;

    void run() noexcept final;

private:
    std::uint32_t const m_score;
    cc::widget::window m_score_window;
};

} // namespace st

#endif

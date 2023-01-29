#ifndef SUPERTYPER_SUPERTYPER_H
#define SUPERTYPER_SUPERTYPER_H

#include "state.h"


namespace st {

class Supertyper {
public:
    Supertyper() noexcept;
    ~Supertyper() noexcept;

    void update() noexcept;

    void change_state(std::shared_ptr<State> new_state) noexcept;

private:
    void run_state() noexcept;

    std::shared_ptr<State> m_state;
};

} // namespace st

#endif

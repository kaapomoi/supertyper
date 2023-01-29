#ifndef SUPERTYPER_MENU_STATE_H
#define SUPERTYPER_MENU_STATE_H

#include "state.h"

#include <cstdint>
#include <memory>
#include <random>
#include <stack>
#include <string>
#include <vector>

namespace st {

class Menu_state : public State {
public:
    Menu_state(Supertyper& context) noexcept;
    ~Menu_state() noexcept override = default;

    void run() noexcept final;

private:
    cc::widget::window m_menu_window;
};

} // namespace st

#endif

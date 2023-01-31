#ifndef SUPERTYPER_MENU_STATE_H
#define SUPERTYPER_MENU_STATE_H

#include "state.h"

#include <cstdint>
#include <map>
#include <memory>
#include <random>
#include <stack>
#include <string>
#include <vector>

namespace st {

class Menu_state : public State {
public:
    enum class Menu_option : std::uint32_t { play = 0, words, about, quit };

    explicit Menu_state(Supertyper& context) noexcept;
    ~Menu_state() noexcept override = default;

    void run() noexcept final;

private:
    void handle_menu(std::uint32_t const c) noexcept;

    void handle_menu_choices() noexcept;

    std::map<Menu_option, std::string> m_menu_options{{Menu_option::play, "Play"},
                                                      {Menu_option::words, "Words"},
                                                      {Menu_option::about, "About"},
                                                      {Menu_option::quit, "Quit"}};


    std::uint32_t m_choice{0};
    bool m_keep_running{true};

    cc::widget::window m_title_window;
    cc::widget::window m_menu_window;
};

} // namespace st

#endif

#include "supertyper.h"

#include "menu_state.h"

#include <curses.h>

#include <algorithm>
#include <chrono>
#include <iostream>
#include <memory>
#include <numeric>
#include <regex>
#include <string>

namespace st {

Supertyper::Supertyper() noexcept : m_state{std::make_shared<Menu_state>(*this)}
{
    change_state(m_state);
}

Supertyper::~Supertyper() noexcept {}

void Supertyper::update() noexcept
{
    while (m_state) {
        m_state->run();
    }
}

void Supertyper::change_state(std::shared_ptr<State> new_state) noexcept
{
    if (m_state) {
        m_state.reset();
    }
    m_state = new_state;
}

} // namespace st

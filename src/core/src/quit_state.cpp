#include "quit_state.h"

#include "supertyper.h"

#include <algorithm>
#include <cstdint>

namespace st {

Quit_state::Quit_state(Supertyper& context) noexcept : State{context} {}

void Quit_state::run() noexcept
{
    m_context.change_state(nullptr);
}

} // namespace st

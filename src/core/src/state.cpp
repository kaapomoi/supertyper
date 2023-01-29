#include "state.h"

#include "supertyper.h"

namespace st {

State::State(Supertyper& context) noexcept
    : m_context{context}, m_dims{cc::terminal::main_win.max_yx()}
{
}

} // namespace st

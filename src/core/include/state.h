#ifndef SUPERTYPER_STATE_H
#define SUPERTYPER_STATE_H

#include "buffer.h"
#include "file_parser.h"
#include "word_shuffler.h"

#include <cxxcurses/cxxcurses.hpp>

#include <cstdint>
#include <memory>
#include <random>
#include <stack>
#include <string>
#include <vector>

namespace st {

namespace cc = cxxcurses;

class Supertyper;

class State {
public:
    State(Supertyper& context) noexcept;
    virtual ~State() noexcept = default;

    virtual void run() noexcept = 0;

protected:
    std::pair<std::int32_t, std::int32_t> m_dims;
    Supertyper& m_context;

    static constexpr std::int32_t m_box_width{40};
    static constexpr std::int32_t m_box_pad{2};
};

} // namespace st

#endif

#ifndef SUPERTYPER_QUIT_STATE_H
#define SUPERTYPER_QUIT_STATE_H

#include "state.h"

#include <cstdint>
#include <map>
#include <memory>
#include <random>
#include <stack>
#include <string>
#include <vector>

namespace st {

class Quit_state : public State {
public:
    explicit Quit_state(Supertyper& context) noexcept;
    ~Quit_state() noexcept override = default;

    void run() noexcept final;
};

} // namespace st

#endif

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

    void set_words_file(std::string const& file) noexcept;

    std::string const& get_words_file() noexcept;

private:
    void run_state() noexcept;

    std::string m_words_file{"../words/words.st"};

    std::shared_ptr<State> m_state;
};

} // namespace st

#endif

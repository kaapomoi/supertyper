#ifndef SUPERTYPER_FILE_BROWSER_STATE_H
#define SUPERTYPER_FILE_BROWSER_STATE_H

#include "state.h"

#include <cstdint>
#include <map>
#include <memory>
#include <random>
#include <stack>
#include <string>
#include <vector>

namespace st {

class File_browser_state : public State {
public:
    explicit File_browser_state(Supertyper& context) noexcept;
    ~File_browser_state() noexcept override = default;

    void run() noexcept final;

private:
    struct Word_file {
        std::string const name;
        std::uint32_t word_lines;
    };

    void handle_input(std::int32_t const c) noexcept;

    void handle_menu_choices() noexcept;

    std::vector<Word_file> m_word_files;

    bool m_keep_running{true};

    std::size_t m_word_files_in_dir{0};
    std::uint32_t m_choice{0};
    cc::widget::window m_file_browser_window;
};

} // namespace st

#endif

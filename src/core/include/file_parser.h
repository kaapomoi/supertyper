#ifndef SUPERTYPER_FILE_PARSER_H
#define SUPERTYPER_FILE_PARSER_H

#include <cstdint>
#include <string>
#include <vector>

namespace st {

class File_parser {
public:
    File_parser() noexcept = default;

    void parse(std::string const& file) noexcept;

    std::vector<std::string> get_lines() noexcept;

private:
    std::vector<std::string> m_lines;
};

} // namespace st

#endif

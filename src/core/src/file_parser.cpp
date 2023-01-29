#include "file_parser.h"

#include <fstream>

namespace st {

void File_parser::parse(std::string const& file) noexcept
{
    std::ifstream infile(file);
    std::string line;
    while (std::getline(infile, line)) {
        m_lines.push_back(line);
    }
}

std::vector<std::string> File_parser::get_lines() noexcept
{
    return m_lines;
}

} // namespace st

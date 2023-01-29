#include "buffer.h"

#include <cstddef>
#include <iostream>
#include <regex>

namespace st {

Buffer::Buffer() noexcept : m_data{} {}

Buffer::Buffer(std::string const& initial_data) noexcept : m_data(initial_data) {}

void Buffer::append(char const c) noexcept
{
    m_data += c;
}

void Buffer::rm_back() noexcept
{
    m_data.pop_back();
}

std::vector<std::size_t> Buffer::check(Buffer const& other) noexcept
{
    std::vector<std::size_t> incorrect_letter_indices;

    for (std::size_t i = 0; i < m_data.size(); i++) {
        if (i < other.m_data.size()) {
            if (m_data.at(i) != other.m_data.at(i)) {
                incorrect_letter_indices.push_back(i);
            }
        }
        else {
            incorrect_letter_indices.push_back(i);
        }
    }

    return incorrect_letter_indices;
}

std::size_t Buffer::clear() noexcept
{
    auto size = m_data.size();
    m_data.clear();

    return size;
}

std::string const& Buffer::data() noexcept
{
    return m_data;
}

std::size_t Buffer::size() noexcept
{
    return m_data.size();
}

} // namespace st

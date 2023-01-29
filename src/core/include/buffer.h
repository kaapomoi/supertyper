#ifndef SUPERTYPER_BUFFER_H
#define SUPERTYPER_BUFFER_H

#include <cstdint>
#include <string>
#include <vector>

namespace st {

class Buffer {
public:
    Buffer() noexcept;
    explicit Buffer(std::string const& initial_data) noexcept;

    void append(char const c) noexcept;

    void rm_back() noexcept;

    /// Returns the indices of non-matching characters in this buffer.
    std::vector<std::size_t> check(Buffer const& other) noexcept;

    /// Clear the buffer and return the amount of characters it held.
    std::size_t clear() noexcept;

    std::string const& data() noexcept;
    std::size_t size() noexcept;

private:
    std::string m_data;
};

} // namespace st

#endif

#include "word_shuffler.h"

#include <algorithm>
#include <cstddef>
#include <iostream>
#include <random>
#include <regex>
#include <vector>

namespace st {

Word_shuffler::Word_shuffler() noexcept : m_rand_device{}, m_rand_engine(m_rand_device()) {}

void Word_shuffler::shuffle(std::vector<std::string>& words) noexcept
{
    std::uniform_int_distribution<> distribution(0, words.size() - 1);

    std::shuffle(words.begin(), words.end(), m_rand_engine);
}


} // namespace st

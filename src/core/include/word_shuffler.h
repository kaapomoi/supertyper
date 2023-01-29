#ifndef SUPERTYPER_WORD_SHUFFLER_H
#define SUPERTYPER_WORD_SHUFFLER_H

#include <cstdint>
#include <random>
#include <string>
#include <vector>

namespace st {

class Word_shuffler {
public:
    Word_shuffler() noexcept;

    void shuffle(std::vector<std::string>& words) noexcept;

private:
    std::random_device m_rand_device;
    std::mt19937 m_rand_engine;
};

} // namespace st

#endif

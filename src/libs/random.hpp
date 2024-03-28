#ifndef LIBS_RANDOM_HPP
#define LIBS_RANDOM_HPP

#include <random>

auto random(int min, int max) -> int {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(min, max);
    return dist(gen);
}

#endif

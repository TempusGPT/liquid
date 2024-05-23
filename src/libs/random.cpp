#include "random.hpp"

#include <random>

auto random(int min, int max) -> int {
    static auto device = std::random_device();
    static auto engine = std::mt19937(device());
    auto dist = std::uniform_int_distribution(min, max);
    return dist(engine);
}

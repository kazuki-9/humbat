#include "landscape.h"
#include <random>

landscape::landscape(
    const unsigned x_map,
    const unsigned y_map)
    : x_map(x_map), y_map(y_map) {
    std::random_device rd;     // Only used once to initialise (seed) engine
    std::mt19937 rng(rd());    // Random-number engine used (Mersenne-Twister in this case)
    std::uniform_int_distribution<int> uni_x(0, x_map - 1); // https://stackoverflow.com/questions/5008804/how-do-you-generate-uniformly-distributed-random-integers
    std::uniform_int_distribution<int> uni_y(0, y_map - 1);
}


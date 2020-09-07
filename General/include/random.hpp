#ifndef HEROES_OF_EANDOM_RANDOM_HPP
#define HEROES_OF_EANDOM_RANDOM_HPP

#include <cstdlib>
#include <cassert>
#include <exception>
#include <vector>
#include <array>

class RandomGenerator {
public:
    static void set_seed(unsigned int seed) {
        srand(seed);
    }
    // low included, high excluded
    static int64_t randint(int64_t low, int64_t high) {
        assert(high > low);
        return (rand() % (high - low)) + low;
    }

    static int64_t randint(int64_t high) {
        return randint(0, high);
    }

    template<typename T>
    static T sample(const std::vector<T>& arr) {
        return arr[randint(arr.size())];
    }

    template<typename T, size_t N>
    static T sample(const std::array<T, N>& arr) {
        return arr[static_cast<size_t>(randint((arr.size())))];
    }
};

#endif //HEROES_OF_EANDOM_RANDOM_HPP

#ifndef HEROES_OF_EANDOM_RANDOM_HPP
#define HEROES_OF_EANDOM_RANDOM_HPP

#include <cstdlib>
#include <cassert>
#include <exception>
#include <vector>
#include <array>

class RandomGenerator {
    // low included, high excluded
    int64_t randint(int64_t low, int64_t high) {
        assert(high > low);
        return (rand() % (high - low)) + low;
    }

    int64_t randint(int64_t high) {
        return randint(0, high);
    }

    template<typename T>
    T sample(std::vector<T> arr) {
        return arr[randint(arr.size())];
    }

    template<typename T, int N>
    T sample(std::array<T, N> arr) {
        return arr[randint(arr.size())];
    }
};

#endif //HEROES_OF_EANDOM_RANDOM_HPP

#ifndef HEROES_OF_RANDOM_RANDOM_HPP
#define HEROES_OF_RANDOM_RANDOM_HPP

#include <cstdlib>
#include <cassert>
#include <exception>
#include <vector>
#include <array>

class RandomGenerator {
public:
    RandomGenerator() = delete;

    static void set_seed(unsigned int seed) {
        srand(seed);
    }
    // low included, high excluded
    static int64_t randint(int64_t low, int64_t high) {
        assert(high > low);
        return (rand() % (high - low)) + low;
    }

    static size_t randuint(size_t low, size_t high) {
        assert(high > low);
        return (static_cast<size_t>(rand()) % (high - low)) + low;
    }

    static int64_t randint(int64_t high) {
        return randint(0, high);
    }

    template<typename T>
    static const T& sample(const std::vector<T>& arr) {
        return arr[static_cast<size_t>(randint(static_cast<int64_t >(arr.size())))];
    }

    template<typename T>
    static void shuffle(std::vector<T>& arr) {
        for (size_t i = 0; i < arr.size(); ++i) {
            size_t j = randuint(i, arr.size());
            std::swap<T>(arr[i], arr[j]);
        }
    }

    template<typename T, size_t N>
    static const T& sample(const std::array<T, N>& arr) {
        return arr[static_cast<size_t>(randint((arr.size())))];
    }
};

#endif //HEROES_OF_RANDOM_RANDOM_HPP

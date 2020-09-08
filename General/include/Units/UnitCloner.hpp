//
// Created by fedor on 9/8/20.
//

#ifndef HEROES_OF_RANDOM_UNITCLONER_HPP
#define HEROES_OF_RANDOM_UNITCLONER_HPP

#include "UnitGroup.hpp"

class Cloner {
    friend class UnitEditor;
public:
    Cloner(UnitGroup reference, int64_t cost)
    : cost(cost), reference(std::move(reference)){}

    UnitGroup create(int64_t count) {
        auto copy = reference;
        copy.count = count;
        return copy;
    }

    [[nodiscard]] const UnitGroup& getReference() const {
        return reference;
    }

    int64_t getCost() const {
        return cost;
    }
private:
    int64_t cost;
    UnitGroup reference;
};

#endif //HEROES_OF_RANDOM_UNITCLONER_HPP

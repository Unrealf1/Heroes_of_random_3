//
// Created by fedor on 9/8/20.
//

#ifndef HEROES_OF_RANDOM_ARCHER_HPP
#define HEROES_OF_RANDOM_ARCHER_HPP

#include "BaseFactory.hpp"

class ArcherFactory: public BaseFactory {
public:
    UnitGroup Create(int64_t number) override {
        return UnitGroup(
                12,
                2,
                5,
                0,
                7,
                "Archers",
                number
        );
    }

    int64_t GetPrice() const override {
        return 10;
    }
};

#endif //HEROES_OF_RANDOM_ARCHER_HPP
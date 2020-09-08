//
// Created by fedor on 9/8/20.
//

#ifndef HEROES_OF_RANDOM_SWORDSMAN_HPP
#define HEROES_OF_RANDOM_SWORDSMAN_HPP

#include "BaseFactory.hpp"

class SwordsmanFactory: public BaseFactory {
public:
    UnitGroup Create(int64_t number) override {
        return UnitGroup(
            12,
            5,
            15,
            1,
            3,
            "Swordsmen",
            number
        );
    }

    int64_t GetPrice() const override {
        return 20;
    }
};

#endif //HEROES_OF_RANDOM_SWORDSMAN_HPP

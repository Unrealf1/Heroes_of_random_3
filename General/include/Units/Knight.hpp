//
// Created by fedor on 9/8/20.
//

#ifndef HEROES_OF_RANDOM_KNIGHT_HPP
#define HEROES_OF_RANDOM_KNIGHT_HPP

#include "BaseFactory.hpp"

class KnightFactory: public BaseFactory {
public:
    UnitGroup Create(int64_t number) override {
        return UnitGroup(
                30,
                4,
                6,
                2,
                1,
                "Knights",
                number
        );
    }

    int64_t GetPrice() const override {
        return 40;
    }
};

#endif //HEROES_OF_RANDOM_KNIGHT_HPP

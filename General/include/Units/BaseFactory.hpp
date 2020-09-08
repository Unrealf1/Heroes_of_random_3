//
// Created by fedor on 9/8/20.
//

#ifndef HEROES_OF_RANDOM_BASEFACTORY_HPP
#define HEROES_OF_RANDOM_BASEFACTORY_HPP

#include "UnitGroup.hpp"

class BaseFactory {
public:
    virtual ~BaseFactory() = default;
    virtual UnitGroup Create(int64_t number) = 0;
    virtual int64_t GetPrice() const = 0;
};

#endif //HEROES_OF_RANDOM_BASEFACTORY_HPP

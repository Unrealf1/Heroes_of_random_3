//
// Created by fedor on 9/8/20.
//

#ifndef HEROES_OF_RANDOM_ARMY_HPP
#define HEROES_OF_RANDOM_ARMY_HPP

#include <deque>
#include <utility>
#include <vector>
#include "UnitGroup.hpp"


class Army {
public:
    explicit Army(std::vector<UnitGroup> groups = {});

    UnitGroup& getCurrent();

    void Cycle();

    size_t GroupsLeft() const;

    bool Defeated() const;

    size_t GetCurrentIndex() const;

    ~Army();

    std::vector<UnitGroup> composition;

    void clear();

    std::string name = "Enemy";
private:
    size_t current_index = 0;
};

#endif //HEROES_OF_RANDOM_ARMY_HPP

//
// Created by fedor on 9/8/20.
//

#ifndef HEROES_OF_RANDOM_ARMY_HPP
#define HEROES_OF_RANDOM_ARMY_HPP

#include <deque>
#include <vector>
#include "UnitGroup.hpp"

class Army {
public:
    explicit Army(std::vector<UnitGroup>& groups)
    :composition(groups) {

    }

    UnitGroup& getCurrent() {
        return composition[current_index];
    }

    void Cycle() {
        if (Defeated()) {
            return;
        }

        do {
            current_index = (current_index + 1) % composition.size();
        } while(!composition[current_index].IsAlive());
    }

    size_t GroupsLeft() const {
        size_t cnt = 0;
        for (auto& group : composition) {
            if (group.IsAlive()) {
                ++cnt;
            }
        }
        return cnt;
    }

    bool Defeated() const {
        return GroupsLeft() == 0;
    }

    size_t GetCurrentIndex() const {
        return current_index;
    }

    std::vector<UnitGroup>& composition;

private:
    size_t current_index = 0;
};

#endif //HEROES_OF_RANDOM_ARMY_HPP
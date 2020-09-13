//
// Created by fedor on 9/13/20.
//

#include "Army.hpp"

Army::Army(std::vector<UnitGroup> groups):composition(std::move(groups)) {
    for (auto& group : composition) {
        group.army = this;
    }
}

UnitGroup &Army::getCurrent() {
    return composition[current_index];
}

void Army::Cycle() {
    if (Defeated()) {
        return;
    }

    do {
        current_index = (current_index + 1) % composition.size();
    } while(!composition[current_index].IsAlive());
}

size_t Army::GroupsLeft() const {
    size_t cnt = 0;
    for (auto& group : composition) {
        if (group.IsAlive()) {
            ++cnt;
        }
    }
    return cnt;
}

bool Army::Defeated() const {
    return GroupsLeft() == 0;
}

size_t Army::GetCurrentIndex() const {
    return current_index;
}

Army::~Army() {
    for (auto& group : composition) {
        group.army = nullptr;
    }
}

void Army::clear() {
    for (size_t i = 0; i < composition.size(); ++i) {
        if (!composition[i].IsAlive()) {
            if (current_index == i) {
                Cycle();
            }
            if (current_index > i) {
                --current_index;
            }
            composition.erase(composition.begin() + static_cast<int64_t >(i));
        }
    }
}



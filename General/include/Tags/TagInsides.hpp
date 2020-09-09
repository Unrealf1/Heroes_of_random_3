//
// Created by fedor on 9/10/20.
//

#ifndef HEROES_OF_RANDOM_TAGINSIDES_HPP
#define HEROES_OF_RANDOM_TAGINSIDES_HPP

#include <UnitGroup.hpp>

struct TagInsides {
    actions_t actions_before_attack;
    post_actions_t actions_after_attack;
    actions_t actions_before_attacked;
    post_actions_t actions_after_attacked;
};




#endif //HEROES_OF_RANDOM_TAGINSIDES_HPP

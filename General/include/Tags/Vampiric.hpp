//
// Created by fedor on 9/10/20.
//

#ifndef HEROES_OF_RANDOM_VAMPIRIC_HPP
#define HEROES_OF_RANDOM_VAMPIRIC_HPP

#include <string>
#include "TagInsides.hpp"

struct Vampiric {
    inline const static std::string name = "vampiric";
    inline const static TagInsides insides = {
            {},
            {post_action_t([](UnitGroup* me, Army*, UnitGroup* target, int64_t dmg){
                auto percent = RandomGenerator::randint(101);
                auto heal = percent * dmg / 100;
                me->heal(heal);
                Output::LogAbility(fmt::format(
                        "{} drained life from {} and restored {} hp!",
                        me->name,
                        target->name,
                        heal));
            })},
            {},
            {}
    };
};

#endif //HEROES_OF_RANDOM_VAMPIRIC_HPP

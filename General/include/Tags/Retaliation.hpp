//
// Created by fedor on 9/10/20.
//

#ifndef HEROES_OF_RANDOM_RETALIATION_HPP
#define HEROES_OF_RANDOM_RETALIATION_HPP

#include <string>
#include "TagInsides.hpp"

struct Retaliation {
    inline const static std::string name = "retaliation";
    inline const static TagInsides insides = {
            {},
            {},
            {},
            {post_action_t([](UnitGroup* me, UnitGroup* target, int64_t){
                auto dmg = me->doAttack(*target);
                Output::LogAbility(fmt::format(
                        "{} retaliated upon {} and dealed {} damage!",
                        me->name,
                        target->name,
                        dmg));
            })}
    };
};

#endif //HEROES_OF_RANDOM_RETALIATION_HPP

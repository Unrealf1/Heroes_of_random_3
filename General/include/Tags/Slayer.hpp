//
// Created by fedor on 9/20/20.
//

#ifndef HEROES_OF_RANDOM_SLAYER_HPP
#define HEROES_OF_RANDOM_SLAYER_HPP

#include <string>
#include "TagInsides.hpp"
#include "Army.hpp"

struct Slayer {
    inline const static std::string name = "slayer";
    inline const static TagInsides insides = {
            {},
            {post_action_t([](UnitGroup* me, UnitGroup* target, int64_t dmg){
                if (target->has_tag("hero")) {
                    auto additional = dmg * 10 / 100;
                    target->doTakeDamage(additional);
                    Output::LogAbility(fmt::format(
                            "{} dealed {} additional damage to {}!",
                            me->name,
                            additional,
                            target->name));
                }
            })},
            {},
            {}
    };
};

#endif //HEROES_OF_RANDOM_SLAYER_HPP

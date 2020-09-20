//
// Created by fedor on 9/20/20.
//

#ifndef HEROES_OF_RANDOM_MASSHEAL_HPP
#define HEROES_OF_RANDOM_MASSHEAL_HPP

#include <string>
#include "TagInsides.hpp"
#include "Army.hpp"

struct MassHeal {
    inline const static std::string name = "mass heal";
    inline const static TagInsides insides = {
            {action_t([](UnitGroup* me, UnitGroup*){
                auto alive = me->army->getAlive();
                auto amount = RandomGenerator::randint(1, 100);
                for (auto unit : alive) {
                    unit->heal(amount);
                }
                Output::LogAbility(fmt::format(
                        "{} healed all allies for {} hp!",
                        me->name,
                        amount));
            })},
            {},
            {},
            {}
    };
};

#endif //HEROES_OF_RANDOM_MASSHEAL_HPP

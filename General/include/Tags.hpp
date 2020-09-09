//
// Created by fedor on 9/9/20.
//

#ifndef HEROES_OF_RANDOM_TAGS_HPP
#define HEROES_OF_RANDOM_TAGS_HPP

#include <string>
#include "UnitGroup.hpp"
#include <map>



struct TagInsides {
    actions_t actions_before_attack;
    actions_t actions_after_attack;
    actions_t actions_before_attacked;
    actions_t actions_after_attacked;
};

struct Retaliation {
    inline const static std::string name = "retaliation";
    inline const static TagInsides insides = {
            {},
            {},
            {},
            {action_t([](UnitGroup* me, Army* army, UnitGroup* target){
                (void)army;
                auto dmg = me->doAttack(*target);
                Output::LogAbility(fmt::format(
                        "{} retaliated upon {} and dealed {} damage!",
                        me->name,
                        target->name,
                        dmg));
            })}
    };
};

class TagContainer {
public:
    using tag_t = std::string;

    static void populateActions(
            const tag_t& tag,
            ActionPack& actions) {
        const auto& insides = actual_tags.at(tag);
        actions.before_attack = insides.actions_before_attack;
        actions.after_attack = insides.actions_after_attack;
        actions.before_attacked = insides.actions_before_attacked;
        actions.after_attacked = insides.actions_after_attacked;
    }

    inline const static std::map<tag_t, TagInsides> actual_tags = {
            {Retaliation::name, Retaliation::insides}
    };
};

#endif //HEROES_OF_RANDOM_TAGS_HPP

#ifndef HEROES_OF_RANDOM_UNITGROUP_HPP
#define HEROES_OF_RANDOM_UNITGROUP_HPP

#include <cstdlib>
#include <algorithm>
#include <string>
#include <utility>
#include <fmt/core.h>

#include "Interaction/Output.hpp"
#include "Random.hpp"

using rnd = RandomGenerator;

class Army;
class UnitGroup;

using action_t = std::function<void(UnitGroup*, Army*, UnitGroup*)>;
using actions_t = std::vector<action_t>;

struct ActionPack {
    actions_t before_attack;
    actions_t after_attack;
    actions_t before_attacked;
    actions_t after_attacked;
};

class UnitGroup {
    friend class Cloner;
    friend class UnitSerializer;
public:
    UnitGroup(
            int64_t hp,
            int64_t min_damage,
            int64_t max_damage,
            int64_t armor,
            int64_t speed,
            std::string name,
            int64_t count=0,
            std::vector<std::string> tags = {},
            ActionPack actions = {}
        )
        : hp(hp),
          min_damage(min_damage),
          max_damage(max_damage),
          armor(armor),
          speed(speed),
          name(std::move(name)),
          count(count),
          top_hp(hp),
          tags(std::move(tags)),
          actions(std::move(actions)){}

    int64_t Attack(UnitGroup& target) {
        for (auto& action : actions.before_attack) {
            action(this, army, &target);
        }
        for (auto& action : target.actions.before_attacked) {
            action(&target, army, this);
        }

        auto dmg = doAttack(target);
        Output::LogAttack(name, target.name, dmg);

        for (auto& action : target.actions.after_attacked) {
            action(&target, army, this);
        }
        for (auto& action : actions.after_attack) {
            action(this, army, &target);
        }
        return dmg;
    }

    void TakeDamage(int64_t dmg) {
        doTakeDamage(dmg);
    }

    bool IsAlive() const {
        return count > 0;
    }

    int64_t GetCount() const {
        return count;
    }

    int64_t GetTopHp() const {
        return top_hp;
    }

    Army* army = nullptr;

    int64_t hp;
    int64_t min_damage;
    int64_t max_damage;
    int64_t armor;
    int64_t speed;

    std::string name;

    int64_t doAttack(UnitGroup& target) {
        int64_t total_dmg = 0;
        for (int64_t i = 0; i < count; ++i) {
            total_dmg += std::max<int64_t>(rnd::randint(min_damage, max_damage+1) - target.armor, 0);
        }
        target.TakeDamage(total_dmg);
        return total_dmg;
    }

    void doTakeDamage(int64_t dmg) {
        // First
        if (top_hp < hp) {
            if (dmg < top_hp) {
                top_hp -= dmg;
                dmg = 0;
            }
            else {
                dmg -= top_hp;
                top_hp = hp;
                count--;
            }
        }

        // Mid
        int64_t killed = dmg / hp;
        count -= killed;
        count = std::max<int64_t>(count, 0);
        dmg -= killed*hp;

        // Last
        top_hp -= dmg;
    }
private:
    int64_t count;
    int64_t top_hp;
public:
    std::vector<std::string> tags;
private:
    ActionPack actions;
};


#endif //HEROES_OF_EANDOM_UNITS_HPP
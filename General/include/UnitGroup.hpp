#ifndef HEROES_OF_RANDOM_UNITGROUP_HPP
#define HEROES_OF_RANDOM_UNITGROUP_HPP

#include <cstdlib>
#include <algorithm>
#include <string>
#include <utility>
#include <fmt/core.h>

#include "Interaction/Output.hpp"
#include "Random.hpp"
//#include "Army.hpp"

using rnd = RandomGenerator;

class Army;
class UnitGroup;

using action_t = std::function<void(UnitGroup*, Army*, UnitGroup*)>;
using post_action_t = std::function<void(UnitGroup*, Army*, UnitGroup*, int64_t)>;
using actions_t = std::vector<action_t>;
using post_actions_t = std::vector<post_action_t>;

struct ActionPack {
    actions_t before_attack;
    post_actions_t after_attack;
    actions_t before_attacked;
    post_actions_t after_attacked;
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
    );

    int64_t Attack(UnitGroup& target, const std::string &my_army_name, const std::string &enemy_army_name);

    void TakeDamage(int64_t dmg);

    bool IsAlive() const;

    int64_t GetCount() const;

    int64_t GetTopHp() const;

    Army* army = nullptr;

    int64_t hp;
    int64_t min_damage;
    int64_t max_damage;
    int64_t armor;
    int64_t speed;

    std::string name;

    int64_t doAttack(UnitGroup& target);

    void doTakeDamage(int64_t dmg);

    void heal(int64_t amount);
private:
    int64_t count;
    int64_t top_hp;
public:
    std::vector<std::string> tags;
private:
    ActionPack actions;
};


#endif //HEROES_OF_EANDOM_UNITS_HPP

#ifndef HEROES_OF_RANDOM_UNITGROUP_HPP
#define HEROES_OF_RANDOM_UNITGROUP_HPP

#include <cstdlib>
#include <algorithm>
#include <string>
#include <utility>
#include <fmt/core.h>

#include "Random.hpp"

using rnd = RandomGenerator;

class UnitGroup {
public:
    UnitGroup(
            int64_t hp,
            int64_t min_damage,
            int64_t max_damage,
            int64_t armor,
            int64_t speed,
            std::string name,
            int64_t count=0
        )
        : name(std::move(name)),
          hp(hp),
          min_damage(min_damage),
          max_damage(max_damage),
          armor(armor),
          speed(speed),
          count(count),
          top_hp(hp) {
    }

    UnitGroup(const UnitGroup&) = default;
    UnitGroup(UnitGroup&&) = default;
    UnitGroup& operator=(const UnitGroup&)=default;
    UnitGroup& operator=(UnitGroup&&)=default;

    int64_t Attack(UnitGroup& target) {
        int64_t total_dmg = 0;
        for (int64_t i = 0; i < count; ++i) {
            total_dmg += std::max<int64_t>(rnd::randint(min_damage, max_damage+1) - target.armor, 0);
        }
        target.TakeDamage(total_dmg);
        return total_dmg;
    }

    void TakeDamage(int64_t dmg) {
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

    bool IsAlive() const {
        return count > 0;
    }

    int64_t GetCount() {
        return count;
    }

    int64_t GetTopHp() {
        return top_hp;
    }

    std::string name;

    int64_t hp;
    int64_t min_damage;
    int64_t max_damage;
    int64_t armor;
    int64_t speed;

    int64_t count;
    int64_t top_hp;
};

#endif //HEROES_OF_EANDOM_UNITS_HPP

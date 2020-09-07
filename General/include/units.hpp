#ifndef HEROES_OF_EANDOM_UNITS_HPP
#define HEROES_OF_EANDOM_UNITS_HPP

#include <cstdlib>
#include <algorithm>
#include <string>
#include <utility>

class Unit {
 public:
    Unit(int64_t hp, int64_t min_damage, int64_t max_damage,int64_t armor, int64_t speed,
        std::string name,
        int64_t count=0):
        count(count), top_hp(hp),
        hp(hp), min_damage(min_damage), max_damage(max_damage), armor(armor), speed(speed),
        name(std::move(name)) {
    }

    void Attack(Unit* target) {
        target->armor;
        int64_t total_dmg = 0;
        for (int i = 0; i < count; ++i) {
            total_dmg += std::max<int64_t >(random() - target->armor, 0);
        }
        target->TakeDamage(total_dmg);
    }


    void TakeDamage(int64_t dmg) {
        // First
        if (top_hp < hp) {
            if (dmg < top_hp) {
                top_hp -= dmg;
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

    bool IsAlive() {
        return count > 0;
    }

    int64_t count;
    int64_t top_hp;

    const int64_t hp;
    const int64_t min_damage;
    const int64_t max_damage;
    const int64_t armor;
    const int64_t speed;

    const std::string name;
};

#endif //HEROES_OF_EANDOM_UNITS_HPP

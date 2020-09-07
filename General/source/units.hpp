#ifndef HEROES_OF_EANDOM_UNITS_HPP
#define HEROES_OF_EANDOM_UNITS_HPP

#include <cstdlib>

class Unit {
 public:
    Unit(int64_t hp, int64_t min_damage, int64_t max_damage,int64_t armor, int64_t speed,
        int64_t count=0)
        :
        count(count), top_hp(hp),
        hp(hp), min_damage(min_damage), max_damage(max_damage), armor(armor), speed(speed) {
    }

    void Attack(Unit* target) {
        target->armor;
        int64_t total_dmg = 0;
        for (int i = 0; i < count; ++i) {
            total_dmg += max(random() - target->armor, 0)
        }
    }


    void TakeDamage(size_t dmg);
    bool IsAlive();

    int64_t count;
    int64_t top_hp;

    const int64_t hp;
    const int64_t min_damage;
    const int64_t max_damage;
    const int64_t armor;
    const int64_t speed;

    const std::string
};

#endif //HEROES_OF_EANDOM_UNITS_HPP

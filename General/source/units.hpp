#ifndef HEROES_OF_EANDOM_UNITS_HPP
#define HEROES_OF_EANDOM_UNITS_HPP

#include <cstdio>

class Unit {
 public:
    Unit(size_t hp, size_t dmg, size_t armor);

    void Attack(Unit* target);
    void TakeDamage(size_t dmg);
    bool IsAlive();

    size_t count;
    size_t top_hp;

    const size_t hp;
    const size_t damage;
    const size_t armor;
};

#endif //HEROES_OF_EANDOM_UNITS_HPP

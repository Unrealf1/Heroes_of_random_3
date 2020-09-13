//
// Created by fedor on 9/13/20.
//

#include "UnitGroup.hpp"

void UnitGroup::doTakeDamage(int64_t dmg) {
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

void UnitGroup::heal(int64_t amount) {
    top_hp = std::min(hp, top_hp + amount);
}

int64_t UnitGroup::doAttack(UnitGroup &target) {
    int64_t total_dmg = 0;
    for (int64_t i = 0; i < count; ++i) {
        total_dmg += std::max<int64_t>(rnd::randint(min_damage, max_damage+1) - target.armor, 0);
    }
    target.TakeDamage(total_dmg);
    return total_dmg;
}

int64_t UnitGroup::GetTopHp() const {
    return top_hp;
}

int64_t UnitGroup::GetCount() const {
    return count;
}

bool UnitGroup::IsAlive() const {
    return count > 0;
}

void UnitGroup::TakeDamage(int64_t dmg) {
    doTakeDamage(dmg);
}

UnitGroup::UnitGroup(int64_t hp, int64_t min_damage, int64_t max_damage, int64_t armor, int64_t speed, std::string name,
                     int64_t count, std::vector<std::string> tags, ActionPack actions) : hp(hp),
                                                                                         min_damage(min_damage),
                                                                                         max_damage(max_damage),
                                                                                         armor(armor),
                                                                                         speed(speed),
                                                                                         name(std::move(name)),
                                                                                         count(count),
                                                                                         top_hp(hp),
                                                                                         tags(std::move(tags)),
                                                                                         actions(std::move(actions)){}

int64_t UnitGroup::Attack(UnitGroup &target, const std::string &my_army_name, const std::string &enemy_army_name) {
    for (auto& action : actions.before_attack) {
        action(this, army, &target);
    }
    for (auto& action : target.actions.before_attacked) {
        action(&target, army, this);
    }

    auto dmg = doAttack(target);
    Output::LogAttack(
            fmt::format("{} {}", my_army_name, name),
            fmt::format("{} {}", enemy_army_name, target.name),
            dmg);

    for (auto& action : target.actions.after_attacked) {
        action(&target, army, this, dmg);
    }
    for (auto& action : actions.after_attack) {
        action(this, army, &target, dmg);
    }
    return dmg;
}


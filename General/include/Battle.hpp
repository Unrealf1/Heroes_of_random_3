//
// Created by fedor on 9/8/20.
//

#ifndef HEROES_OF_RANDOM_BATTLE_HPP
#define HEROES_OF_RANDOM_BATTLE_HPP

#include "Army.hpp"
#include "Interaction/Output.hpp"

struct TestInfo {
    int64_t first_army_left = 0;
    int64_t second_army_left = 0;
};

class Battle {
public:
    static bool Start(Army& player, Army& enemy, TestInfo* info = nullptr) {
        while(!player.Defeated() && !enemy.Defeated()) {
            auto& player_top = player.getCurrent();
            auto& enemy_top = enemy.getCurrent();

            if (player_top.speed == enemy_top.speed) {
                bool coin_flip = RandomGenerator::randint(2);
                if (coin_flip) {
                    Round(player_top, enemy_top);
                } else {
                    Round(enemy_top, player_top);
                }
            } else if (player_top.speed > enemy_top.speed) {
                Round(player_top, enemy_top);
            } else {
                Round(enemy_top, player_top);
            }
            player.Cycle();
            enemy.Cycle();

            LogBattleStatus(player, enemy);
            player.clear();
            enemy.clear();
        }
        if (info != nullptr) {
            info->first_army_left = 0;
            for (auto& group : player.composition) {
                info->first_army_left += group.GetCount();
            }
            info->second_army_left = 0;
            for (auto& group : enemy.composition) {
                info->second_army_left += group.GetCount();
            }
        }
        return !player.Defeated();
    }

private:
    static void Round(UnitGroup& first, UnitGroup& second) {
        auto were_first = first.GetCount();
        auto were_second = second.GetCount();
        first.Attack(second, first.army->name, second.army->name);
        second.Attack(first, second.army->name, first.army->name);
        Output::LogRound(
                first.name,
                second.name,
                were_first,
                were_second,
                were_first - first.GetCount(),
                were_second - second.GetCount()
        );
        if (!first.IsAlive()) {
            Output::LogDeath(first.name);
        }

        if (!second.IsAlive()) {
            Output::LogDeath(second.name);
        }
    }

    // Should use stringbuilder
    static void LogBattleStatus(const Army& player, const Army& enemy) {
        std::string to_log = fmt::format("Current disposition:\n{}: ", player.name);
        for (size_t i = 0; i < player.composition.size(); ++i) {
            auto& group = player.composition[
                    (i + player.GetCurrentIndex()) % player.composition.size()
            ];
            groupToString(group, to_log);
        }
        to_log += fmt::format("\n{}: ", enemy.name);
        for (size_t i = 0; i < enemy.composition.size(); ++i) {
            auto& group = enemy.composition[
                    (i + enemy.GetCurrentIndex()) % enemy.composition.size()
            ];
            groupToString(group, to_log);
        }
        Output::LogInBattle(to_log, fmt::color::lemon_chiffon);
    }

    static void groupToString(const UnitGroup& group, std::string& to_log) {
        if (group.IsAlive()) {
            if (group.GetCount() > 5) {
                to_log += fmt::format("{}({} left)  ", group.name, group.GetCount());
            } else {
                to_log += fmt::format("{}({} left [{}/{}])", group.name, group.GetCount(), group.GetTopHp(), group.hp);
            }
        }
    }
};

#endif //HEROES_OF_RANDOM_BATTLE_HPP

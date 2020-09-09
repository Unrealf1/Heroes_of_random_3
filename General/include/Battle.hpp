//
// Created by fedor on 9/8/20.
//

#ifndef HEROES_OF_RANDOM_BATTLE_HPP
#define HEROES_OF_RANDOM_BATTLE_HPP

#include "Army.hpp"
#include "Interaction/Output.hpp"

class Battle {
public:
    static bool Start(Army& player, Army& enemy) {
        player.is_player = true;
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
        }
        if (player.Defeated()) {
            Output::LogLoss();
            return false;
        } else {
            Output::LogVictory();
            return true;
        }
    }

private:
    static void Round(UnitGroup& first, UnitGroup& second) {
        auto were_first = first.GetCount();
        auto were_second = second.GetCount();
        first.Attack(second, first.army->is_player);
        second.Attack(first, second.army->is_player);
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
        if (!Output::battle_logging) {return;}

        std::string to_log = "Current disposition:\nPlayer: ";
        for (size_t i = 0; i < player.composition.size(); ++i) {
            auto& group = player.composition[
                    (i + player.GetCurrentIndex()) % player.composition.size()
            ];
            if (group.IsAlive()) {
                to_log += fmt::format("{}({} left)  ", group.name, group.GetCount());
            }
        }
        to_log += "\nEnemy: ";
        for (size_t i = 0; i < enemy.composition.size(); ++i) {
            auto& group = enemy.composition[
                    (i + enemy.GetCurrentIndex()) % enemy.composition.size()
            ];
            if (group.IsAlive()) {
                to_log += fmt::format("{}({} left)  ", group.name, group.GetCount());
            }
        }
        Output::LogLine(to_log, fmt::color::lemon_chiffon);
    }
};

#endif //HEROES_OF_RANDOM_BATTLE_HPP

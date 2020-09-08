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
        while(!player.Defeated() && !enemy.Defeated()) {
            auto& player_top = player.getCurrent();
            auto& enemy_top = enemy.getCurrent();

            if (player_top.speed > enemy_top.speed) {
                Round(player_top, enemy_top);
            } else {
                Round(enemy_top, player_top);
            }
            player.Cycle();
            enemy.Cycle();
            Output::LogBattleStatus(player, enemy);
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
        auto dmg1 = first.Attack(second);
        Output::LogAttack(first.name, second.name, dmg1);
        auto dmg2 = second.Attack(first);
        Output::LogAttack(second.name, first.name, dmg2);
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
};

#endif //HEROES_OF_RANDOM_BATTLE_HPP

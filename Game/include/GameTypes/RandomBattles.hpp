//
// Created by fedor on 9/8/20.
//

#ifndef HEROES_OF_RANDOM_RANDOMBATTLES_HPP
#define HEROES_OF_RANDOM_RANDOMBATTLES_HPP

#include <cstdint>
#include <utility>
#include <vector>
#include <string>
#include "Units/UnitCloner.hpp"
#include "Interaction/Input.hpp"
#include "Battle.hpp"
#include "BaseGameType.hpp"

class RandomBattles: BaseGameType {
public:
    RandomBattles(std::vector<Cloner*> cloners, int64_t initial_money)
    : BaseGameType(std::move(cloners)), initial_money(initial_money){}
    void Start() {
        auto offer = getOffer(cloners);
        std::vector<UnitGroup> playerUnits;
        auto current_money = initial_money;
        std::function<void(std::string)> dispatcher([this, &current_money, &playerUnits](std::string choice) {
            for (auto& f : cloners) {
                if (f->getReference().name == choice) {
                    int64_t num = Input::AskForInt("How many?");

                    auto total_cost = num * f->getCost();
                    if (total_cost > current_money) {
                        Output::LogInfo("Sorry, not enough money");
                    } else {
                        if (Input::Confirm(fmt::format("Total cost is {}. Are you sure? (yes/no)", total_cost),
                                           fmt::color::white)) {
                            current_money -= total_cost;
                            playerUnits.push_back(f->create(num));
                        }
                    }
                    break;
                }
            }
        });
        Input::ChoiceActionWithFinish(
                dispatcher,
                std::function<std::string(void)>([&]{
                    return fmt::format(
                            "You have {} money. Choose units to buy. Available:\n{}",
                            current_money,
                            offer);
                }),
                fmt::color::white,
                getNames(cloners));

        Army army(playerUnits);
        army.name = "Player";
        Play(army);
    }
private:
    const int64_t initial_money;

    void Play(Army& player) {
        // Enemy boost and win condition should be moved to parameters
        auto enemy_cost = initial_money + 50;
        Output::LogInfo(fmt::format("Be ready for the first battle!"));
        while (enemy_cost > 10) {
            auto enemy_dudes = generateArmy(enemy_cost);
            Army enemy(enemy_dudes);
            if (!Battle::Start(player, enemy)) {
                Output::LogLoss();
                return;
            }
            Output::LogVictory();
            Output::LogInfo(fmt::format("Be ready for the next battle!"));
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            enemy_cost -= std::max(50l, static_cast<int64_t>(0.1* static_cast<double>(enemy_cost)));
        }
    }


    std::vector<Cloner*> getAffordable(int64_t money) {
        std::vector<Cloner*> affordable_factories;
        for (auto& f : cloners) {
            if (f->getCost() <= money) {
                affordable_factories.push_back(f);
            }
        }
        return affordable_factories;
    }

    std::vector<UnitGroup> generateArmy(int64_t cost) {
        auto affordable = getAffordable(cost);
        std::vector<UnitGroup> dudes;
        while (!affordable.empty()) {
            auto& choice = RandomGenerator::sample(affordable);
            auto num = RandomGenerator::randint(1, cost / choice->getCost() + 1);
            if (num == 0) {
                continue;
            }
            dudes.push_back(choice->create(num));
            cost -= choice->getCost() * num;
            affordable = getAffordable(cost);
        }
        return dudes;
    }
};

#endif //HEROES_OF_RANDOM_RANDOMBATTLES_HPP

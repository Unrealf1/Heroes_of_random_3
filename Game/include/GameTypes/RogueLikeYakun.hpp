//
// Created by yakun on 9/8/2020.
//

#ifndef HEROES_OF_RANDOM_ROGUELIKEYAKUN_HPP
#define HEROES_OF_RANDOM_ROGUELIKEYAKUN_HPP

#include <cstdint>
#include <utility>
#include <vector>
#include <string>
#include "Units/UnitCloner.hpp"
#include "Interaction/Input.hpp"
#include "Battle.hpp"

class RogueLike: BaseGameType {
public:
    RogueLike(
            std::vector<Cloner*>  cloners,
            int64_t initial_money,
            int64_t shuffle_price,
            int64_t enemy_budget_step
        )
        : BaseGameType(std::move(cloners)),
          initial_money(initial_money),
          shuffle_price(shuffle_price),
          enemy_budget_step(enemy_budget_step){}
    void Start() {
        auto non_hero = clonersWithoutTags(cloners, {"hero"});
        auto offer = getOffer(non_hero);
        Army player;
        std::string choice;
        int64_t current_money = 0;
        for (int stage = 1;; ++stage) {
            auto enemy_dudes = generateArmy(initial_money + enemy_budget_step*(stage - 1));
            Army enemy(enemy_dudes);
            for (auto& unit : enemy.composition) {
                unit.army = &enemy;
            }
            current_money += initial_money;

            Output::LogInfo(fmt::format("Stage {} started", stage));
            if (stage != 1) {
                Output::LogInfo("Your army:");
                LogArmy(player);
            }
            Output::LogInfo("Enemy army:");
            LogArmy(enemy);

            do {
                Output::LogInfo("");
                choice = Input::AskForChoiceWithFinish(
                        fmt::format(
                                "You have {} money. Choose units to buy. Available:\n{}",
                                current_money,
                                offer),
                        fmt::color::white,
                        getNames(non_hero),
                        "Please choose one of the given options"
                );

                if (choice == "Shuffle") {
                    if (current_money < shuffle_price) {
                        Output::LogInfo("Sorry, not enough money");
                        continue;
                    }
                    if (Input::Confirm(fmt::format(
                            "For {} positions of your units will be shuffled",
                            shuffle_price))) {
                        current_money -= shuffle_price;
                        RandomGenerator::shuffle(player.composition);
                        Output::LogInfo("Your army:");
                        LogArmy(Army(player.composition));
                    }
                    continue;
                }

                for (auto &f : cloners) {
                    if (f->getReference().name == choice) {
                        int64_t num = Input::AskForInt("How many?");
                        auto total_cost = num * f->getCost();
                        if (total_cost > current_money) {
                            Output::LogInfo("Sorry, not enough money");
                            break;
                        } else {
                            if (Input::Confirm(fmt::format("Total cost is {}. Are you sure?", total_cost))) {
                                current_money -= total_cost;
                                player.composition.push_back(f->create(num));
                                player.composition.back().army = &player;
                            }
                            break;
                        }
                    }
                }

            } while (choice != "finish");
            auto possible_score = getScore(enemy);
            if (!Battle::Start(player, enemy)) {
                Output::LogLoss();
                Output::LogLine(
                        fmt::format("You died on stage {}\nYour score is {}", stage, total_score),
                        fmt::color::forest_green);
                return;
            }
            total_score += possible_score;
            Output::LogVictory();
        }
    }
private:
    const int64_t initial_money;
    const int64_t shuffle_price;
    const int64_t enemy_budget_step;
    int64_t total_score = 0;

    std::vector<UnitGroup> generateArmy(int64_t cost) {
        auto affordable = getAffordable(cloners, cost);
        std::vector<UnitGroup> dudes;
        while (!affordable.empty()) {
            auto& choice = RandomGenerator::sample(affordable);
            auto num = RandomGenerator::randint(1, cost / choice->getCost() + 1);
            if (num == 0) {
                continue;
            }
            dudes.push_back(choice->create(num));
            cost -= choice->getCost() * num;
            affordable = getAffordable(affordable, cost);
        }
        return dudes;
    }

    static void LogArmy(const Army& army) {
        std::string to_log;
        for (size_t i = 0; i < army.composition.size(); ++i) {
            auto& group = army.composition[
                    (i + army.GetCurrentIndex()) % army.composition.size()
            ];
            if (group.IsAlive()) {
                to_log += fmt::format("{}({} left)  ", group.name, group.GetCount());
            }
        }
        Output::LogLine(to_log, fmt::color::white);
    }
};


#endif //HEROES_OF_RANDOM_ROGUELIKEYAKUN_HPP

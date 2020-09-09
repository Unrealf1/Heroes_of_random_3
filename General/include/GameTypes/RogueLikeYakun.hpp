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

class RogueLike {
public:
    RogueLike(
            std::vector<Cloner*>  cloners,
            int64_t initial_money,
            int64_t shuffle_price,
            int64_t enemy_budget_step
        )
        : cloners(std::move(cloners)),
          initial_money(initial_money),
          shuffle_price(shuffle_price),
          enemy_budget_step(enemy_budget_step){}
    void Start() {
        std::string pattern = "{} for {}";
        std::vector<std::string> available_units(cloners.size() + 1);

        std::string offer;
        for (size_t i = 0; i < cloners.size(); ++i) {
            available_units[i] = cloners[i]->create(1).name;
            offer += fmt::format(pattern, cloners[i]->create(1).name, cloners[i]->getCost()) + "\n";
        }
        available_units[cloners.size()] = "Shuffle";
        offer += fmt::format(pattern, "Shuffle", shuffle_price) + "\n";

        std::vector<UnitGroup> player_units;
        std::string choice;
        int64_t current_money = 0;
        for (int stage = 1;; ++stage) {
            auto enemy_dudes = generateArmy(initial_money + enemy_budget_step*(stage - 1));
            Army enemy(enemy_dudes);
            current_money += initial_money;

            Output::LogInfo(fmt::format("Stage {} started", stage));
            if (stage != 1) {
                Output::LogInfo("Your army:");
                LogArmy(Army(player_units));
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
                        available_units,
                        "Please choose one of the given options"
                );

                if (choice == "Shuffle") {
                    if (current_money < shuffle_price) {
                        Output::LogInfo("Sorry, not enough money");
                        continue;
                    }
                    auto confirmation = Input::AskForChoice(
                            fmt::format(
                                    "For {} positions of your units will be shuffled",
                                    shuffle_price),
                            fmt::color::white,
                            std::vector<std::string>{"yes", "no", "y", "n"});
                    if (confirmation == "y" || confirmation == "yes") {
                        current_money -= shuffle_price;
                        RandomGenerator::shuffle(player_units);
                        Output::LogInfo("Your army:");
                        LogArmy(Army(player_units));
                    }
                    continue;
                }

                for (auto &f : cloners) {
                    if (f->create(1).name == choice) {
                        int64_t num = Input::AskForInt("How many?");
                        auto total_cost = num * f->getCost();
                        if (total_cost > current_money) {
                            Output::LogInfo("Sorry, not enough money");
                            break;
                        } else {
                            auto confirmation = Input::AskForChoice(
                                    fmt::format("Total cost is {}. Are you sure? (yes/no)", total_cost),
                                    fmt::color::white,
                                    std::vector<std::string>{"yes", "no", "y", "n"});
                            if (confirmation == "y" || confirmation == "yes") {
                                current_money -= total_cost;
                                player_units.push_back(f->create(num));
                            }
                            break;
                        }
                    }
                }

            } while (choice != "finish");
            Army player(player_units);

            if (!Battle::Start(player, enemy)) {
                return;
            }
        }
    }
private:
    const std::vector<Cloner*> cloners;
    const int64_t initial_money;
    const int64_t shuffle_price;
    const int64_t enemy_budget_step;

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

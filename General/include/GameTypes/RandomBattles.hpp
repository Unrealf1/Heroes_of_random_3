//
// Created by fedor on 9/8/20.
//

#ifndef HEROES_OF_RANDOM_RANDOMBATTLES_HPP
#define HEROES_OF_RANDOM_RANDOMBATTLES_HPP

#include <cstdint>
#include <vector>
#include <string>
#include "Units/UnitFactories.hpp"
#include "Interaction/Input.hpp"
#include "Battle.hpp"

class RandomBattles {
public:
    RandomBattles(const std::vector<BaseFactory*>& factories, int64_t initial_money)
    : factories(factories), initial_money(initial_money){}
    void Start() {
        std::string pattern = "{} for {}";
        std::vector<std::string> available_units(factories.size() + 1);
        std::string offer;
        for (size_t i = 0; i < factories.size(); ++i) {
            available_units[i] = factories[i]->Create(1).name;
            offer += fmt::format(pattern, factories[i]->Create(1).name, factories[i]->GetPrice()) + "\n";
        }
        std::vector<UnitGroup> playerUnits;
        std::string choice;
        auto current_money = initial_money;
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

            for (auto& f : factories) {
                if (f->Create(1).name == choice) {
                    int64_t num = Input::AskForInt("How many?");
                    auto total_cost = num * f->GetPrice();
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
                            playerUnits.push_back(f->Create(num));
                        }
                        break;
                    }
                }
            }

        } while(choice != "finish");
        Army army(playerUnits);
        Play(army);
    }
private:
    const std::vector<BaseFactory*> factories;
    const int64_t initial_money;

    void Play(Army& player) {
        // Enemy boost and win condition should be moved to parameters
        auto enemy_cost = initial_money + 50;
        Output::LogInfo(fmt::format("Be ready for the first battle!"));
        while (enemy_cost > 10) {
            auto enemy_dudes = generateArmy(enemy_cost);
            Army enemy(enemy_dudes);
            if (!Battle::Start(player, enemy)) {
                return;
            }
            Output::LogInfo(fmt::format("Be ready for the next battle!"));
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            enemy_cost -= std::max(50l, static_cast<int64_t>(0.1* static_cast<double>(enemy_cost)));
        }
    }

    std::vector<BaseFactory*> getAffordable(int64_t money) {
        std::vector<BaseFactory*> affordable_factories;
        for (auto& f : factories) {
            if (f->GetPrice() <= money) {
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
            auto num = RandomGenerator::randint(1, cost / choice->GetPrice() + 1);
            if (num == 0) {
                continue;
            }
            dudes.push_back(choice->Create(num));
            cost -= choice->GetPrice() * num;
            affordable = getAffordable(cost);
        }
        return dudes;
    }
};

#endif //HEROES_OF_RANDOM_RANDOMBATTLES_HPP

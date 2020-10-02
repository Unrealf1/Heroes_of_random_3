//
// Created by fedor on 9/20/20.
//

#ifndef HEROES_OF_RANDOM_GAMETYPESELECTOR_HPP
#define HEROES_OF_RANDOM_GAMETYPESELECTOR_HPP

#include "GameTypes/Arena.hpp"
#include "GameTypes/RandomBattles.hpp"
#include "GameTypes/RogueLikeYakun.hpp"
#include "Interaction/Input.hpp"

class GameTypeSelector {
public:
    static void select(const std::vector<Cloner*>& all_cloners) {
        auto choice = Input::AskForChoice("Choose game type", fmt::color::wheat, names);
        auto to_settings = Input::Confirm("Do you want to change settings?");
        if (choice == battles_name) {
            RandomBattles battles(all_cloners, 400);
            battles.Start();
        } else if (choice == roguelike_name) {
            RogueLike rl(all_cloners, 400, 5, 100);
            rl.Start();
        } else if (choice == arena_name) {
            size_t num_battles = 3;
            size_t initial_money = 4000;
            size_t max_unit_cost = 500;
            size_t income = 0;
            while (to_settings) {
                auto choice = Input::AskForChoiceWithFinish(
                        fmt::format(
                        "Current settings:\n"
                        "Best of(num) = {}\n"
                        "Initial money(money) = {}\n"
                        "Max unit cost(max cost) = {}\n"
                        "Income(income) = {}\n"
                        "What would you like to change?",
                        num_battles, initial_money, max_unit_cost, income),
                                fmt::color::wheat,
                        {"num", "money", "max cost", "income"});

                if (choice == "finish") {
                    to_settings = false;
                } else if (choice == "num") {
                    num_battles = Input::AskForInt("Enter new value");
                } else if (choice == "money") {
                    initial_money = Input::AskForInt("Enter new value");
                } else if (choice == "max cost") {
                    max_unit_cost = Input::AskForInt("Enter new value");
                } else if (choice == "income") {
                    income = Input::AskForInt("Enter new value");
                }

            }
            Arena arena(all_cloners, num_battles, initial_money, max_unit_cost, income);
            arena.startLocal();
        }
    }

private:
    inline static const char* const arena_name = "Arena";
    inline static const char* const roguelike_name = "Roguelike";
    inline static const char* const battles_name = "Battles";

    const inline static std::vector<std::string> names{arena_name, roguelike_name, battles_name};
};

#endif //HEROES_OF_RANDOM_GAMETYPESELECTOR_HPP

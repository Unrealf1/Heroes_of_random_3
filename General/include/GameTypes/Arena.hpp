//
// Created by fedor on 9/13/20.
//

#ifndef HEROES_OF_RANDOM_ARENA_HPP
#define HEROES_OF_RANDOM_ARENA_HPP

#include <Units/UnitCloner.hpp>
#include <utility>
#include <Battle.hpp>
#include "Interaction/Input.hpp"
#include "Interaction/Output.hpp"
#include "BaseGameType.hpp"

class Arena: BaseGameType {
public:
    Arena(std::vector<Cloner*> cloners, size_t num_battles, size_t initial_money, size_t max_unit_cost=500):
            BaseGameType(std::move(cloners)),
            num_battles(num_battles),
            initial_money(initial_money),
            max_unit_cost(max_unit_cost) {}

    void startLocal() {
        auto name1 = Input::AskForLine("Enter name of the first player");
        auto name2 = Input::AskForLine("Enter name of the second player");
        if (name1.empty()) {
            name1 = "Player 1";
        }
        if (name2.empty()) {
            name2 = "Player 2";
        }
        play(name1, name2);
    }

    void startAsHost() {

    }

    void startAsClient() {

    }

private:
    struct player {
        std::string name;
        size_t money;
        std::vector<UnitGroup> units;
        size_t won = 0;
    };

    void play(const std::string& name1, const std::string& name2) {
        auto old_logger = Output::logger;

        player current{name1, initial_money, {}};
        player opponent{name2, initial_money, {}};
        while (current.won <= num_battles / 2 && opponent.won <= num_battles / 2) {
            round(current, opponent);
        }

        auto winner = current.won > opponent.won  ? name1 : name2;
        Output::LogInfo(fmt::format("{} have won!"));

        Output::logger = old_logger;
    }

    void round(player& current, player& opponent) {
        current.units = {};
        opponent.units = {};

        Output::logger = local_logger;
        shop(current);
        for (size_t i = 0; i < 100; ++i) {
            Output::LogInfo("");
        }
        Input::Confirm(fmt::format("{} ready?", opponent.name));
        Output::logger = opponent_logger;
        shop(opponent);

        Army cur(current.units);
        cur.name = "Player 1";
        Army opp(opponent.units);
        opp.name = "Player 2";
        if (Battle::Start(cur, opp)) {
            ++current.won;
        } else {
            ++opponent.won;
        }
    }

    void shop(player& player) {
        auto offer = getOffer(cloners);
        std::function<void(std::string)> dispatcher([&player, this](std::string choice) {
            for (auto& f : cloners) {
                if (f->getReference().name == choice) {
                    size_t num = static_cast<size_t>(Input::AskForInt("How many?"));

                    auto total_cost = num * f->getCost();
                    Output::LogInfo(fmt::format("Total cost is {}", total_cost));
                    if (total_cost > max_unit_cost) {
                        Output::LogInfo(fmt::format("This is too expensive, max unit cost is {}", max_unit_cost));
                    } else if (total_cost > player.money) {
                        Output::LogInfo("Sorry, not enough money");
                    } else {
                        if (Input::Confirm(fmt::format("Are you sure? (yes/no)"),
                                           fmt::color::white)) {
                            player.money -= total_cost;
                            player.units.push_back(f->create(num));
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
                            "{}, you have {} money. Choose units to buy. Available:\n{}",
                            player.name,
                            player.money,
                            offer);
                }),
                fmt::color::wheat,
                getNames(cloners));
    }

    ILogger* local_logger = nullptr;
    ILogger* opponent_logger = nullptr;

    const size_t num_battles;
    const size_t initial_money;
    const size_t max_unit_cost;
};

#endif //HEROES_OF_RANDOM_ARENA_HPP

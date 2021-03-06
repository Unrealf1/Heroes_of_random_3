//
// Created by fedor on 9/7/20.
//

#ifndef HEROES_OF_RANDOM_OUTPUT_HPP
#define HEROES_OF_RANDOM_OUTPUT_HPP

#include <fmt/core.h>
#include <fmt/color.h>
#include <ostream>
#include <chrono>
#include <thread>

#include "Random.hpp"
#include "ILogger.hpp"
#include "ConsoleLogger.hpp"

using rnd = RandomGenerator;

class Output {
public:
    Output() = delete;

    static inline void LogLine(
            const std::string& message,
            const fmt::color& clr=fmt::color::white) {
        if (logger == nullptr) {
            logger = &default_logger;
        }
        logger->LogLine(message, clr);
    }

    static void LogInBattle(const std::string& message,
                            const fmt::color& clr) {
        if (logger == nullptr) {
            logger = &default_logger;
        }
        logger->LogInBattle(message, clr);
    }

    static void LogAbility(const std::string& message) {
        LogInBattle(message, fmt::color::orange);
    }

    static void LogInfo(const std::string& message) {
        LogLine(message, fmt::color::white);
    }

    static void LogAttack(
            const std::string& attackers,
            const std::string& defenders,
            int64_t damage
    ) {
            LogInBattle(fmt::format("{} dealed {} damage to {}", attackers, damage, defenders),
                        fmt::color::crimson);
    }

    static void LogRound(
            const std::string& attackers,
            const std::string& defenders,
            const int64_t were_attackers,
            const int64_t were_defenders,
            const int64_t died_attackers,
            const int64_t died_defenders
    ) {
        const std::string& quote = rnd::sample(attack_quotes);
        LogInBattle(
                fmt::format(
                        quote,
                        attackers,
                        defenders,
                        were_attackers,
                        were_defenders,
                        died_attackers,
                        died_defenders),
                fmt::color::crimson);
    }

    static void LogDeath(const std::string& name) {
        const std::string& quote = rnd::sample(death_quotes);
        LogInBattle(
                fmt::format(
                        quote,
                        name),
                fmt::color::red);
    }

    static void LogVictory() {
        const std::string& quote = rnd::sample(victory_quotes);
        LogInBattle(fmt::format(quote), fmt::color::yellow);
    }

    static void LogLoss() {
        const std::string& quote = rnd::sample(loss_quotes);
        LogInBattle(fmt::format(quote), fmt::color::blue);
    }
    inline static ILogger* logger = nullptr;
private:
    inline static ConsoleLogger default_logger;
    //0-attackers; 1-defenders; 2-were_attackers; 3-were_defenders; 4-died-atk; 5-died-def
    inline static std::array<std::string, 3> attack_quotes = {
            "{0} reduced population of {1} by {5}, but {4} of them died after",
            "{5} {1} were killed by {0}. But {4} of them had to die for that",
            "{1} got attacked by {0} and lost {5} lives, but killed {4} opponentts in counterattack"};

    inline static std::array<std::string, 2> death_quotes = {
            "squad of {} perished",
            "the last of {} died in agony"};

    inline static std::array<std::string, 2> victory_quotes = {
            "Victory!",
            "Absolute triumph"};

    inline static std::array<std::string, 2> loss_quotes = {
            "You lost.",
            "This is the end of your journey"};
};

#endif //HEROES_OF_RANDOM_OUTPUT_HPP

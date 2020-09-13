//
// Created by fedor on 9/13/20.
//

#ifndef HEROES_OF_RANDOM_CONSOLELOGGER_HPP
#define HEROES_OF_RANDOM_CONSOLELOGGER_HPP

#include <thread>
#include "ILogger.hpp"

class ConsoleLogger: public ILogger {
public:
    void LogLine(const std::string& message, const fmt::color& clr) override {
        fmt::print(fg(clr), "{}", message);
        fmt::print("\n");
    }

    void LogInBattle(const std::string& message, const fmt::color& clr) override {
        std::this_thread::sleep_for(minimum_battle_display_delay);
        LogLine(message, clr);
    }

    std::chrono::milliseconds minimum_battle_display_delay{300};
};

#endif //HEROES_OF_RANDOM_CONSOLELOGGER_HPP

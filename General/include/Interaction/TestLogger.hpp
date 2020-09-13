//
// Created by fedor on 9/13/20.
//

#ifndef HEROES_OF_RANDOM_TESTLOGGER_HPP
#define HEROES_OF_RANDOM_TESTLOGGER_HPP

#include "ConsoleLogger.hpp"

class TestLogger: public ConsoleLogger {
    void LogInBattle(const std::string&, const fmt::color&) override {}
};

#endif //HEROES_OF_RANDOM_TESTLOGGER_HPP

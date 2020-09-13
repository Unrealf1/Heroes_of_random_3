//
// Created by fedor on 9/13/20.
//

#ifndef HEROES_OF_RANDOM_ILOGGER_HPP
#define HEROES_OF_RANDOM_ILOGGER_HPP

#include <string>
#include <fmt/color.h>
#include <fmt/core.h>

class ILogger {
public:
    virtual void LogLine( const std::string& message, const fmt::color& clr) = 0;
    virtual void LogInBattle(const std::string& message, const fmt::color& clr) = 0;
    virtual ~ILogger() = default;

};
#endif //HEROES_OF_RANDOM_ILOGGER_HPP

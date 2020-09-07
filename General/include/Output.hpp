#include <fmt/core.h>
#include <fmt/color.h>
#include <ostream>

class Output {
public:
    static void LogString(
            const std::string& message,
            const fmt::color& clr) {
        fmt::print(fg(clr), message);
        fmt::print("\n");
    }

    static void LogAttack(
            const std::string& attackers,
            const std::string& defenders,
            const int64_t were_attackers,
            const int64_t were_defenders,
            const int64_t died_attackers,
            const int64_t died_defenders
            ) {
        const std::string& quote = attack_quotes[0];
        LogString(
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
        const std::string& quote = death_quotes[0];
        LogString(
                fmt::format(
                        quote,
                        name),
                fmt::color::red);
    }

    static void LogVictory() {
        const std::string& quote = victory_quotes[0];
        LogString(fmt::format(quote), fmt::color::yellow);
    }
private:
    //0-attackers; 1-defenders; 2-were_attackers; 3-were_defenders; 4-died-atk; 5-died-def
    inline static std::array<std::string, 2> attack_quotes = {
            "{0} reduced population of {1} by {5}, but {4} of them died in the process",
            "{5} {1} were killed by {0}. But {4} of them died"};

    inline static std::array<std::string, 2> death_quotes = {
            "squad of {} perished",
            "the last of {} died in agony"};

    inline static std::array<std::string, 2> victory_quotes = {
            "Victory!",
            "Absolute triumph"};
};


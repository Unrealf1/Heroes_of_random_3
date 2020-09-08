//
// Created by fedor on 9/8/20.
//

#ifndef HEROES_OF_RANDOM_INPUT_HPP
#define HEROES_OF_RANDOM_INPUT_HPP

#include "Output.hpp"
#include <iostream>
#include <algorithm>

class Input {
public:
    static std::string AskForLine(const std::string& message,
                           const fmt::color& clr) {
        Output::LogString(message, clr);
        std::string answer;
        std::getline(std::cin, answer);
        //std::transform(answer.begin(), answer.end(), answer.begin(), ::tolower);
        return answer;
    }

    static int64_t AskForInt(const std::string& message) {
        auto answer = AskForLine(message, fmt::color::white);
        while (!is_number(answer)) {
            answer = AskForLine("Please enter a valid number", fmt::color::white);
        }
        return std::stol(answer);
    }

    static std::string AskForChoice(const std::string& message,
                                    const fmt::color& clr,
                                    const std::vector<std::string>& choices,
                                    const std::string& backup = "") {
        auto new_choices = choices;
        /*for (auto& ch : new_choices) {
            std::transform(ch.begin(), ch.end(), ch.begin(), ::tolower);
        }*/

        std::string answer = AskForLine(message, clr);
        const std::string& real_backup = backup.empty() ? message : backup;
        bool need_leave = false;
        for (auto& ch : new_choices) {
            if (ch == answer) {
                need_leave = true;
            }
        }
        while(!need_leave) {
            for (auto& ch : new_choices) {
                if (ch == answer) {
                    need_leave = true;
                }
            }
            answer = AskForLine(real_backup, clr);
        }
        /*while (std::find(choices.begin(), choices.end(), answer) == choices.end()) {
            answer = AskForLine(real_backup, clr);
        }*/

        return answer;
    }

    static std::string AskForChoiceWithFinish(const std::string& message,
                                    const fmt::color& clr,
                                    const std::vector<std::string>& choices,
                                    const std::string& backup = "") {
        auto new_choices = choices;
        new_choices.emplace_back("finish");
        Output::LogInfo("Type \"finish\" if you wish to exit this choice");
        return AskForChoice(message, clr, new_choices, backup);
    }

private:
    static bool is_number(const std::string& s)
    {
        return !s.empty() && std::find_if(s.begin(),
                                          s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
    }
};

#endif //HEROES_OF_RANDOM_INPUT_HPP

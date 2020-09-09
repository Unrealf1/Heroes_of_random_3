//
// Created by fedor on 9/8/20.
//

#ifndef HEROES_OF_RANDOM_INPUT_HPP
#define HEROES_OF_RANDOM_INPUT_HPP

#include "Output.hpp"
#include <iostream>
#include <algorithm>
#include <map>

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

        std::string answer = AskForLine(message, clr);
        std::string all_choices;
        for (const auto& ch : choices) {
            all_choices += ch + '\n';
        }
        const std::string& real_backup = backup.empty() ? ("Options are:\n" + all_choices) : backup;
        bool need_leave = false;
        for (auto& ch : choices) {
            if (ch == answer) {
                need_leave = true;
            }
        }
        while(!need_leave) {
            answer = AskForLine(real_backup, clr);
            for (auto& ch : choices) {
                if (ch == answer) {
                    need_leave = true;
                }
            }
        }

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

    static bool Confirm(const std::string& message,
                        const fmt::color& clr = fmt::color::white) {
        std::string confirmation = Input::AskForChoice(
                message,
                clr,
                std::vector<std::string>{"yes", "no", "y", "n"});
        return confirmation == "y" || confirmation == "yes";
    }

    using dispatcher_t = std::function<void(std::string)>;
    static void ChoiceActionWithFinish(dispatcher_t& dispatcher,
                             const std::string& message,
                             const fmt::color& clr,
                             const std::vector<std::string>& choices,
                             const std::string& backup = "") {
        std::string answer = AskForChoiceWithFinish(
                message,
                clr,
                choices,
                backup);
        while (answer != "finish") {
            dispatcher(answer);
            answer = AskForChoiceWithFinish(
                    message,
                    clr,
                    choices,
                    backup);
        }
    }

    using message_supplier = std::function<std::string(void)>;
    static void ChoiceActionWithFinish(dispatcher_t& dispatcher,
                                       const message_supplier& supplier,
                                       const fmt::color& clr,
                                       const std::vector<std::string>& choices,
                                       const std::string& backup = "") {
        std::string answer = AskForChoiceWithFinish(
                supplier(),
                clr,
                choices,
                backup);
        while (answer != "finish") {
            dispatcher(answer);
            answer = AskForChoiceWithFinish(
                    supplier(),
                    clr,
                    choices,
                    backup);
        }
    }

private:
    static bool is_number(const std::string& s)
    {
        return !s.empty() && std::find_if(s.begin(),
                                          s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
    }
};

#endif //HEROES_OF_RANDOM_INPUT_HPP

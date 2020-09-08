//
// Created by fedor on 9/8/20.
//

#include "Interaction/Input.hpp"
#include "UnitInspector.hpp"
#include <fmt/color.h>
#include <string>
#include "Units/UnitCloner.hpp"
#include "Units/UnitSerializer.hpp"

int main() {
    std::string answer;
    std::vector<std::string> options{"create", "inspect"};
    UnitSerializer serializer("./Units");
    UnitInspector inspector("./Units/list.json");

    while (answer != "finish") {
        answer = Input::AskForChoiceWithFinish(
                "What would you like to do?",
                fmt::color::white,
                options);
        if (answer == "create") {
            inspector.Create(serializer);
        } else if (answer == "inspect") {
            inspector.Edit(serializer);
        }
    }


}
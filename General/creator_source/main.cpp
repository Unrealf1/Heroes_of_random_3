//
// Created by fedor on 9/8/20.
//

#include "Interaction/Input.hpp"
#include "UnitEditor.hpp"
#include <fmt/color.h>
#include <string>
#include "Units/UnitCloner.hpp"
#include "Units/UnitSerializer.hpp"

int main() {
    std::string answer;
    std::vector<std::string> options{"create", "inspect"};
    UnitSerializer serializer("./Units");
    UnitEditor inspector("./Units");

    while (answer != "finish") {
        answer = Input::AskForChoiceWithFinish(
                "What would you like to do?",
                fmt::color::wheat,
                options);
        if (answer == "create") {
            inspector.create(serializer);
        } else if (answer == "inspect") {
            inspector.edit(serializer);
        }
    }


}
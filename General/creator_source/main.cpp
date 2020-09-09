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
    std::vector<std::string> options{"create", "edit", "test"};
    UnitSerializer serializer("./Units");
    UnitEditor inspector("./Units");
    Input::dispatcher_t dispatcher([&](std::string choice) {
        if (choice == "create") {
            inspector.create(serializer);
        } else if (choice == "edit") {
            inspector.edit(serializer);
        } else if (choice == "test") {
            inspector.test();
        }
    });
    Input::ChoiceActionWithFinish(dispatcher, "What would you like to do?", fmt::color::wheat, options);
}
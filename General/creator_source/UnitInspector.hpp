//
// Created by fedor on 9/8/20.
//

#ifndef HEROES_OF_RANDOM_UNITINSPECTOR_HPP
#define HEROES_OF_RANDOM_UNITINSPECTOR_HPP

#include <string>
#include <vector>
#include <Units/UnitCloner.hpp>
#include <Units/UnitLoader.hpp>
#include <Interaction/Input.hpp>
#include <cstdio>
#include <Units/UnitSerializer.hpp>

class UnitInspector {
public:
    explicit UnitInspector(std::string list_path) {
        std::ifstream ifs(list_path);
        if (ifs.good()) {
            json list;
            ifs >> list;
            for (const auto& path : list["units"]) {
                cloners.push_back(UnitLoader::parseUnit(path));
            }
        } else {
            std::ofstream ofs(list_path);
            json list;
            list["units"] = json::array();
        }

    }

    void Create(UnitSerializer& serializer) {
        Cloner* new_unit = new Cloner(
                UnitGroup(0, 0, 0, 0, 0, "New Unit"), 0);
        cloners.push_back(new_unit);
        if (EditUnit(new_unit)) {
            serializer.serialize(*new_unit);
        }

    }

    void Edit(UnitSerializer& serializer) {
        std::vector<std::string> names(cloners.size());
        for (size_t i = 0; i < cloners.size(); ++i) {
            names[i] = cloners[i]->getReference().name;
        }

        std::function<void(std::string)> dispatcher([this, &serializer](std::string name){
            Cloner* chosen = nullptr;
            for (Cloner* cl : cloners) {
                if (cl->getReference().name == name) {
                    chosen = cl;
                    break;
                }
            }
            if (EditUnit(chosen)) {
                serializer.serialize(*chosen);
            }
        });
        Input::ChoiceActionWithFinish(
                dispatcher,
                "Which unit ouy would like to edit?",
                fmt::color::white,
                names);
    }

    ~UnitInspector() {
        for (Cloner* cl : cloners) {
            delete cl;
        }
    }
private:
    bool EditUnit(Cloner* cloner) {
        bool edited = false;
        std::vector<std::string> choices{"hp", "max damage", "min damage", "armor", "speed", "name"};
        std::function<void(std::string)> dispatcher([&edited, cloner](std::string parameter){
            edited = true;
            if (parameter == "hp") {
                cloner->reference.hp = Input::AskForInt("Enter new value");
            } else if (parameter == "max damage") {
                cloner->reference.max_damage = Input::AskForInt("Enter new value");
            } else if (parameter == "min damage") {
                cloner->reference.min_damage = Input::AskForInt("Enter new value");
            }else if (parameter == "armor") {
                cloner->reference.armor = Input::AskForInt("Enter new value");
            }else if (parameter == "speed") {
                cloner->reference.speed = Input::AskForInt("Enter new value");
            } else if (parameter == "name") {
                cloner->reference.name = Input::AskForLine("Enter new name", fmt::color::white);
            }
        });
        Input::ChoiceActionWithFinish(
                dispatcher,
                "What you would like to change?",
                fmt::color::white,
                choices);
        return edited;
    }
    std::vector<Cloner*> cloners;
};

#endif //HEROES_OF_RANDOM_UNITINSPECTOR_HPP

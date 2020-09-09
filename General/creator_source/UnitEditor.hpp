//
// Created by fedor on 9/8/20.
//

#ifndef HEROES_OF_RANDOM_UNITEDITOR_HPP
#define HEROES_OF_RANDOM_UNITEDITOR_HPP

#include <string>
#include <vector>
#include <Units/UnitCloner.hpp>
#include <Units/UnitLoader.hpp>
#include <Interaction/Input.hpp>
#include <cstdio>
#include <Units/UnitSerializer.hpp>
#include <Tags.hpp>
#include <fmt/ranges.h>

class UnitEditor {
public:
    explicit UnitEditor(const std::string& list_dir): list_path(fmt::format("{}/list.json", list_dir)) {
        std::ifstream ifs(list_path);
        if (ifs.is_open()) {
            fmt::print("was good\n");
            json list;
            ifs >> list;
            for (const auto& name : list["units"]) {
                cloners.push_back(UnitLoader::parseUnit(fmt::format("{}/{}.json", list_dir, name)));
            }
        } else {
            fmt::print("was bad\n");
            std::ofstream ofs(list_path);
            json list;
            list["units"] = json::array();
            ofs << list.dump(4);
        }
    }

    void create(UnitSerializer& serializer) {
        Cloner* new_unit = new Cloner(
                UnitGroup(0, 0, 0, 0, 0, "New Unit"), 0);
        cloners.push_back(new_unit);
        if (editUnit(new_unit)) {
            serializer.serialize(*new_unit);
        }
        updateList();
    }

    void edit(UnitSerializer& serializer) {
        std::vector<std::string> names = getNames();
        fmt::print("found {} units\n", names.size());
        std::function<void(std::string)> dispatcher([this, &serializer](std::string name) {
            Cloner* chosen = nullptr;
            for (Cloner* cl : cloners) {
                if (cl->getReference().name == name) {
                    chosen = cl;
                    break;
                }
            }
            if (editUnit(chosen)) {
                serializer.serialize(*chosen);
            }
        });
        Input::ChoiceActionWithFinish(
                dispatcher,
                "Which unit ouy would like to edit?",
                fmt::color::wheat,
                names);
    }

    ~UnitEditor() {
        for (Cloner* cl : cloners) {
            delete cl;
        }
    }
private:
    const std::string list_path;

    void updateList() {
        std::ofstream ofs(list_path, std::ofstream::trunc);
        json list;
        list["units"] = getNames();
        ofs << list.dump(4);
    }

    std::vector<std::string> getNames() {
        std::vector<std::string> names(cloners.size());
        for (size_t i = 0; i < cloners.size(); ++i) {
            names[i] = cloners[i]->getReference().name;
        }
        return names;
    }

    bool editUnit(Cloner* cloner) {
        UnitGroup& ref = cloner->reference;
        Output::LogInfo(fmt::format(FMT_STRING(
                                            "currently stats are:\nhp={}, min damage = {}, max damage = {}, armor = {}, speed = {}, name = {}, cost = {}\nTags are: {}"),
                                    ref.hp,
                                    ref.min_damage,
                                    ref.max_damage,
                                    ref.armor,
                                    ref.speed,
                                    ref.name,
                                    cloner->cost,
                                    ref.tags));
        bool edited = false;
        std::vector<std::string> choices{"hp", "min damage", "max damage", "armor", "speed", "name", "cost", "tags"};
        std::function<void(std::string)> dispatcher([cloner, &ref, &edited](std::string parameter){
            edited = true;
            if (parameter == "hp") {
                ref.hp = Input::AskForInt("Enter new value");
            } else if (parameter == "max damage") {
                ref.max_damage = Input::AskForInt("Enter new value");
            } else if (parameter == "min damage") {
                ref.min_damage = Input::AskForInt("Enter new value");
            }else if (parameter == "armor") {
                ref.armor = Input::AskForInt("Enter new value");
            }else if (parameter == "speed") {
                ref.speed = Input::AskForInt("Enter new value");
            } else if (parameter == "name") {
                ref.name = Input::AskForLine("Enter new name", fmt::color::white);
            } else if (parameter == "cost") {
                cloner->cost = Input::AskForInt("Enter new value");
            } else if (parameter == "tags") {
                if (Input::Confirm(R"(Enter "yes" to add tags or "no" to remove)")) {
                    auto& tags = TagContainer::actual_tags;
                    std::vector<TagContainer::tag_t> tag_names;
                    tag_names.reserve(tags.size());
                    for (auto& pr : tags) {
                        tag_names.push_back(pr.first);
                    }

                    Input::dispatcher_t dispatcher([cloner](std::string choice){
                        cloner->reference.tags.push_back(choice);
                    });
                    Input::ChoiceActionWithFinish(dispatcher, "Which tag?", fmt::color::wheat, tag_names);
                } else {
                    Input::dispatcher_t dispatcher([&ref](std::string choice){
                        auto it = ref.tags.begin();
                        for (; *it != choice; ++it) {}
                        ref.tags.erase(it);
                    });
                    Input::ChoiceActionWithFinish(dispatcher, "Which tag?", fmt::color::wheat, cloner->reference.tags);
                }
            }
        });
        Input::ChoiceActionWithFinish(
                dispatcher,
                "What you would like to change?",
                fmt::color::wheat,
                choices);
        return edited;
    }
    std::vector<Cloner*> cloners;
};

#endif //HEROES_OF_RANDOM_UNITEDITOR_HPP

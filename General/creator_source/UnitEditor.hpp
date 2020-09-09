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
#include <Tags/Tags.hpp>
#include <fmt/ranges.h>
#include "Battle.hpp"

struct TestData {
    size_t avg_left_1;
    size_t avg_left_2;
    size_t won_1;
};

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
        Cloner* chosen = askForUnit();
        if (editUnit(chosen)) {
            serializer.serialize(*chosen);
        }
    }

    void test() {
        Output::battle_logging = false;
        bool in_test = true;
        while(in_test) {
            Cloner* subject1 = askForUnit("Choose first unit");
            Cloner* subject2 = askForUnit("Choose second unit");
            bool repeat = true;
            while (repeat) {
                size_t total_tests = 1000;
                int64_t first_num = Input::AskForInt(fmt::format("How many {}?", subject1->getReference().name));
                int64_t second_num = Input::AskForInt(fmt::format("How many {}?", subject2->getReference().name));

               auto data = testCase(subject1, subject2, first_num, second_num, total_tests);

                Output::LogLine(fmt::format(
                        "Results for test case {} ({} worth {} money) vs {} ({} worth {} money):\n"
                        "First won in {} cases ({}%). On average {} units left\n"
                        "Second win in {} cases ({}%). On average {} units left",
                        subject1->reference.name, first_num, first_num*subject1->getCost(),
                        subject2->reference.name, second_num, second_num*subject2->getCost(),
                        data.won_1, data.won_1 * 100 / total_tests, data.avg_left_1,
                        total_tests - data.won_1, (total_tests - data.won_1) * 100 / total_tests, data.avg_left_2),
                                fmt::color::green_yellow);
                repeat = Input::Confirm("Test this units again?");
            }
            in_test = Input::Confirm("Test other units?");
        }
        Output::battle_logging = false;
    }

    ~UnitEditor() {
        for (Cloner* cl : cloners) {
            delete cl;
        }
    }
private:
    // Returns total wins of subject 1
    static TestData testCase(Cloner* subject1, Cloner* subject2, int64_t num_1, int64_t num_2, size_t iterations) {
        size_t first_won = 0;
        size_t left_1 = 0;
        size_t left_2 = 0;
        for (size_t i = 0; i < iterations; ++i) {
            std::vector<UnitGroup> groups1{subject1->create(num_1)};
            std::vector<UnitGroup> groups2{subject2->create(num_2)};
            Army army1(groups1);
            Army army2(groups2);
            TestInfo info;
            if (Battle::Start(army1, army2, &info)) {
                ++first_won;
            }
            left_1 += static_cast<size_t>(info.first_army_left);
            left_2 += static_cast<size_t>(info.second_army_left);
        }
        return {first_won != 0 ? (left_1 / first_won) : 0,
                first_won != iterations ? (left_2 / (iterations - first_won)) : 0,
                first_won};
    }

    const std::string list_path;

    Cloner* askForUnit(const std::string& question = "Which unit would you like to choose?") {
        std::vector<std::string> names = getNames();
        fmt::print("found {} units\n", names.size());
        Cloner* chosen = nullptr;

        auto name = Input::AskForChoice(
                question,
                fmt::color::wheat,
                names);
        for (Cloner* cl : cloners) {
            if (cl->getReference().name == name) {
                chosen = cl;
                break;
            }
        }
        return chosen;
    }

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

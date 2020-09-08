//
// Created by fedor on 9/8/20.
//

#ifndef HEROES_OF_RANDOM_UNITLOADER_HPP
#define HEROES_OF_RANDOM_UNITLOADER_HPP

#include "UnitCloner.hpp"

#include <nlohmann/json.hpp>
#include <vector>
#include <fstream>

using json = nlohmann::json;

class UnitLoader {
    using cloners_t = std::vector<Cloner*>;
public:
    explicit UnitLoader(const std::string& list_path) {
        std::ifstream ifs(list_path);
        json list;
        ifs >> list;
        for (const auto& path : list["units"]) {
            cloners.push_back(parseUnit(path));
        }
    }

    cloners_t& getCloners() {
        return cloners;
    }

    ~UnitLoader() {
        for (auto ptr : cloners) {
            delete ptr;
        }
    }

    static Cloner* parseUnit(const std::string& filepath) {
        std::ifstream file(filepath);
        json js;
        file >> js;
        int64_t hp = js["hp"];
        int64_t min_damage = js["min_damage"];
        int64_t max_damage = js["max_damage"];
        int64_t armor = js["armor"];
        int64_t speed = js["speed"];
        std::string name = js["name"];
        int64_t cost = js["cost"];
        return new Cloner(
                UnitGroup(
                hp,
                min_damage,
                max_damage,
                armor,
                speed,
                name
            ),
            cost
        );
    }
private:
    cloners_t cloners;
};

#endif //HEROES_OF_RANDOM_UNITLOADER_HPP

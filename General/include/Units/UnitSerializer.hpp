//
// Created by fedor on 9/8/20.
//

#ifndef HEROES_OF_RANDOM_UNITSERIALIZER_HPP
#define HEROES_OF_RANDOM_UNITSERIALIZER_HPP

#include <string>
#include <fstream>
#include <nlohmann/json.hpp>
#include <utility>
#include "UnitCloner.hpp"

class UnitSerializer {
public:
    explicit UnitSerializer(std::string dir_path): dir_path(std::move(dir_path)) {}

    void serialize(const Cloner& cloner) {
        nlohmann::json js;
        js["hp"] = cloner.getReference().hp;
        js["min_damage"] = cloner.getReference().min_damage;
        js["max_damage"] = cloner.getReference().max_damage;
        js["armor"] = cloner.getReference().armor;
        js["speed"] = cloner.getReference().speed;
        js["name"] = cloner.getReference().name;
        js["cost"] = cloner.getCost();
        js["tags"] = cloner.getReference().tags;
        std::ofstream off(fmt::format("{}/{}.json", dir_path, cloner.getReference().name));
        off << js.dump(4);
    }
private:
    const std::string dir_path;
};

#endif //HEROES_OF_RANDOM_UNITSERIALIZER_HPP

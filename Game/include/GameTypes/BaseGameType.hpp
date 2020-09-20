//
// Created by fedor on 9/13/20.
//

#ifndef HEROES_OF_RANDOM_BASEGAMETYPE_HPP
#define HEROES_OF_RANDOM_BASEGAMETYPE_HPP

#include <vector>
#include <Units/UnitCloner.hpp>

class BaseGameType {
    using cloners_t = std::vector<Cloner*>;
public:
    explicit BaseGameType(cloners_t cloners): cloners(std::move(cloners)) {

    }

protected:
    cloners_t cloners;

    static std::string getOffer(cloners_t& options) {
        std::string pattern = "{} for {}";
        std::vector<std::string> available_units(options.size());
        std::string offer;

        for (size_t i = 0; i < options.size(); ++i) {
            available_units[i] = options[i]->getReference().name;
            offer += fmt::format(pattern, options[i]->getReference().name, options[i]->getCost()) + "\n";
        }
        return offer;
    }

    static std::vector<std::string> getNames(cloners_t& cloners) {
        std::vector<std::string> names;
        names.reserve(cloners.size());
        for (auto cloner : cloners) {
            names.emplace_back(cloner->getReference().name);
        }
        return names;
    }
};

#endif //HEROES_OF_RANDOM_BASEGAMETYPE_HPP

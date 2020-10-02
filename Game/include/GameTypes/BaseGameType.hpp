//
// Created by fedor on 9/13/20.
//

#ifndef HEROES_OF_RANDOM_BASEGAMETYPE_HPP
#define HEROES_OF_RANDOM_BASEGAMETYPE_HPP

#include <vector>
#include <Units/UnitCloner.hpp>
#include <algorithm>
#include <numeric>

class BaseGameType {
    using cloners_t = std::vector<Cloner*>;
public:
    explicit BaseGameType(cloners_t cloners): cloners(std::move(cloners)) {

    }
protected:
    cloners_t cloners;

    static cloners_t getAffordable(const cloners_t& cloners, int64_t money) {
        cloners_t affordable;
        affordable.reserve(cloners.size());
        std::remove_copy_if(
                cloners.begin(),
                cloners.end(),
                std::back_inserter(affordable),
                [&money](const Cloner* const cloner){return cloner->getCost() > money;}
        );
        affordable.shrink_to_fit();
        return affordable;
    }

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

    static uint64_t getScore(const Army& enemy) {
        return std::transform_reduce(
                enemy.composition.begin(),
                enemy.composition.end(),
                0ul,
                [](int64_t first, int64_t second){
                    return first + second;
                },
                [](const UnitGroup& group){
                    return group.GetCount();
                });
    }

    static cloners_t clonersWithoutTags(const cloners_t& cloners, const std::vector<std::string>& tags) {
        cloners_t filtered;
        filtered.reserve(cloners.size());
        std::remove_copy_if(cloners.begin(), cloners.end(), std::back_inserter(filtered), [&tags](const Cloner* const cloner) {
            return std::any_of(tags.begin(), tags.end(), [&cloner](const std::string& tag){
                return cloner->getReference().has_tag(tag);
            });
        });
        filtered.shrink_to_fit();
        return filtered;
    }
};

#endif //HEROES_OF_RANDOM_BASEGAMETYPE_HPP

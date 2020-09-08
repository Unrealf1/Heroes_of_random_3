#include "GameTypes/RandomBattles.hpp"
#include "Units/UnitFactories.hpp"

int main()  {
    RandomGenerator::set_seed(140123);
    KnightFactory knight;
    SwordsmanFactory sword;
    ArcherFactory bow;
    std::vector<BaseFactory*> facts{&knight, &sword, &bow};
    RandomBattles rb(facts, 400);
    rb.Start();
}
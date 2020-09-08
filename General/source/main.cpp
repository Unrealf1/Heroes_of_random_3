#include "GameTypes/RandomBattles.hpp"
#include "GameTypes/RogueLikeYakun.hpp"
#include "Interaction/Input.hpp"
#include "Units/UnitFactories.hpp"

int main()  {
    RandomGenerator::set_seed(static_cast<unsigned int>(Input::AskForInt("Enter random seed")));
    KnightFactory knight;
    SwordsmanFactory sword;
    ArcherFactory bow;
    std::vector<BaseFactory*> facts{&knight, &sword, &bow};
    RogueLike rl(facts, 400, 20);
    rl.Start();
}
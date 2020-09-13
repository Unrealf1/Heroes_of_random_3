#include <Interaction/ConsoleLogger.hpp>
#include <GameTypes/Arena.hpp>
#include "GameTypes/RandomBattles.hpp"
#include "GameTypes/RogueLikeYakun.hpp"
#include "Units/UnitLoader.hpp"
#include "Interaction/Input.hpp"

int main()  {
    RandomGenerator::set_seed(static_cast<unsigned int>(Input::AskForInt("Enter random seed")));
    UnitLoader loader("./Units");
    auto cloners = loader.getCloners();
    RandomBattles battles(cloners, 400);
    RogueLike rl(cloners, 400, 5, 100);
    Arena arena(cloners, 3, 1200);
    arena.startLocal();
}

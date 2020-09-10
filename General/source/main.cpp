#include "GameTypes/RandomBattles.hpp"
#include "GameTypes/RogueLikeYakun.hpp"
#include "Units/UnitLoader.hpp"
#include "Interaction/Input.hpp"

int main()  {
    RandomGenerator::set_seed(static_cast<unsigned int>(Input::AskForInt("Enter random seed")));
    UnitLoader loader("./Units");
    auto cloners = loader.getCloners();
    RogueLike rl(cloners, 400, 5, 100);
    rl.Start();
}

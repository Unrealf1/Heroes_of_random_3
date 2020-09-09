#include "GameTypes/RandomBattles.hpp"
#include "Units/UnitLoader.hpp"

int main()  {

    RandomGenerator::set_seed(140123);

    UnitLoader loader("./Units");
    auto cloners = loader.getCloners();
    RandomBattles rb(cloners, 400);
    rb.Start();
}
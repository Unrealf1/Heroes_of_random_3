#include "Units/UnitLoader.hpp"
#include "Interaction/Input.hpp"
#include "GameTypeSelector.hpp"

int main()  {
    RandomGenerator::set_seed(static_cast<unsigned int>(Input::AskForInt("Enter random seed")));
    UnitLoader loader("./Units");
    auto cloners = loader.getCloners();
    GameTypeSelector::select(cloners);
}

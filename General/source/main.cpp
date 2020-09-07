#include <iostream>
#include "Output.hpp"
#include "random.hpp"


int main()  {
    RandomGenerator::set_seed(140123);
    Output::LogDeath("my happiness");
    Output::LogAttack("bears", "wolfs", 100, 50, 7, 30);
    Output::LogVictory();
}
#include <iostream>
#include "Creature.h"

int main()
{
    Creature wolf;

    for(int i = 0; i < 5; i++)
    {
        wolf.Update();

        std::cout
            << "Age: " << wolf.age
            << " Energy: " << wolf.energy
            << std::endl;
    }

    return 0;
}
#include <iostream>

#include "Creature.h"
#include "World.h"

int main()
{
    World world;

    Creature wolf;
    Creature rabbit;
    Creature bear;

    world.AddCreature(wolf);
    world.AddCreature(rabbit);
    world.AddCreature(bear);

    for(int tick = 0; tick < 5; tick++)
    {
        std::cout
            << "\n=== Tick "
            << tick
            << " ==="
            << std::endl;

        world.Update();

        world.PrintStats();
    }

    return 0;
}
#include <iostream>

#include "World.h"

void World::AddCreature(const Creature& creature)
{
    creatures.push_back(creature);
}

void World::Update()
{
    for (auto& creature : creatures)
    {
        creature.Update();
    }
}

void World::PrintStats() const
{
    std::cout
        << "Population: "
        << creatures.size()
        << std::endl;

    for (std::size_t i = 0; i < creatures.size(); i++)
    {
        std::cout
            << "Creature "
            << i
            << " Age="
            << creatures[i].age
            << " Energy="
            << creatures[i].energy
            << " Pos=("
            << creatures[i].x
            << ","
            << creatures[i].y
            << ")"
            << std::endl;
    }
}
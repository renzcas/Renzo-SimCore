#include "Creature.h"

Creature::Creature()
{
    health = 100;
    energy = 100;
    age = 0;
}

void Creature::Update()
{
    age++;
    energy--;
}
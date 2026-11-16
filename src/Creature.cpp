#include "Creature.h"

Creature::Creature()
{
    health = 100;
    energy = 100;
    age = 0;

    x = 0;
    y = 0;
}

void Creature::Move()
{
    x++;

    energy -= 2;
}

void Creature::Sleep()
{
    energy += 1;
}

void Creature::Update()
{
    age++;

    if (energy > 50)
    {
        Move();
    }
    else
    {
        Sleep();
    }
}
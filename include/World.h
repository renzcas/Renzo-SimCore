#pragma once

#include <vector>
#include "Creature.h"

class World
{
public:
    void AddCreature(const Creature& creature);

    void Update();

    void PrintStats() const;

private:
    std::vector<Creature> creatures;
};
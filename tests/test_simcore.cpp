#include <cassert>
#include <iostream>
#include <memory>
#include "world/World.h"
#include "entities/Creature.h"
#include "simcore/Agent.h"
#include "simcore/Signal.h"

int main() {
    std::cout << "=== Running SimCore Layer 1 Tests ===" << std::endl;

    World world(800, 600);
    auto creature = std::make_shared<Creature>(1, "Trog", 100.0, 50.0);
    auto agent = std::make_shared<Agent>(2, "Watcher");

    world.addEntity(creature);
    world.addEntity(agent);

    world.emitSignal({1, "proximity", 0.75});
    world.update(1.0);

    assert(agent->getBelief("proximity") == 0.75);
    assert(creature->getEnergy() < 50.0);

    std::cout << "All SimCore Layer 1 Tests Passed!" << std::endl;
    return 0;
}

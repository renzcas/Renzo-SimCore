#include <cassert>
#include <memory>
#include <iostream>
#include "core/Entity.h"
#include "entities/Creature.h"
#include "world/World.h"

void testEntityCreation() {
    std::cout << "Running testEntityCreation..." << std::endl;
    
    // Test default and parameterized construction through Creature
    Creature c1;
    assert(c1.getId() == 0);
    assert(c1.getName() == "Entity");
    assert(c1.getHealth() == 100.0);
    assert(c1.getEnergy() == 100.0);

    Creature c2(42, "Dragon", 250.0, 150.0);
    assert(c2.getId() == 42);
    assert(c2.getName() == "Dragon");
    assert(c2.getHealth() == 250.0);
    assert(c2.getEnergy() == 150.0);

    std::cout << "testEntityCreation passed!" << std::endl;
}

void testCreatureStateUpdates() {
    std::cout << "Running testCreatureStateUpdates..." << std::endl;

    Creature creature(1, "Goblin", 100.0, 50.0);
    
    creature.setHealth(75.5);
    creature.setEnergy(25.0);

    assert(creature.getHealth() == 75.5);
    assert(creature.getEnergy() == 25.0);

    // Test update loop simulation
    creature.update(1.0);
    
    std::cout << "testCreatureStateUpdates passed!" << std::endl;
}

void testWorldIntegration() {
    std::cout << "Running testWorldIntegration..." << std::endl;

    World world(800, 600);
    assert(world.getEntityCount() == 0);

    auto creature = std::make_shared<Creature>(10, "Minotaur", 500.0, 200.0);
    world.addEntity(creature);

    assert(world.getEntityCount() == 1);

    world.update(0.016);

    std::cout << "testWorldIntegration passed!" << std::endl;
}

int main() {
    std::cout << "=== Starting Creature & World Unit Tests ===" << std::endl;
    
    testEntityCreation();
    testCreatureStateUpdates();
    testWorldIntegration();

    std::cout << "=== All Tests Passed Successfully! ===" << std::endl;
    return 0;
}
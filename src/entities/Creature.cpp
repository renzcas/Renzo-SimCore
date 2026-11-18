#include "entities/Creature.h"

Creature::Creature() : Entity(0, "Entity"), health(100.0), energy(100.0) {}

Creature::Creature(uint64_t id, const std::string& name, double health, double energy)
    : Entity(id, name), health(health), energy(energy) {}

double Creature::getHealth() const {
    return health;
}

void Creature::setHealth(double h) {
    health = h;
}

double Creature::getEnergy() const {
    return energy;
}

void Creature::setEnergy(double e) {
    energy = e;
}

void Creature::update(double dt) {
    // Example update logic reducing energy over time
    energy -= dt;
    if (energy < 0.0) energy = 0.0;
}
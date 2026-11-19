#include "world/World.h"
#include "simcore/Agent.h"

World::World(int w, int h) : width(w), height(h) {}

void World::addEntity(std::shared_ptr<Entity> entity) {
    if (entity) {
        entities.push_back(entity);
    }
}

void World::emitSignal(const Signal& sig) {
    signalBus.publish(sig);
}

void World::update(double dt) {
    // 1. Drain signals emitted since last tick and deliver to all Agents (excluding self-signals)
    auto signals = signalBus.drain();
    for (auto& entity : entities) {
        if (auto* agent = dynamic_cast<Agent*>(entity.get())) {
            for (const auto& sig : signals) {
                if (sig.sourceId != agent->getId()) {
                    agent->receiveSignal(sig);
                }
            }
        }
    }

    // 2. Step all entities in the simulation loop
    for (auto& entity : entities) {
        entity->update(dt);
    }

    // 3. Flush agent actions back onto the SignalBus for the next tick
    for (auto& entity : entities) {
        if (auto* agent = dynamic_cast<Agent*>(entity.get())) {
            for (const auto& action : agent->flushActions()) {
                signalBus.publish(action);
            }
        }
    }
}

int World::getWidth() const noexcept {
    return width;
}

int World::getHeight() const noexcept {
    return height;
}

size_t World::getEntityCount() const noexcept {
    return entities.size();
}

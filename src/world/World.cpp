#include "world/World.h"

World::World() : width(800), height(600) {}

World::World(int width, int height) : width(width), height(height) {}

void World::addEntity(std::shared_ptr<Entity> entity) {
    entities.push_back(entity);
}

size_t World::getEntityCount() const {
    return entities.size();
}

void World::update(double dt) {
    for (auto& entity : entities) {
        entity->update(dt);
    }
}
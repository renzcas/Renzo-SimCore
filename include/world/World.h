#pragma once
#include <vector>
#include <memory>
#include "core/Entity.h"

class World {
private:
    int width;
    int height;
    std::vector<std::shared_ptr<Entity>> entities;

public:
    World();
    World(int width, int height);

    void addEntity(std::shared_ptr<Entity> entity);
    size_t getEntityCount() const;
    void update(double dt = 0.016);
};
#pragma once
#include "core/Entity.h"
#include "simcore/Signal.h"
#include "simcore/SignalBus.h"
#include <vector>
#include <memory>

class World {
private:
    int width;
    int height;
    std::vector<std::shared_ptr<Entity>> entities;
    SignalBus signalBus;

public:
    World(int w, int h);

    void addEntity(std::shared_ptr<Entity> entity);
    void emitSignal(const Signal& sig);
    void update(double dt);

    int getWidth() const noexcept;
    int getHeight() const noexcept;
    size_t getEntityCount() const noexcept;
};
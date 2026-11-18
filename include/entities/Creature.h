#pragma once
#include "core/Entity.h"

class Creature : public Entity {
private:
    double health;
    double energy;

public:
    Creature();
    Creature(uint64_t id, const std::string& name, double health, double energy);

    double getHealth() const;
    void setHealth(double h);

    double getEnergy() const;
    void setEnergy(double e);

    void update(double dt) override;
};

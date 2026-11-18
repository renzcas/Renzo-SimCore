#pragma once
#include <string>
#include <cstdint>

class Entity {
protected:
    uint64_t id;
    std::string name;

public:
    Entity(uint64_t id, const std::string& name = "Entity");
    virtual ~Entity() = default;

    uint64_t getId() const;
    void setId(uint64_t newId);

    const std::string& getName() const;
    void setName(const std::string& newName);

    virtual void update(double dt) = 0;
};
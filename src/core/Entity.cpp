#include "core/Entity.h"

Entity::Entity(uint64_t id, const std::string& name)
    : id(id), name(name) {}

uint64_t Entity::getId() const {
    return id;
}

void Entity::setId(uint64_t newId) {
    id = newId;
}

const std::string& Entity::getName() const {
    return name;
}

void Entity::setName(const std::string& newName) {
    name = newName;
}
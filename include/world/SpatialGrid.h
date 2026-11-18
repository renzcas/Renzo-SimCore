#pragma once

#include "core/Entity.h"
#include <vector>
#include <unordered_map>
#include <cmath>

namespace simcore {

struct Coord {
    int x;
    int y;

    bool operator==(const Coord& other) const {
        return x == other.x && y == other.y;
    }
};

} // namespace simcore

// Hash support for grid coordinates
namespace std {
    template<>
    struct hash<simcore::Coord> {
        size_t operator()(const simcore::Coord& c) const {
            return std::hash<int>()(c.x) ^ (std::hash<int>()(c.y) << 1);
        }
    };
}

namespace simcore {

class SpatialGrid {
private:
    double cell_size;
    std::unordered_map<Coord, std::vector<Entity*>> grid;

    Coord get_coord(double px, double py) const {
        return {
            static_cast<int>(std::floor(px / cell_size)),
            static_cast<int>(std::floor(py / cell_size))
        };
    }

public:
    explicit SpatialGrid(double cellSize = 10.0) : cell_size(cellSize) {}

    void clear() {
        grid.clear();
    }

    void insert(Entity* entity, double x, double y) {
        Coord c = get_coord(x, y);
        grid[c].push_back(entity);
    }

    std::vector<Entity*> get_nearby(double x, double y) const {
        Coord c = get_coord(x, y);
        std::vector<Entity*> neighbors;

        // Check 3x3 surrounding cells
        for (int dx = -1; dx <= 1; ++dx) {
            for (int dy = -1; dy <= 1; ++dy) {
                Coord neighbor_cell = {c.x + dx, c.y + dy};
                auto it = grid.find(neighbor_cell);
                if (it != grid.end()) {
                    for (Entity* e : it->second) {
                        neighbors.push_back(e);
                    }
                }
            }
        }
        return neighbors;
    }
};

} // namespace simcore
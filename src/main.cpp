#include <iostream>
#include <memory>
#include "world/World.h"
#include "simcore/Agent.h"
#include "simcore/Signal.h"
#include "simcore/Goal.h"
#include "simcore/Action.h"

int main() {
    std::cout << "=== Renzo-SimCore Live 20-Tick Runner ===" << std::endl;
    World world(800, 600);

    auto scout = std::make_shared<Agent>(2, "Scout", 0.2, 0.1, 10);
    auto sentinel = std::make_shared<Agent>(3, "Sentinel", 0.2, 0.1, 10);

    scout->setGoal({"Secure Perimeter", {{"threat", 0.5}}});
    scout->addActionRule({"perimeter_locked", 0.9, true});

    world.addEntity(scout);
    world.addEntity(sentinel);

    world.emitSignal({1, "threat", 0.95});

    for (int tick = 0; tick < 20; ++tick) {
        world.update(1.0);
        std::cout << "--- Tick: " << tick << " ---" << std::endl;
        std::cout << "Scout Threat: " << scout->getBelief("threat") << std::endl;
        std::cout << "Sentinel Alert: " << sentinel->getBelief("alert") << std::endl;
        std::cout << "Goal: " << (scout->isGoalSatisfied() ? "SATISFIED" : "UNSATISFIED") << std::endl;
        std::cout << "Memory: " << sentinel->getMemory().size() << std::endl;
    }

    std::cout << "=== Simulation Complete ===" << std::endl;
    return 0;
}

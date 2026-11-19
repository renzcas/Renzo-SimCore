#include <cassert>
#include <cmath>
#include <iostream>
#include <memory>
#include "world/World.h"
#include "entities/Creature.h"
#include "simcore/Agent.h"
#include "simcore/Signal.h"
#include "simcore/Goal.h"

int main() {
    std::cout << "=== Running SimCore Layer 3 & 4 Closed-Loop Tests ===" << std::endl;
    World world(800, 600);
    auto scout = std::make_shared<Agent>(2, "Scout", 0.2, 0.1, 5);
    auto sentinel = std::make_shared<Agent>(3, "Sentinel", 0.2, 0.1, 5);
    world.addEntity(scout);
    world.addEntity(sentinel);

    // Layer 3: Goal & Decay
    scout->setGoal({"Secure Perimeter", {{"threat", 0.5}}});
    assert(!scout->isGoalSatisfied());

    // Tick 1: External threat arrives -> Scout threat reaches 0.85 (> 0.8) -> Scout flushes "alert" to bus
    world.emitSignal({1, "threat", 0.95});
    world.update(1.0);
    assert(std::abs(scout->getBelief("threat") - 0.85) < 1e-6);
    assert(scout->isGoalSatisfied());

    // Tick 2: World delivers Scout's "alert" action to Sentinel
    world.update(1.0);
    assert(sentinel->getBelief("alert") > 0.5);
    assert(sentinel->getMemory().size() == 2);

    std::cout << "All SimCore Layer 3 & 4 Tests Passed!" << std::endl;
    return 0;
}

#include <cassert>
#include <cmath>
#include <iostream>
#include <memory>
#include "world/World.h"
#include "entities/Creature.h"
#include "simcore/Agent.h"
#include "simcore/Signal.h"
#include "simcore/Goal.h"
#include "simcore/Action.h"

int main() {
    std::cout << "=== Running SimCore Layer 3, 4 & 5 Tests ===" << std::endl;
    World world(800, 600);
    auto scout = std::make_shared<Agent>(2, "Scout", 0.2, 0.1, 5);
    auto sentinel = std::make_shared<Agent>(3, "Sentinel", 0.2, 0.1, 5);
    world.addEntity(scout);
    world.addEntity(sentinel);

    scout->setGoal({"Secure Perimeter", {{"threat", 0.5}}});
    scout->addActionRule({"perimeter_locked", 0.9, true});
    assert(!scout->isGoalSatisfied());

    world.emitSignal({1, "threat", 0.95});
    world.update(1.0);
    assert(std::abs(scout->getBelief("threat") - 0.85) < 1e-6);
    assert(scout->isGoalSatisfied());

    world.update(1.0);
    assert(sentinel->getBelief("alert") > 0.5);
    assert(sentinel->getBelief("perimeter_locked") > 0.5);
    assert(sentinel->getMemory().size() == 3);

    std::cout << "All SimCore Layer 3, 4 & 5 Tests Passed!" << std::endl;
    return 0;
}

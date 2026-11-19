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
#include "simcore/BeliefLink.h"

int main() {
    std::cout << "=== Running SimCore Layer 3, 4, 5 & 8 Tests ===" << std::endl;
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

    auto agent = std::make_shared<Agent>(10, "Tester", 0.1, 0.0, 5);
    agent->addBeliefLink({"threat", "fear", 0.7});
    agent->addBeliefLink({"fear", "panic", 0.5});
    agent->addBeliefLink({"trust", "panic", -0.4});
    agent->setBelief("threat", 0.8);
    agent->setBelief("trust", 0.5);
    agent->update(1.0);
    assert(agent->getBelief("fear") > 0.5);
    assert(agent->getBelief("panic") > 0.0);
    double panic_with_trust = agent->getBelief("panic");

    auto baseline = std::make_shared<Agent>(11, "Baseline", 0.1, 0.0, 5);
    baseline->addBeliefLink({"threat", "fear", 0.7});
    baseline->addBeliefLink({"fear", "panic", 0.5});
    baseline->setBelief("threat", 0.8);
    baseline->update(1.0);
    assert(panic_with_trust < baseline->getBelief("panic"));

    std::cout << "All SimCore Tests Passed!" << std::endl;
    return 0;
}

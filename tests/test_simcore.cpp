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
    std::cout << "=== Running SimCore Layer 3 Tests (Goals & Decay) ===" << std::endl;
    World world(800, 600);
    auto agent = std::make_shared<Agent>(2, "Observer", 0.2, 0.1, 5);
    world.addEntity(agent);
    agent->setGoal({"Secure Perimeter", {{"threat", 0.5}}});
    assert(!agent->isGoalSatisfied());
    agent->receiveSignal({1, "threat", 0.8});
    agent->update(1.0);
    assert(std::abs(agent->getBelief("threat") - 0.7) < 1e-6);
    assert(agent->isGoalSatisfied());
    agent->update(5.0);
    assert(std::abs(agent->getBelief("threat") - 0.2) < 1e-6);
    assert(!agent->isGoalSatisfied());
    std::cout << "All SimCore Layer 3 Tests Passed!" << std::endl;
    return 0;
}

#include <iomanip>
#include <iostream>
#include <memory>
#include "world/World.h"
#include "simcore/Agent.h"
#include "simcore/Signal.h"
#include "simcore/Goal.h"
#include "simcore/Action.h"
#include "simcore/BeliefLink.h"

int main() {
    std::cout << "=== Renzo-SimCore 5-Agent Belief Network (50 Ticks) ===" << std::endl;
    World world(800, 600);

    auto scout    = std::make_shared<Agent>(2, "Scout",    0.15, 0.10, 12, AgentRole::Scout);
    auto sentinel = std::make_shared<Agent>(3, "Sentinel", 0.05, 0.10, 12, AgentRole::Sentinel);
    auto keeper   = std::make_shared<Agent>(4, "Keeper",   0.20, 0.05, 12, AgentRole::Keeper);
    auto trickster= std::make_shared<Agent>(5, "Trickster",0.20, 0.10, 12, AgentRole::Trickster);
    auto citizen  = std::make_shared<Agent>(6, "Citizen",  0.20, 0.10, 12, AgentRole::Citizen);

    for (const auto& agent : {scout, sentinel, keeper, trickster, citizen}) {
        agent->addBeliefLink({"threat", "fear", 0.7});
        agent->addBeliefLink({"fear", "panic", 0.5});
    }

    scout->setGoal({"Secure Perimeter", {{"threat", 0.5}}});
    scout->addActionRule({"perimeter_locked", 0.9, true});
    citizen->setGoal({"Stay Safe", {{"panic", 0.3}}});
    citizen->addActionRule({"seek_shelter", 0.8, true});

    world.addEntity(scout);
    world.addEntity(sentinel);
    world.addEntity(keeper);
    world.addEntity(trickster);
    world.addEntity(citizen);

    world.emitSignal({1, "threat", 0.95});

    for (int tick = 0; tick < 50; ++tick) {
        world.update(1.0);
        std::cout << "--- Tick " << tick << " ---" << std::endl;
        auto printAgent = [](const char* roleName, const std::shared_ptr<Agent>& a) {
            std::cout << std::left << std::setw(10) << roleName
                      << " threat=" << std::fixed << std::setprecision(2) << a->getBelief("threat")
                      << " fear=" << a->getBelief("fear")
                      << " panic=" << a->getBelief("panic")
                      << " | Goal=" << (a->isGoalSatisfied() ? "SATISFIED  " : "UNSATISFIED")
                      << " | Mem=" << a->getMemory().size() << std::endl;
        };
        printAgent("Scout", scout);
        printAgent("Sentinel", sentinel);
        printAgent("Keeper", keeper);
        printAgent("Trickster", trickster);
        printAgent("Citizen", citizen);
    }

    std::cout << "=== 50-Tick Belief Network Complete ===" << std::endl;
    return 0;
}

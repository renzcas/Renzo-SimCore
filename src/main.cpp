#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <memory>
#include <ostream>
#include <sstream>
#include <string>
#include "world/World.h"
#include "simcore/Agent.h"
#include "simcore/Signal.h"
#include "simcore/Goal.h"
#include "simcore/Action.h"
#include "simcore/BeliefLink.h"

namespace fs = std::filesystem;

namespace {

std::string escapeJson(const std::string& input) {
    std::ostringstream out;
    for (unsigned char c : input) {
        switch (c) {
            case '"': out << "\\\""; break;
            case '\\': out << "\\\\"; break;
            case '\b': out << "\\b"; break;
            case '\f': out << "\\f"; break;
            case '\n': out << "\\n"; break;
            case '\r': out << "\\r"; break;
            case '\t': out << "\\t"; break;
            default:
                if (c < 0x20) {
                    out << "\\u00";
                    constexpr char hex[] = "0123456789abcdef";
                    out << hex[(c >> 4) & 0x0f] << hex[c & 0x0f];
                } else {
                    out << static_cast<char>(c);
                }
        }
    }
    return out.str();
}

const char* roleToString(AgentRole role) noexcept {
    switch (role) {
        case AgentRole::Scout: return "Scout";
        case AgentRole::Sentinel: return "Sentinel";
        case AgentRole::Keeper: return "Keeper";
        case AgentRole::Trickster: return "Trickster";
        case AgentRole::Citizen: return "Citizen";
    }
    return "Citizen";
}

void emitAgentSnapshotNdjson(
    std::ostream& out,
    int tick,
    double dt,
    const std::shared_ptr<Agent>& agent
) {
    if (!agent) return;

    out << "{\"tick\":" << tick
        << ",\"dt\":" << dt
        << ",\"agentId\":" << agent->getId()
        << ",\"agentName\":\"" << escapeJson(agent->getName()) << "\""
        << ",\"role\":\"" << roleToString(agent->getRole()) << "\""
        << ",\"goalSatisfied\":" << (agent->isGoalSatisfied() ? "true" : "false")
        << ",\"memorySize\":" << agent->getMemory().size()
        << ",\"beliefs\":{"
        << "\"threat\":" << agent->getBelief("threat")
        << ",\"fear\":" << agent->getBelief("fear")
        << ",\"panic\":" << agent->getBelief("panic")
        << ",\"trust\":" << agent->getBelief("trust")
        << ",\"calm\":" << agent->getBelief("calm")
        << "}"
        << ",\"metrics\":{"
        << "\"resilience\":" << agent->getResilience()
        << "}"
        << "}\n";
    out.flush();
}

}  // namespace

int main(int argc, char* argv[]) {
    bool ndjsonEnabled = false;
    std::string ndjsonPath;
    int ticks = 50;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--ndjson") {
            ndjsonEnabled = true;
            if (i + 1 < argc && argv[i + 1][0] != '-') {
                ndjsonPath = argv[++i];
            }
        } else if (arg == "--ticks" && i + 1 < argc) {
            ticks = std::max(1, std::stoi(argv[++i]));
        }
    }

    std::ofstream fileOut;
    std::ostream* ndjsonStream = &std::cout;
    if (ndjsonEnabled && !ndjsonPath.empty() && ndjsonPath != "-") {
        fs::path outPath(ndjsonPath);
        if (outPath.has_parent_path()) {
            fs::create_directories(outPath.parent_path());
        }
        fileOut.open(outPath, std::ios::out | std::ios::trunc);
        if (!fileOut) {
            std::cerr << "Failed to open NDJSON output file: " << ndjsonPath << std::endl;
            return 1;
        }
        ndjsonStream = &fileOut;
    }

    if (!ndjsonEnabled) {
        std::cout << "=== Renzo-SimCore 5-Agent Balance of Forces (" << ticks << " Ticks) ===" << std::endl;
    }

    World world(800, 600);

    auto scout    = std::make_shared<Agent>(2, "Scout",    0.15, 0.10, 12, AgentRole::Scout);
    auto sentinel = std::make_shared<Agent>(3, "Sentinel", 0.05, 0.10, 12, AgentRole::Sentinel);
    auto keeper   = std::make_shared<Agent>(4, "Keeper",   0.20, 0.05, 12, AgentRole::Keeper);
    auto trickster= std::make_shared<Agent>(5, "Trickster",0.20, 0.10, 12, AgentRole::Trickster);
    auto citizen  = std::make_shared<Agent>(6, "Citizen",  0.20, 0.10, 12, AgentRole::Citizen);

    const std::shared_ptr<Agent> roster[] = {scout, sentinel, keeper, trickster, citizen};

    for (const auto& agent : roster) {
        agent->addBeliefLink({"threat", "fear", 0.7});
        agent->addBeliefLink({"fear", "panic", 0.5});
        agent->addBeliefLink({"trust", "calm", 0.6});
        agent->addBeliefLink({"calm", "fear", -0.3});
        agent->addBeliefLink({"calm", "panic", -0.4});
    }

    keeper->setBelief("trust", 0.8);
    citizen->setBelief("trust", 0.5);

    scout->setGoal({"Secure Perimeter", {{"threat", 0.5}}});
    scout->addActionRule({"perimeter_locked", 0.9, true});
    citizen->setGoal({"Stay Safe", {{"panic", 0.3}}});
    citizen->addActionRule({"seek_shelter", 0.8, true});

    for (const auto& agent : roster) {
        world.addEntity(agent);
    }

    world.emitSignal({1, "threat", 0.95});

    for (int tick = 0; tick < ticks; ++tick) {
        world.update(1.0);
        if (ndjsonEnabled) {
            for (const auto& agent : roster) {
                emitAgentSnapshotNdjson(*ndjsonStream, tick, 1.0, agent);
            }
        } else {
            std::cout << "--- Tick " << tick << " ---" << std::endl;
            auto printAgent = [](const char* roleName, const std::shared_ptr<Agent>& a) {
                std::cout << std::left << std::setw(10) << roleName
                          << " threat=" << std::fixed << std::setprecision(2) << a->getBelief("threat")
                          << " fear=" << a->getBelief("fear")
                          << " panic=" << a->getBelief("panic")
                          << " calm=" << a->getBelief("calm")
                          << " | Goal=" << (a->isGoalSatisfied() ? "SATISFIED  " : "UNSATISFIED")
                          << " | Mem=" << a->getMemory().size() << std::endl;
            };
            printAgent("Scout", scout);
            printAgent("Sentinel", sentinel);
            printAgent("Keeper", keeper);
            printAgent("Trickster", trickster);
            printAgent("Citizen", citizen);
        }
    }

    if (!ndjsonEnabled) {
        std::cout << "=== " << ticks << "-Tick Balance of Forces Complete ===" << std::endl;
    }
    return 0;
}

#include "simcore/Agent.h"
#include <algorithm>

Agent::Agent(uint64_t id, const std::string& name)
    : Entity(id, name) {}

void Agent::receiveSignal(const Signal& sig) {
    inbox.push_back(sig);
}

double Agent::getBelief(const std::string& key) const {
    auto it = beliefs.find(key);
    return (it != beliefs.end()) ? it->second : 0.0;
}

void Agent::setBelief(const std::string& key, double value) {
    beliefs[key] = std::clamp(value, 0.0, 1.0);
}

void Agent::update(double dt) {
    for (const auto& sig : inbox) {
        double current = getBelief(sig.type);
        setBelief(sig.type, current + (sig.strength * dt));
    }
    inbox.clear();
}

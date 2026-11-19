#include "simcore/Agent.h"
#include <algorithm>

Agent::Agent(uint64_t id, const std::string& name, double attention_threshold, double decay_rate, size_t memory_capacity)
    : Entity(id, name), attention_threshold(attention_threshold), decay_rate(decay_rate), memory_capacity(memory_capacity) {}

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

void Agent::setGoal(const Goal& goal) {
    active_goal = goal;
}

bool Agent::isGoalSatisfied() const {
    if (!active_goal) return false;
    return active_goal->isSatisfied(beliefs);
}

const std::vector<Signal>& Agent::getMemory() const {
    return short_term_memory;
}

std::vector<Signal> Agent::flushActions() {
    std::vector<Signal> actions;
    actions.swap(pending_actions);
    return actions;
}

void Agent::update(double dt) {
    // 1. Process inbox through attention filter
    for (const auto& sig : inbox) {
        if (sig.strength < attention_threshold) {
            continue;
        }

        double current = getBelief(sig.type);
        setBelief(sig.type, current + (sig.strength * dt));

        short_term_memory.push_back(sig);
        if (short_term_memory.size() > memory_capacity) {
            short_term_memory.erase(short_term_memory.begin());
        }
    }
    inbox.clear();

    // 2. Apply belief decay over time (dt)
    for (auto& [key, val] : beliefs) {
        val = std::max(0.0, val - (decay_rate * dt));
    }

    // 3. Trigger action if threat is high
    if (getBelief("threat") > 0.8) {
        pending_actions.push_back({getId(), "alert", getBelief("threat")});
    }
}

#include "simcore/Agent.h"
#include <algorithm>

Agent::Agent(uint64_t id, const std::string& name, double attention_threshold, double decay_rate, size_t memory_capacity, AgentRole role)
    : Entity(id, name), role(role), attention_threshold(attention_threshold), decay_rate(decay_rate), memory_capacity(memory_capacity) {}

AgentRole Agent::getRole() const noexcept {
    return role;
}

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

double Agent::getResilience() const {
    double trust = getBelief("trust");
    double calm = getBelief("calm");
    double fear = getBelief("fear");
    double panic = getBelief("panic");
    return std::clamp(trust + calm - fear - panic, 0.0, 1.0);
}

void Agent::addBeliefLink(const BeliefLink& link) {
    belief_links.push_back(link);
}

void Agent::setGoal(const Goal& goal) {
    active_goal = goal;
}

bool Agent::isGoalSatisfied() const {
    if (!active_goal) return false;
    return active_goal->isSatisfied(beliefs);
}

void Agent::addActionRule(const ActionRule& rule) {
    action_rules.push_back(rule);
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

    for (auto& [key, val] : beliefs) {
        val = std::max(0.0, val - (decay_rate * dt));
    }

    for (const auto& link : belief_links) {
        double src_val = getBelief(link.source);
        if (src_val > 0.0) {
            double propagated = src_val * link.weight * dt;
            setBelief(link.target, getBelief(link.target) + propagated);
        }
    }

    if (getBelief("threat") > 0.8) {
        pending_actions.push_back({getId(), "alert", getBelief("threat")});
    }

    switch (role) {
        case AgentRole::Scout:
            if (getBelief("threat") > 0.3) {
                pending_actions.push_back({getId(), "scout_report", getBelief("threat")});
            }
            break;
        case AgentRole::Keeper:
            if (getBelief("threat") > 0.25) {
                pending_actions.push_back({getId(), "verified_status", 0.5});
            }
            break;
        case AgentRole::Trickster:
            if (getBelief("threat") > 0.4 || getBelief("noise") > 0.2) {
                pending_actions.push_back({getId(), "noise", 0.65});
            }
            break;
        case AgentRole::Sentinel:
        case AgentRole::Citizen:
        default:
            break;
    }

    if (active_goal) {
        bool satisfied = isGoalSatisfied();
        for (const auto& rule : action_rules) {
            if (rule.trigger_when_satisfied == satisfied) {
                pending_actions.push_back({getId(), rule.action_type, rule.strength});
            }
        }
    }
}

#pragma once
#include "core/Entity.h"
#include "simcore/Signal.h"
#include "simcore/Goal.h"
#include "simcore/Action.h"
#include "simcore/BeliefLink.h"
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

enum class AgentRole {
    Scout,
    Sentinel,
    Keeper,
    Trickster,
    Citizen
};

class Agent : public Entity {
public:
    Agent(uint64_t id, const std::string& name, double attention_threshold, double decay_rate, size_t memory_capacity, AgentRole role = AgentRole::Citizen);

    AgentRole getRole() const noexcept;
    void receiveSignal(const Signal& sig);
    double getBelief(const std::string& key) const;
    void setBelief(const std::string& key, double value);
    void addBeliefLink(const BeliefLink& link);

    void setGoal(const Goal& goal);
    bool isGoalSatisfied() const;
    void addActionRule(const ActionRule& rule);

    const std::vector<Signal>& getMemory() const;
    std::vector<Signal> flushActions();

    void update(double dt) override;

private:
    AgentRole role;
    double attention_threshold;
    double decay_rate;
    size_t memory_capacity;

    std::vector<Signal> inbox;
    std::vector<Signal> short_term_memory;
    std::unordered_map<std::string, double> beliefs;
    std::vector<BeliefLink> belief_links;
    std::optional<Goal> active_goal;
    std::vector<ActionRule> action_rules;
    std::vector<Signal> pending_actions;
};

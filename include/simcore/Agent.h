#pragma once
#include "core/Entity.h"
#include "simcore/Signal.h"
#include "simcore/Goal.h"
#include <string>
#include <unordered_map>
#include <vector>
#include <optional>

class Agent : public Entity {
private:
    std::unordered_map<std::string, double> beliefs;
    std::vector<Signal> inbox;
    std::vector<Signal> short_term_memory;
    std::vector<Signal> pending_actions;
    double attention_threshold;
    double decay_rate;
    size_t memory_capacity;
    std::optional<Goal> active_goal;

public:
    Agent(uint64_t id, const std::string& name, double attention_threshold = 0.2, double decay_rate = 0.05, size_t memory_capacity = 10);

    void receiveSignal(const Signal& sig);
    double getBelief(const std::string& key) const;
    void setBelief(const std::string& key, double value);

    void setGoal(const Goal& goal);
    bool isGoalSatisfied() const;

    const std::vector<Signal>& getMemory() const;
    std::vector<Signal> flushActions();

    void update(double dt) override;
};

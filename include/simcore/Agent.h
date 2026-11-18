#pragma once
#include "core/Entity.h"
#include "simcore/Signal.h"
#include <string>
#include <unordered_map>
#include <vector>

class Agent : public Entity {
private:
    std::unordered_map<std::string, double> beliefs;
    std::vector<Signal> inbox;

public:
    Agent(uint64_t id, const std::string& name);

    void receiveSignal(const Signal& sig);
    double getBelief(const std::string& key) const;
    void setBelief(const std::string& key, double value);

    void update(double dt) override;
};

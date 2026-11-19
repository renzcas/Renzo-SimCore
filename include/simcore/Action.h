#pragma once
#include <string>

struct ActionRule {
    std::string action_type;
    double strength;
    bool trigger_when_satisfied;
};

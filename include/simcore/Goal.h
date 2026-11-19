#pragma once
#include <string>
#include <unordered_map>

struct Goal {
    std::string description;
    std::unordered_map<std::string, double> target_beliefs;

    bool isSatisfied(const std::unordered_map<std::string, double>& current_beliefs) const {
        for (const auto& [key, target_val] : target_beliefs) {
            auto it = current_beliefs.find(key);
            if (it == current_beliefs.end() || it->second < target_val) {
                return false;
            }
        }
        return true;
    }
};

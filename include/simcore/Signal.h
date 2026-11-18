#pragma once
#include <string>
#include <cstdint>

struct Signal {
    uint64_t sourceId{0};
    std::string type;
    double strength{0.0};
};

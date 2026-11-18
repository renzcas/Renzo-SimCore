#pragma once
#include "simcore/Signal.h"
#include <vector>

class SignalBus {
private:
    std::vector<Signal> pending;

public:
    void publish(const Signal& sig) {
        pending.push_back(sig);
    }

    std::vector<Signal> drain() {
        std::vector<Signal> batch;
        batch.swap(pending);
        return batch;
    }

    size_t size() const noexcept {
        return pending.size();
    }
};
#pragma once
#include "TrafficStrategy.h"

class FixedStrategy : public TrafficStrategy {
public:
    void update(TrafficLight& light) override;
};

#pragma once
#include "TrafficStrategy.h"

class AdaptiveStrategy : public TrafficStrategy {
public:
    void update(TrafficLight& light) override;
};
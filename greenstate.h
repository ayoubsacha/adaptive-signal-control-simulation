#pragma once
#include "trafficlightState.h"

class GreenState : public TrafficLightState {
public:
    void next(TrafficLight& light) override;
    float duration() const override { return 7.0f; }
};


#pragma once
#include "trafficlightState.h"

class RedState : public TrafficLightState {
public:
    void next(TrafficLight& light) override;
    float duration() const override { return 5.0f; }
};

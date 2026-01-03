#include "FixedStrategy.h"
#include "TrafficLight.h"

void FixedStrategy::update(TrafficLight& light) {
    light.switchState();
}
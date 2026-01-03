#include "greenstate.h"
#include "TrafficLight.h"
#include "yellowstate.h"

void GreenState::next(TrafficLight& light) {
    light.setState(new YellowState());
}

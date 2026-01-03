#include "redstate.h"
#include "TrafficLight.h"
#include "greenstate.h"

void RedState::next(TrafficLight& light) {
    light.setState(new GreenState());
}

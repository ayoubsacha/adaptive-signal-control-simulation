#include "YellowState.h"
#include "TrafficLight.h"
#include "RedState.h"

void YellowState::next(TrafficLight& light) {
    light.setState(new RedState());
}

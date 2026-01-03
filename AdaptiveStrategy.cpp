#include "AdaptiveStrategy.h"
#include "trafficLight.h"
#include "sensorr.h"

void AdaptiveStrategy::update(TrafficLight& light) {
    if (light.getCapteur() && light.getCapteur()->obtenirLongueurFile() > 2) {
        light.extendGreen(3.0f);
    }
    else {
        light.switchState();
    }
}
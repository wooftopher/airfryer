#include "heater.hpp"

void Heater::setTargetTemp(int temp) {
    targetTemp = temp;
}

int Heater::getTemp() {
    return currentTemp;
}

void Heater::update() {
    if (currentTemp < targetTemp) {
        currentTemp++;
    } 
    else if (currentTemp > targetTemp) {
        currentTemp--;
    }

    // 🔥 safety clamp (ambient temperature)
    if (currentTemp < 25) {
        currentTemp = 25;
    }
}
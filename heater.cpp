#include "heater.hpp"

static int currentTemp = 25;
static int targetTemp = 25;

void Heater::setTargetTemp(int temp) {
    targetTemp = temp;
}

int Heater::getTemp() {
    return currentTemp;
}

void Heater::update() {
    if (currentTemp < targetTemp) {
        currentTemp++;
    } else if (currentTemp > targetTemp) {
        currentTemp--;
    }
}
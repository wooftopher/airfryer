#include "heater.hpp"
#include <iostream>

static int currentTemp = 25;   // start at room temp
static int targetTemp = 25;

void Heater::setTargetTemp(int temp) {
    targetTemp = temp;
    std::cout << "Target temperature set to: " << targetTemp << std::endl;
}

int Heater::getTemp() {
    return currentTemp;
}

void Heater::update() {
    // simple simulation: move toward target
    if (currentTemp < targetTemp) {
        currentTemp++;
    } else if (currentTemp > targetTemp) {
        currentTemp--;
    }

    std::cout << "Current temperature: " << currentTemp << std::endl;
}
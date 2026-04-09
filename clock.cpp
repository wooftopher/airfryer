#include "clock.hpp"
#include <iostream>

static int timeLeft = 0;

void Clock::setTime(int seconds) {
    timeLeft = seconds;
    std::cout << "Timer set to: " << timeLeft << " seconds" << std::endl;
}

void Clock::tick() {
    if (timeLeft > 0) {
        timeLeft--;
    }
}

void Clock::update() {
    tick();

    std::cout << "Time left: " << timeLeft << std::endl;
}
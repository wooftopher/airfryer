#include <iostream>
#include <cstdint>
#include <thread>
#include <chrono>

#include "device.hpp"
#include "keypad.hpp"
#include "heater.hpp"
#include "clock.hpp"
#include "protocol.hpp"

int main() {
    Keypad keypad;
    // Heater heater;
    // Clock clock;

    while (true) {
        keypad.update();
        // heater.update();
        // clock.update();

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    return 0;
}
#include "keypad.hpp"
#include <iostream>

uint8_t Keypad::getKey() {
    uint8_t key;
    std::cout << "Press a key (0-15): ";
    std::cin >> key;

    if (key > 15) {
        std::cout << "Invalid key, returning 0\n";
        return 0;
    }

    return key;
}

void Keypad::update() {
    uint8_t key = getKey();

    // For now just print it (later you’ll send via protocol)
    std::cout << "Key pressed: " << static_cast<int>(key) << std::endl;
}
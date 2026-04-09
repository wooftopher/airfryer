#include "keypad.hpp"
#include <iostream>

Input Keypad::getKey() {
    int key;
    std::cin >> key;

    switch (key) {
        case 1: return Input::POWER;
        case 2: return Input::START;
        case 3: return Input::STOP;

        case 4: return Input::SET_TEMP_50;
        case 5: return Input::SET_TEMP_100;
        case 6: return Input::SET_TEMP_150;

        default:
            return Input::NONE;
    }
}


void Keypad::update() {
    Input key = getKey();

    std::cout << "Key pressed: " << static_cast<int>(key) << std::endl;
}
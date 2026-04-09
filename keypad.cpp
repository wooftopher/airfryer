#include "keypad.hpp"
#include <iostream>

Input Keypad::getKey() {
    int key;
    std::cout << "Press key: ";
    std::cin >> key;

    switch (key) {
        case 1: return Input::POWER;
        case 2: return Input::START;
        case 3: return Input::STOP;
        case 4: return Input::SET_TEMP;
        case 5: return Input::SET_TIME;
        case 6: return Input::ENTER;

        case 7: return Input::DIGIT_0;
        case 8: return Input::DIGIT_1;
        case 9: return Input::DIGIT_2;
        case 10: return Input::DIGIT_3;
        case 11: return Input::DIGIT_4;
        case 12: return Input::DIGIT_5;
        case 13: return Input::DIGIT_6;
        case 14: return Input::DIGIT_7;
        case 15: return Input::DIGIT_8;
        case 16: return Input::DIGIT_9;

        default:
            return Input::NONE;
    }
}


void Keypad::update() {
    Input key = getKey();

    // For now just print it (later you’ll send via protocol)
    std::cout << "Key pressed: " << static_cast<int>(key) << std::endl;
}
#pragma once

enum class Input {
    NONE,
    POWER,
    START,
    STOP,
    SET_TEMP,
    SET_TIME,
    ENTER,

    DIGIT_0,
    DIGIT_1,
    DIGIT_2,
    DIGIT_3,
    DIGIT_4,
    DIGIT_5,
    DIGIT_6,
    DIGIT_7,
    DIGIT_8,
    DIGIT_9
};

#include <cstdint>
#include "device.hpp"

class Keypad : public Device {
public:
    Input getKey();
    void update() override;
};
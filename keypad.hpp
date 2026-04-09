#pragma once

#include <cstdint>
#include "device.hpp"

enum class Input {
    NONE,
    POWER,
    START,
    STOP,
    SET_TEMP_50,
    SET_TEMP_100,
    SET_TEMP_150,
};

class Keypad : public Device {
public:
    Input getKey();
    void update() override;
};
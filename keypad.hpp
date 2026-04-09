#pragma once

#include <cstdint>
#include "device.hpp"

class Keypad : public Device {
public:
    uint8_t getKey();
    void update() override;
};
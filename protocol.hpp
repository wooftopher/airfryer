#pragma once

#include <cstdint>
#include <string>

enum class Command : uint8_t {
    SET_TEMP,
    START,
    STOP,
    SET_TIMER
};

class UART {
public:
    void send(const std::string& msg);
    std::string receive();

private:
    std::string buffer;
};

class I2C {
public:
    void write(uint8_t address, uint8_t data);
    uint8_t read(uint8_t address);

private:
    uint8_t memory[256] = {0}; // simple addressable space
};

class SPI {
public:
    uint8_t transfer(uint8_t data);

private:
    uint8_t lastData = 0;
};
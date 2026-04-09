#pragma once

#include <cstdint>
#include <string>
#include <queue>

class UART {
public:
    void send(const std::string& msg);

    // simulate incoming data (like hardware RX interrupt)
    void injectRX(const std::string& msg);

    // check if data is available
    bool available();

    // read one message
    std::string read();

private:
    std::queue<std::string> rxQueue;
};

// class I2C {
// public:
//     void write(uint8_t address, uint8_t data);
//     uint8_t read(uint8_t address);

// private:
//     uint8_t memory[256] = {0}; // simple addressable space
// };

// class SPI {
// public:
//     uint8_t transfer(uint8_t data);

// private:
//     uint8_t lastData = 0;
// };
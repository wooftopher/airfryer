#include "protocol.hpp"
#include <iostream>

//
// UART
//

void UART::send(const std::string& msg) {
    std::cout << "[UART SEND] " << msg << std::endl;
    buffer = msg;
}

std::string UART::receive() {
    std::cout << "[UART RECEIVE]" << std::endl;
    return buffer;
}

//
// I2C
//

void I2C::write(uint8_t address, uint8_t data) {
    std::cout << "[I2C WRITE] Addr: " << static_cast<int>(address)
              << " Data: " << static_cast<int>(data) << std::endl;

    memory[address] = data;
}

uint8_t I2C::read(uint8_t address) {
    std::cout << "[I2C READ] Addr: " << static_cast<int>(address)
              << " Data: " << static_cast<int>(memory[address]) << std::endl;

    return memory[address];
}

//
// SPI
//

uint8_t SPI::transfer(uint8_t data) {
    std::cout << "[SPI TRANSFER] Sent: " << static_cast<int>(data)
              << " Received: " << static_cast<int>(lastData) << std::endl;

    uint8_t received = lastData;
    lastData = data;

    return received;
}
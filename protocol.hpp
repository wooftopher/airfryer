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
};

class I2C {
public:
    void write(uint8_t address, uint8_t data);
    uint8_t read(uint8_t address);
};

class SPI {
public:
    uint8_t transfer(uint8_t data);
};
#include <iostream>
#include <cstdint>
#include <thread>
#include <chrono>

#include <queue>
#include <mutex>
#include <thread>

#include "device.hpp"
#include "keypad.hpp"
#include "heater.hpp"
#include "clock.hpp"
#include "protocol.hpp"


std::queue<Input> eventQueue;
std::mutex queueMutex;
std::atomic<bool> running = true;

struct SystemState {
    bool power = false;
    bool heating = false;

    int targetTemp = 0;
    int targetTime = 0;

    int clockTick = 0;
};

void resetSystem(SystemState& state, Heater& heater) {
    state.heating = false;
    state.targetTemp = 25;
    state.targetTime = 0;

    heater.setTargetTemp(0);

    std::cout << "SYSTEM RESET\n";
}

void simulateUART(UART& uart)
{
    std::this_thread::sleep_for(std::chrono::seconds(5));
    uart.injectRX("POWER");

    std::this_thread::sleep_for(std::chrono::seconds(1));
    uart.injectRX("TEMP_100");

    std::this_thread::sleep_for(std::chrono::seconds(1));
    uart.injectRX("START");
}

Input parseUARTCommand(const std::string& cmd)
{
    if (cmd == "POWER") return Input::POWER;
    if (cmd == "START") return Input::START;
    if (cmd == "STOP") return Input::STOP;
    if (cmd == "TEMP_100") return Input::SET_TEMP_100;
    if (cmd == "TEMP_50") return Input::SET_TEMP_50;

    return Input::NONE;
}

void uartTask(UART& uart)
{
    while (true)
    {
        if (uart.available())
        {
            std::string msg = uart.read();
            Input input = parseUARTCommand(msg);

            if (input != Input::NONE)
            {
                std::lock_guard<std::mutex> lock(queueMutex);
                eventQueue.push(input);
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}

void handleInput(Input input, SystemState& state, Heater& heater) {

    // 🔴 POWER GATE
    if (!state.power && input != Input::POWER) {
        std::cout << "ERROR: Device not ON\n";
        return;
    }

    switch (input) {

        case Input::POWER:
            state.power = !state.power;

            if (state.power) {
                std::cout << "SYSTEM ON\n";
            } else {
                std::cout << "SYSTEM OFF\n";
                resetSystem(state, heater);
            }
            break;

        case Input::START:
            state.heating = true;
            heater.setTargetTemp(state.targetTemp);
            std::cout << "HEATING STARTED\n";
            break;

        case Input::STOP:
            state.heating = false;
            heater.setTargetTemp(0);
            std::cout << "HEATING STOPPED\n";
            break;

        case Input::SET_TEMP_50:
            state.targetTemp = 50;
            std::cout << "TEMP SET TO 50\n";
            break;

        case Input::SET_TEMP_100:
            state.targetTemp = 100;
            std::cout << "TEMP SET TO 100\n";
            break;

        case Input::SET_TEMP_150:
            state.targetTime = 150;
            std::cout << "TIME SET TO 150\n";
            break;

        default:
            break;
    }
}

void inputThread(Keypad& keypad) {
    while (running) {
        Input in = keypad.getKey();

        std::lock_guard<std::mutex> lock(queueMutex);
        eventQueue.push(in);
    }
}

void timerInterrupt(SystemState& state, Heater& heater)
{
    while (true)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));

        // "timer interrupt"
        if (state.power)
        {
            heater.update();
        }

        state.clockTick++;
    }
}

int main() {
    Keypad keypad;
    Heater heater;
    SystemState state;
    UART uart;

    std::thread t(inputThread, std::ref(keypad));
    std::thread uartSimThread(simulateUART, std::ref(uart));
    std::thread uartTaskThread(uartTask, std::ref(uart));
    std::thread timerThread(timerInterrupt, std::ref(state), std::ref(heater));

    auto lastPrint = std::chrono::steady_clock::now();

    while (true) {

        // 🔥 process events (interrupt queue)
        {
            std::lock_guard<std::mutex> lock(queueMutex);

            while (!eventQueue.empty()) {
                Input input = eventQueue.front();
                eventQueue.pop();

                handleInput(input, state, heater);
            }
        }

        if (state.power) {

            auto now = std::chrono::steady_clock::now();

            if (std::chrono::duration_cast<std::chrono::seconds>(now - lastPrint).count() >= 3) {
                std::cout << "TEMP: " << heater.getTemp() << std::endl;
                lastPrint = now;
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }

    running = false;

    t.join();
    uartSimThread.join();
    uartTaskThread.join();
    timerThread.join();
}


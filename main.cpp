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

struct SystemState {
    bool power = false;
    bool heating = false;

    int targetTemp = 0;
    int targetTime = 0;

    int inputBuffer = 0;
    bool enteringTemp = false;
    bool enteringTime = false;
};

void resetSystem(SystemState& state, Heater& heater) {
    state.heating = false;
    state.targetTemp = 25;
    state.targetTime = 0;
    state.inputBuffer = 0;
    state.enteringTemp = false;
    state.enteringTime = false;

    heater.setTargetTemp(0);

    std::cout << "SYSTEM RESET\n";
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
            break;

        case Input::STOP:
            state.heating = false;
            heater.setTargetTemp(0);
            break;

        case Input::SET_TEMP:
            state.enteringTemp = true;
            state.enteringTime = false;
            state.inputBuffer = 0;
            break;

        case Input::SET_TIME:
            state.enteringTime = true;
            state.enteringTemp = false;
            state.inputBuffer = 0;
            break;

        case Input::ENTER:
            if (state.enteringTemp) {
                state.targetTemp = state.inputBuffer;
                state.enteringTemp = false;
            }
            else if (state.enteringTime) {
                state.targetTime = state.inputBuffer;
                state.enteringTime = false;
            }
            state.inputBuffer = 0;
            break;

        default:
            if (input >= Input::DIGIT_0 && input <= Input::DIGIT_9) {
                int digit = static_cast<int>(input) - static_cast<int>(Input::DIGIT_0);
                state.inputBuffer = state.inputBuffer * 10 + digit;

                std::cout << "BUFFER: " << state.inputBuffer << std::endl;
            }
            break;
    }
}

std::queue<Input> eventQueue;
std::mutex queueMutex;
std::atomic<bool> running = true;


void inputThread(Keypad& keypad) {
    while (running) {
        Input in = keypad.getKey(); // blocking is OK HERE

        std::lock_guard<std::mutex> lock(queueMutex);
        eventQueue.push(in);
    }
}

int main() {
    Keypad keypad;
    Heater heater;
    SystemState state;

    std::thread t(inputThread, std::ref(keypad));

    auto lastPrint = std::chrono::steady_clock::now();

    while (true) {

        // 🔥 process "interrupts"
        {
            std::lock_guard<std::mutex> lock(queueMutex);

            while (!eventQueue.empty()) {
                Input input = eventQueue.front();
                eventQueue.pop();

                handleInput(input, state, heater);
            }
        }

        heater.update();

        auto now = std::chrono::steady_clock::now();
        if (std::chrono::duration_cast<std::chrono::seconds>(now - lastPrint).count() >= 3) {
            std::cout << "TEMP: " << heater.getTemp() << std::endl;
            lastPrint = now;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }

    running = false;
    t.join();
}

#pragma once

class Heater {
public:
    void setTargetTemp(int temp);
    int getTemp();
    void update();

private:
    int currentTemp = 25;
    int targetTemp = 25;
};
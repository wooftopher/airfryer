#pragma once

class Device {
public:
    virtual void update() = 0;
    virtual ~Device() = default;
};
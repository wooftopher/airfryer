class Heater : public Device {
public:
    void setTargetTemp(int temp);
    int getTemp();

    void update() override;
};
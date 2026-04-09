class Clock : public Device {
public:
    void setTime(int seconds);
    void tick();

    void update() override;
};
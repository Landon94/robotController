#include "include/PWM.hpp"
#include <vector>

class Servo : public PWM {
    public:
        Servo(std::string channelStr, std::vector<uint8_t> address = {});

        void angle(int8_t angle);
        void pulseWidthTime(uint16_t pulseWidthTime);

    private:
        double freqHz = 50;
        uint16_t MaxPw = 2500;
        uint16_t MinPw = 500;
        uint16_t PERIOD = 4095;
};
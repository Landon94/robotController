#include "include/I2C.hpp"
#include <cstdint>
#include <vector>
#include <string>


class PWM: public I2C {
    public:

    PWM(std::string pinName, std::vector<uint8_t> address = {}); 

    void setFreq(double freq);

    void setPeriod(uint16_t arr);
    uint16_t getPeriod();

    void setPrescaler(uint16_t prescaler);
    uint16_t getPrescaler();

    void setPulseWidth(uint16_t PulseWidth);
    uint16_t getPulseWidth();

    void setPulseWidthPercentage(uint8_t pulseWidthPercentage);
    uint8_t getPulseWidthPercentage();


    private:
        int pulseWidth;
        int channel;
        double freqHz;

        uint8_t timerIdx;
        uint16_t prescaler;
        uint16_t pulseWidth;

        static constexpr uint8_t REG_CHN = 0x20;
        static constexpr uint8_t REG_PSC = 0x40;
        static constexpr uint8_t REG_ARR = 0x44;
        static constexpr uint8_t REG_PSC2 = 0x50;
        static constexpr uint8_t REG_ARR2 = 0x54;

        static constexpr double CLOCK = 72000000.0;
        static inline uint16_t timerArr[7] = {1,1,1,1,1,1,1};
        std::vector<uint8_t> ADDR = {0x14, 0x15, 0x16};
};
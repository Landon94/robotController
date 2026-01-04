#include "include/Servo.hpp"

Servo::Servo(std::string channelStr, std::vector<uint8_t> address) :
    PWM::PWM(channelStr, address)
{
    setPeriod(PERIOD);
    double psc_d = CLOCK / freqHz / static_cast<double>(PERIOD);
    uint16_t psc = static_cast<uint16_t>(std::round(psc_d));
    setPrescaler(psc);
}

void Servo::angle(int8_t angle) {
    if (angle < -90) angle = -90;
    if (angle > 90) angle = 90;

    uint16_t pwt = (angle - (-90)) * (MaxPw - MinPw) / (90 - (-90)) + MinPw;
    pulseWidthTime(pwt);
}

void Servo::pulseWidthTime(uint16_t pwt) {
    if (pwt > MaxPw) pwt = MaxPw;
    if (pwt < MinPw) pwt = MinPw;

    double pwr = static_cast<double>(pwt) / 20000.0;
    uint16_t value = static_cast<uint16_t>(std::round(pwr * PERIOD));
    setPulseWidth(value);
}

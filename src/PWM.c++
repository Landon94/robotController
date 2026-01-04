#include "include/PWM.hpp"
#include <iostream>
#include <cmath>
#include <limits>
#include <tuple>


const std::vector<uint8_t> PWM::ADDR = {0x14, 0x15, 0x16};
std::array<uint16_t, 7> PWM::timerArr = {1,1,1,1,1,1,1};


PWM::PWM(std::string pinName, std::vector<uint8_t> address)
    : I2C(1, address.empty() ? ADDR : address)
{
    if (pinName.length() > 1) {
        channel = stoi(pinName.substr(1));
    } else if (pinName.length() == 1) {
        channel = stoi(pinName);
    } else {
        std::cout << "WM channel should be between [P0, P19] or [0,19]";
        return;
    }
    
    if (channel < 16) {
        timerIdx = channel/4;
    } else if (channel == 16 || channel == 17) {
        timerIdx = 4;
    } else if (channel == 18) {
        timerIdx = 5;
    } else if (channel == 19) {
        timerIdx = 6;
    }

    pulseWidth = 0;
    freqHz = 50;
    setFreq(freqHz);
}

void PWM::setFreq(double freq) {
    freqHz = freq;
    int st = sqrt(CLOCK/freqHz) - 5;
    if (st <= 0) st = 1;

    uint16_t bestPsc;
    uint16_t bestArr;
    double error = std::numeric_limits<double>::max();
    
    for (uint16_t psc=st; psc<st+10; psc++) {
        int arr = CLOCK/freqHz/psc;
        double accuracy = abs(freqHz-CLOCK/psc/arr);
        if (accuracy < error) {
            error = accuracy;
            bestArr = arr;
            bestPsc = psc;
        }
    }
    setPrescaler(bestPsc);
    setPeriod(bestArr);
}

void PWM::setPeriod(uint16_t arr) {
    timerArr[timerIdx] = round(arr);
    freqHz = CLOCK/prescaler/timerArr[timerIdx];
    
    uint8_t reg;
    if (timerIdx < 4) {
        reg = REG_ARR + timerIdx;
    } else {
        reg = REG_ARR2 + timerIdx - 4;
    }
    writeRegWord(reg, timerArr[timerIdx]);
}

void PWM::setPrescaler(uint16_t prescaler) {
    this->prescaler = round(prescaler);
    freqHz = CLOCK/this->prescaler/timerArr[timerIdx];
    
    uint8_t reg;
    if (timerIdx < 4) {
        reg = REG_PSC + timerIdx;
    } else {
        reg = REG_PSC2 + timerIdx - 4;
    }
    writeRegWord(reg, this->prescaler-1);
}


void PWM::setPulseWidth(uint16_t PulseWidth) {
    this->pulseWidth = PulseWidth;
    uint8_t reg = REG_CHN + channel;
    writeRegWord(reg, PulseWidth);
}


void PWM::setPulseWidthPercentage(uint8_t pulseWidthPercentage) {
    auto temp = pulseWidthPercentage / 100.0;
    uint16_t pulsewidth = temp * timerArr[timerIdx];
    setPulseWidth(pulsewidth);
}

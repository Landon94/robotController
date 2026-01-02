#include "include/PWM.hpp"
#include <iostream>
#include <cmath>
#include <limits>


PWM::PWM(std::string pinName, std::vector<uint8_t> address = {})
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
    freq();
}

void PWM::setFreq(double freq) {
    std::vector<std::tuple<>> resultAp[10];
    std::vector<uint16_t> resultAcc[10];

    int st = sqrt(CLOCK/freqHz);
    st -= 5;

    if (st <= 0) {
        st = 1;
    }

    int minIdx;
    int minPsc = std::numeric_limits<int>::max();
    
    for (int psc=st; psc<st+10; psc++) {
        int arr = CLOCK/freqHz/psc;
        resultAp->push_back(std::make_tuple(psc, arr));
        resultAcc->push_back(abs(freqHz-CLOCK/psc/arr));
        if (psc<minPsc) {
            minPsc = psc;
            minIdx = psc - st;
        }
    }
     i = result_acy.index(min(result_acy))
    i = min()
    int psc = resultAp[i][0];
    int arr = resultAp[i][1];
    setPrescaler(psc);
    setPeriod(arr);


}
    def freq(self, freq=None):
        """
        Set/get frequency, leave blank to get frequency

        :param freq: frequency(0-65535)(Hz)
        :type freq: float
        :return: frequency
        :rtype: float
        """
        if freq == None:
            return self._freq

        self._freq = int(freq)
        # [prescaler,arr] list
        result_ap = []
        # accuracy list
        result_acy = []
        # middle value for equal arr prescaler
        st = int(math.sqrt(self.CLOCK/self._freq))
        # get -5 value as start
        st -= 5
        # prevent negetive value
        if st <= 0:
            st = 1
        for psc in range(st, st+10):
            arr = int(self.CLOCK/self._freq/psc)
            result_ap.append([psc, arr])
            result_acy.append(abs(self._freq-self.CLOCK/psc/arr))
        i = result_acy.index(min(result_acy))
        psc = result_ap[i][0]
        arr = result_ap[i][1]
        self._debug(f"prescaler: {psc}, period: {arr}")
        self.prescaler(psc)
        self.period(arr);

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


void setPulseWidth(uint16_t PulseWidth);


void setPulseWidthPercentage(uint8_t pulseWidthPercentage);
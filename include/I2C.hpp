#ifndef I2C_H
#define I2C_H

#include <cstdint>
#include <vector>

class I2C {
    public:
        I2C(int bus, uint8_t address);
        I2C(int bus, const std::vector<uint8_t>& address);

        bool writeRegWord(uint8_t reg, uint16_t value);

        ~I2C();

    private:
        int fd;
        int bus;

        bool probe(uint8_t addr);
};

#endif
#include "include/I2C.hpp"
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <iostream>
#include <linux/i2c-dev.h>

I2C::I2C(int bus, uint8_t address)
    : bus(bus)
{
    std::string dev = "/dev/i2c-" + std::to_string(bus);
    fd = open(dev.c_str(), O_RDWR);

    if (fd < 0) {
        std::cout << "Failed to open I2C bus\n";
        return;
    }

    if (ioctl(fd, I2C_SLAVE, address) < 0) {
        std::cout << "Failed to set I2C bus\n";
        return;
    }
}

I2C::I2C(int bus, const std::vector<uint8_t>& address) 
    : bus(bus)
{
    std::string dev = "/dev/i2c-" + std::to_string(bus);
    fd = open(dev.c_str(), O_RDWR);

    if (fd < 0) {
        std::cout << "Failed to open I2C bus\n";
        return;
    }

    for (uint8_t addr: address) {
        if (ioctl(fd, I2C_SLAVE, addr) >= 0) {
            return;
        }
    }
    close(fd);
    std::cout << "Failed to set I2C bus\n";
    return;

}

I2C::~I2C() {
    if (fd >= 1) {
        close(fd);
    }
}

bool I2C::writeRegWord(uint8_t reg, uint16_t value) {
    uint8_t buffer[3];
    buffer[0] = reg;
    buffer[1] = value >> 8;
    buffer[2] = value & 0xFF;

    return write(fd, buffer, sizeof(buffer)) == sizeof(buffer);
}
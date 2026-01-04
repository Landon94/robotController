#include "include/Pin.hpp"
#include <stdexcept>

const std::unordered_map<std::string, int> Pin::pinMap = {
    {"D0", 17},
    {"D1", 4},
    {"D2", 27},
    {"D3", 22},
    {"D4", 23},
    {"D5", 24},
    {"D6", 25},
    {"D9", 6},
    {"D10", 12},
    {"D11", 13},
    {"D12", 19},
    {"D13", 16},
    {"D14", 26},
    {"D15", 20},
    {"D16", 21},
};

Pin::Pin(const std::string& name) {
    auto it = pinMap.find(name);
    if (it == pinMap.end()) {
        throw std::invalid_argument("Invalid pin name: " + name);
    }

    int gpio = it->second;

    chip = gpiod_chip_open_by_name("gpiochip0");
    if (!chip) {
        throw std::runtime_error("Failed to open gpiochip0");
    }

    line = gpiod_chip_get_line(chip, gpio);
    if (!line) {
        gpiod_chip_close(chip);
        throw std::runtime_error("Failed to get GPIO line");
    }

    if (gpiod_line_request_output(line, "picarx", 0) < 0) {
        gpiod_chip_close(chip);
        throw std::runtime_error("Failed to request GPIO as output");
    }
}

Pin::~Pin() {
    if (line) gpiod_line_release(line);
    if (chip) gpiod_chip_close(chip);
}

void Pin::high() {
    gpiod_line_set_value(line, 1);
}

void Pin::low() {
    gpiod_line_set_value(line, 0);
}

#ifndef PIN_H
#define PIN_H

#include <string>
#include <unordered_map>
#include <gpiod.h>

class Pin {
public:
    explicit Pin(const std::string& name);
    ~Pin();

    void high();
    void low();

private:
    static const std::unordered_map<std::string, int> pinMap;

    gpiod_chip* chip = nullptr;
    gpiod_line* line = nullptr;
};

#endif
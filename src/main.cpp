#include "include/Car.hpp"
#include <iostream>

int main() {
    Car car;

    char key;
    while (std::cin >> key) {
        if (key == 'q') {
            break;
        }
        car.handleKey(key);
    }

    car.stop();
    std::cout <<  "Car stopped";
    return 0;
}

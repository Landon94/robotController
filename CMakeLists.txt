cmake_minimum_required(VERSION 3.16)
project(car_project LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(car src/main.cpp src/Car.cpp src/Pin.cpp src/PWM.cpp src/Servo.cpp src/I2C.cpp)

target_include_directories(car PRIVATE .)
target_link_libraries(car PRIVATE gpiod)
#ifndef CAR_H
#define CAR_H

#include "include/Servo.hpp"
#include "include/PWM.hpp"
#include "include/Pin.hpp"

class Car {
    public:
    Car(std::array<std::string, 3> servoPins = {"P0","P1","P2"},
        std::array<std::string, 4> motorPins = {"D4","D5","P13","P12"},
        std::array<std::string, 2> ultrasonicPins = {"D2","D3"})
        void forward(int speed);
        void backward(int speed);
        void stop();

        handleKey(char key);
        void setDirServoAngle(float angle);

        // void setDirServoCalibration(float cal);
        // void setMotorDirectionCalibration(int left, int right);
        // void setMotorSpeedCalibration(int leftOffset, int rightOffset);

        const int8_t DIR_MIN = -30;
        const int8_t DIR_MAX = 30;

        // CAM_PAN_MIN = -90
        // CAM_PAN_MAX = 90
        // CAM_TILT_MIN = -35
        // CAM_TILT_MAX = 65

        const uint16_t PERIOD = 4095;
        const uint16_t PRESCALER = 10;
    private:
        void setMotorSpeed(uint8_t motor, int speed);

        Servo camPan;
        Servo camTilt;
        Servo dirServoPin;

        Pin leftRearDirPin;
        Pin rightRearDirPin;
        PWM leftRearPwmPin;
        PWM rightRearPwmPin;

        // Calibration/state
        float dirCaliVal = 0.0f;
        int   caliDirValue[2] = {1, 1};
        int   caliSpeedValue[2] = {0, 0};
        int   dirCurrentAngle = 0;
};

#endif
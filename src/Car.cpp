#include "include/Car.hpp"
#include <cmath>

Car::Car(std::array<std::string, 3> servoPins,
         std::array<std::string, 4> motorPins,
         std::array<std::string, 2> ultrasonicPins)
    : dirServoPin(servoPins[2]),
      leftRearDirPin(motorPins[0]),
      rightRearDirPin(motorPins[1]),
      leftRearPwmPin(motorPins[2]),
      rightRearPwmPin(motorPins[3])
{
    leftRearPwmPin.setPeriod(PERIOD);
    rightRearPwmPin.setPeriod(PERIOD);
    leftRearPwmPin.setPrescaler(PRESCALER);
    rightRearPwmPin.setPrescaler(PRESCALER);
}

void Car::setMotorSpeed(uint8_t motor, int speed) {
    if (speed > 100) speed = 100;
    if (speed < -100) speed = -100;
    motor -= 1;

    int direction = (speed >= 0 ? 1 : -1) * caliDirValue[motor];
    speed = std::abs(speed);
    if (speed != 0) speed = speed/2 + 50;

    speed = speed - caliSpeedValue[motor];

    Pin& dirPin = (motor == 0) ? leftRearDirPin : rightRearDirPin;
    PWM& pwmPin = (motor == 0) ? leftRearPwmPin : rightRearPwmPin;

    if (direction < 0) {
        dirPin.high();
        pwmPin.setPulseWidthPercentage(speed);
    } else {
        dirPin.high();
        pwmPin.setPulseWidthPercentage(speed);
    }

}

void Car::forward(int speed) {
    int currentAngle = dirCurrentAngle;
    if (currentAngle != 0) {
        int unsignedAngle = abs(currentAngle);
        if (unsignedAngle > DIR_MAX) unsignedAngle = DIR_MAX;
        int powerScale = (100 - unsignedAngle) / 100;
        if (currentAngle / unsignedAngle > 0) {
            setMotorSpeed(1, 1*speed * powerScale);
            setMotorSpeed(2, -speed);
        } else {
            setMotorSpeed(1, speed);
            setMotorSpeed(2, -1*speed* powerScale);
        }
    } else {
        setMotorSpeed(1, speed);
        setMotorSpeed(2, -1 * speed);
    }
}

void Car::backward(int speed) {
    int currentAngle = dirCurrentAngle;
    if (currentAngle != 0) {
        int unsignedAngle = abs(currentAngle);
        if (unsignedAngle > DIR_MAX) unsignedAngle = DIR_MAX;
        int powerScale = (100 - unsignedAngle) / 100;
        if (currentAngle / unsignedAngle > 0) {
            setMotorSpeed(1, -1*speed);
            setMotorSpeed(2, speed * powerScale);
        } else {
            setMotorSpeed(1, -1*speed*powerScale);
            setMotorSpeed(2, speed);
        }
    } else {
        setMotorSpeed(1, -1 * speed);
        setMotorSpeed(2, speed);
    }
}

void Car::stop() {
    for (int i=0;i<2;i++){
        leftRearPwmPin.setPulseWidthPercentage(0);
        rightRearPwmPin.setPulseWidthPercentage(0);
    }
}

void Car::steer(int angle) {
    if (angle < -90) angle = -90;
    if (angle > 90)  angle = 90;

    steerAngle = static_cast<int8_t>(angle);
    dirServoPin.angle(steerAngle);
}

void Car::handleKey(char key) {
    switch (key) {
        case 'w': case 'W': forward(driveSpeed); break;
        case 's': case 'S': backward(driveSpeed); break;
        case 'a': case 'A': steer(dirCurrentAngle - steerStep); break;
        case 'd': case 'D': steer(dirCurrentAngle + steerStep); break;
        case ' ': stop(); break;
        default: break;
    }
}
#include "motor.h"

Motor::Motor() {
    setSpeed(SPEED_MAX);
}

Motor::Motor(uint8_t speed) {
    setSpeed(speed);
}

Motor::Motor(uint8_t leftSpeed, uint8_t rightSpeed) {
    setSpeed(leftSpeed, rightSpeed);
}

uint8_t Motor::getLeftSpeed() const {
    return this->leftSpeed;
}

uint8_t Motor::getRightSpeed() const {
    return this->rightSpeed;
}

void Motor::setSpeed(uint8_t speed) {
    if (speed > SPEED_MAX)
        this->leftSpeed = this->rightSpeed = SPEED_MAX;
    else if (speed < SPEED_MIN)
        this->leftSpeed = this->rightSpeed = SPEED_MIN;
    else
        this->leftSpeed = this->rightSpeed = speed;
}

void Motor::setSpeed(uint8_t leftSpeed, uint8_t rightSpeed) {
    if (leftSpeed > SPEED_MAX)
        this->leftSpeed = SPEED_MAX;
    else if (leftSpeed < SPEED_MIN)
        this->leftSpeed = SPEED_MIN;
    else
        this->leftSpeed = leftSpeed;

    if (rightSpeed > SPEED_MAX)
        this->rightSpeed = SPEED_MAX;
    else if (rightSpeed < SPEED_MIN)
        this->rightSpeed = SPEED_MIN;
    else
        this->rightSpeed = rightSpeed;
}

void Motor::init() {
    pinMode(LEFT_MOTOR_FWD_PIN, OUTPUT);
    pinMode(LEFT_MOTOR_BWD_PIN, OUTPUT);
    pinMode(RIGHT_MOTOR_BWD_PIN, OUTPUT);
    pinMode(RIGHT_MOTOR_FWD_PIN, OUTPUT);

    pinMode(LEFT_SPEED_PIN, OUTPUT);
    pinMode(RIGHT_SPEED_PIN, OUTPUT);
}

void Motor::stop() const {
    setState(STATE[STATE_STOP]);
}

void Motor::forward() const {
    setState(STATE[STATE_FWD]);
}

void Motor::turnLeft() const {
    setState(STATE[STATE_LEFT]);
}

void Motor::turnRight() const {
    setState(STATE[STATE_RIGHT]);
}

void Motor::setState(unsigned char state) const {
    uint8_t divider = 1;
    switch (state & 0b00000011)
    {
    case 2:
        divider = 4;
        break;
    case 3:
        divider = 8;
        break;
    default:
        divider = 2;
        break;
    }


    uint8_t right_speed = (state & (1 << 2)) ? rightSpeed / divider : rightSpeed;
    uint8_t left_speed = (state & (1 << 3)) ? leftSpeed / divider : leftSpeed;
    analogWrite(RIGHT_SPEED_PIN, right_speed);
    analogWrite(LEFT_SPEED_PIN, left_speed);

    digitalWrite(RIGHT_MOTOR_FWD_PIN, (bool)(state & (1 << 4)));
    digitalWrite(RIGHT_MOTOR_BWD_PIN, (bool)(state & (1 << 5)));
    digitalWrite(LEFT_MOTOR_BWD_PIN, (bool)(state & (1 << 6)));
    digitalWrite(LEFT_MOTOR_FWD_PIN, (bool)(state & (1 << 7)));
}
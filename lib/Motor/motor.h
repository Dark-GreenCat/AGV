#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>

/* Corresponding ESP32 pin to L298N pin*/
#define IN1 27
#define IN2 26
#define IN3 25
#define IN4 33

#define ENA 15
#define ENB 4


/* Corresponding Motor function to L298N pin*/
#define LEFT_MOTOR_FWD_PIN      IN1
#define LEFT_MOTOR_BWD_PIN      IN2
#define RIGHT_MOTOR_FWD_PIN     IN4
#define RIGHT_MOTOR_BWD_PIN     IN3

#define LEFT_SPEED_PIN          ENA
#define RIGHT_SPEED_PIN         ENB


/* Set speed range */
#define SPEED_MIN   0
#define SPEED_MAX   255


/* State of motor */
/*
 *  Bit 7:      Left Motor Forward State
 *  Bit 6:      Left Motor Backward State
 *  Bit 5:      Right Motor Backward State
 *  Bit 4:      Right Motor Forward State
 *  Bit 3:      Left Motor Divider Enable State
 *  Bit 2:      Right Motor Divider Enable State
 *  Bit 1,0:    Motor Speed Divider Value
 */
#define STATE_STOP  0
#define STATE_FWD   1
#define STATE_LEFT  2
#define STATE_RIGHT 3

const unsigned char STATE[] = {
    0b00000000,       // stop
    0b10010000,       // forward
    0b00010000,       // turn left
    0b10000000        // turn right
};

class Motor {
private:
    uint8_t leftSpeed;
    uint8_t rightSpeed;
public:
    Motor();
    Motor(uint8_t speed);
    Motor(uint8_t leftSpeed, uint8_t rightSpeed);
    
    uint8_t getLeftSpeed() const;
    uint8_t getRightSpeed() const;
    void setSpeed(uint8_t Speed);
    void setSpeed(uint8_t leftSpeed, uint8_t rightSpeed);

    void init();
    
    void stop() const;
    void forward() const;
    void turnLeft() const;
    void turnRight() const;

    void setState(unsigned char state) const;
};

#endif
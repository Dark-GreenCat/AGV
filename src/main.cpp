#include "main.h"

Motor motor(SPEED_MAX / 3);

void setup() {
    motor.init();
}

void loop() {
    motor.forward();
    delay(1000);
    motor.turnLeft();
    delay(1000);
    motor.turnRight();
    delay(1000);
}

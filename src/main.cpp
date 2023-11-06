#include "main.h"

Motor motor(SPEED_MAX / 2);

void setup() {
    motor.init();
}

void loop() {
    motor.forward();
    delay(3000);
    motor.turnLeft();
    delay(3000);
    motor.turnRight();
    delay(3000);
}

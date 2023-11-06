#include "main.h"

Motor motor(SPEED_MAX / 2);
RemoteMotorControl remoteMotorControl(&motor);

void setup() {
    Serial.begin(115200);
    motor.init();
    remoteMotorControl.init();
    remoteMotorControl.begin();
}

void loop() {
    remoteMotorControl.handleClient();
}

#include "main.h"

Motor motor(SPEED_MAX / 2);
RemoteMotorControl remoteMotorControl(&motor);

void handleOn() {
    for(int i = 3; i > 0; i--) {
        digitalWrite(LED_BUILTIN, 1);
        delay(50);
        digitalWrite(LED_BUILTIN, 0);
        delay(50);
    }
}

void setup() {
    Serial.begin(115200);
    pinMode(LED_BUILTIN, OUTPUT);
    remoteMotorControl.init();

    remoteMotorControl.begin();
}

void loop() {
    remoteMotorControl.handleClient();
}

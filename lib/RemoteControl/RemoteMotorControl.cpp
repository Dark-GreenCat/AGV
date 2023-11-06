#include "RemoteMotorControl.h"

RemoteMotorControl::RemoteMotorControl(Motor* p_motor, uint8_t signalLed) : RemoteControl(p_motor) {
    this->signalLed = signalLed;
    this->p_motor = p_motor;
}

void RemoteMotorControl::init() {
    pinMode(signalLed, OUTPUT);

    this->p_motor->init();
    RemoteControl::init();

    setHandler();
}

void RemoteMotorControl::begin() {
    RemoteControl::begin();
}

void RemoteMotorControl::handleClient() {
    RemoteControl::handleClient();
}

void RemoteMotorControl::setHandler() {
    setRequestHandler(ON_CONNECT_REQ, [this]() { handleOnConnectRequest(); });
    setRequestHandler(FORWARD_REQ, [this]() { handleForwardRequest(); });
    setRequestHandler(TURN_LEFT_REQ, [this]() { handleTurnLeftRequest(); });
    setRequestHandler(TURN_RIGHT_REQ, [this]() { handleTurnRightRequest(); });
    setRequestHandler(STOP_REQ, [this]() { handleStopRequest(); });
}

void RemoteMotorControl::handleOnConnectRequest() {
    Serial.println("Receive request: On Connect");
    bool ledstate = false;

    int numberOfBlink = 3;
    while(numberOfBlink--) {
        digitalWrite(signalLed, HIGH);
        delay(50);
        digitalWrite(signalLed, LOW);
        delay(50);
    }
}

void RemoteMotorControl::handleForwardRequest() {
    Serial.println("Receive request: Forward");

    this->p_motor->forward();
}

void RemoteMotorControl::handleTurnLeftRequest() {
    Serial.println("Receive request: Turn Left");

    this->p_motor->turnLeft();
}

void RemoteMotorControl::handleTurnRightRequest() {
    Serial.println("Receive request: Turn Right");

    this->p_motor->turnRight();
}

void RemoteMotorControl::handleStopRequest() {
    Serial.println("Receive request: Stop");

    this->p_motor->stop();
}

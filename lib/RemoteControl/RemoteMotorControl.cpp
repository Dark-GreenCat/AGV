#include "RemoteMotorControl.h"

RemoteMotorControl::RemoteMotorControl(Motor* p_motor, uint8_t signalLed) {
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
    static uint32_t previousMillisOnConnectRequest;
    static bool ledState = false;

    int interval = 50;
    uint32_t currentMillis = millis();

    uint8_t numberOfSignal = 3;
    while (numberOfSignal--) {
        if (currentMillis - previousMillisOnConnectRequest > interval) {
            ledState = !ledState;
            digitalWrite(signalLed, ledState);
        }
    }
}

void RemoteMotorControl::handleForwardRequest() {
    this->p_motor->forward();
}

void RemoteMotorControl::handleTurnLeftRequest() {
    this->p_motor->turnLeft();
}

void RemoteMotorControl::handleTurnRightRequest() {
    this->p_motor->turnRight();
}

void RemoteMotorControl::handleStopRequest() {
    this->p_motor->stop();
}

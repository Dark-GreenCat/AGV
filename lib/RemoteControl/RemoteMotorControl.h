#ifndef REMOTECONTROLMOTOR_H
#define REMOTECONTROLMOTOR_H

#include "RemoteControl.h"

#define ON_CONNECT_REQ  "/"
#define FORWARD_REQ     "/motor/fwd"
#define TURN_LEFT_REQ   "/motor/turnleft"
#define TURN_RIGHT_REQ  "/motor/turnright"
#define STOP_REQ        "/motor/stop"

class RemoteMotorControl : public RemoteControl<Motor> {
private:
    uint8_t signalLed;
    Motor* p_motor;

protected:
    void setHandler();
    void handleOnConnectRequest();

    void handleForwardRequest();
    void handleTurnLeftRequest();
    void handleTurnRightRequest();
    void handleStopRequest();

public:
    RemoteMotorControl(Motor* p_motor, uint8_t signalLed = LED_BUILTIN);
    void init();

    void begin();
    void handleClient();
};

#endif
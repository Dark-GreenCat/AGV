#ifndef REMOTECONTROL_H
#define REMOTECONTROL_H

#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include "motor.h"

#define SSID        "MINTCAT"
#define PASSWORD    "mintcat3008"

#define PORT_HTTP   80

const uint8_t LOCAL_IP[] = { 192, 168, 137, 10 };
const uint8_t GATEWAY[] = { 192, 168, 1, 1 };
const uint8_t SUBNET[] = { 255, 255, 0, 0 };
const uint8_t PRIMARY_DNS[]{ 8, 8, 8, 8 };          // Optional
const uint8_t SECONDARY_DNS[]{ 8, 8, 4, 4 };        // Optional


class RemoteControl {
private:
    Motor* p_motor;

    const char* ssid;
    const char* password;
    WebServer server;
public:
    RemoteControl(Motor* p_motor);

    void connectWifi();
    void init();
    void begin();

    void setRequestHandler(String request, WebServer::THandlerFunction handler);
    void handleClient();
};

#endif
#ifndef REMOTECONTROL_H
#define REMOTECONTROL_H

#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include "motor.h"

#define SSID        "MINTCAT"
#define PASSWORD    "mintcat3008"

#define PORT_HTTP   80
#define STATIC_IP   "192.168.137.10"
#define GATEWAY     "192.168.1.1"
#define SUBNET      "255.255.0.0"

template <class Devices>
class RemoteControl {
private:
    Devices* p_devices;

    const char* ssid;
    const char* password;

    IPAddress local_IP;
    IPAddress gateway;
    IPAddress subnet;

    WebServer server;

public:
    RemoteControl();
    RemoteControl(Devices* p_devices);

    Devices* getDevicesPointer();

    void connectWifi();
    void init();
    void begin();

    void setRequestHandler(String request, WebServer::THandlerFunction handler);
    void handleClient();
};



template<class Devices>
RemoteControl<Devices>::RemoteControl() {
}

template<class Devices>
RemoteControl<Devices>::RemoteControl(Devices* p_devices) : p_devices(p_devices), ssid(SSID), password(PASSWORD), server(PORT_HTTP) {
    Serial.begin(115200);

    /* Set static IP */
    local_IP.fromString(STATIC_IP);
    gateway.fromString(GATEWAY);
    subnet.fromString(SUBNET);
}

template<class Devices>
Devices* RemoteControl<Devices>::getDevicesPointer() {
    return this->p_devices;
}

template<class Devices>
void RemoteControl<Devices>::connectWifi() {
    // Connect to Wi-Fi network with SSID and password
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    // Print local IP address and start web server
    Serial.println("");
    Serial.println("WiFi connected.");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}

template<class Devices>
void RemoteControl<Devices>::init() {
    Serial.println("Configure IP");
    // Configures static IP address
    if (!WiFi.config(local_IP, gateway, subnet)) {
        Serial.println("STA Failed to configure");
    }
    connectWifi();
}

template<class Devices>
void RemoteControl<Devices>::begin() {
    server.begin();
}

template<class Devices>
void RemoteControl<Devices>::setRequestHandler(const String request, WebServer::THandlerFunction handler) {
    server.on(request, handler);
}

template<class Devices>
void RemoteControl<Devices>::handleClient() {
    server.handleClient();
}

#endif
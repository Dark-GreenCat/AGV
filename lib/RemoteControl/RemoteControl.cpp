#include "RemoteControl.h"

RemoteControl::RemoteControl(Motor* p_motor) : ssid(SSID), password(PASSWORD), server(PORT_HTTP) {
    Serial.println("Constructor Remote!");
    p_motor->init();

    Serial.println("Setup static IP!");
    // Set your Static IP address
    IPAddress local_IP(LOCAL_IP[0], LOCAL_IP[1], LOCAL_IP[2], LOCAL_IP[3]);
    // Set your Gateway IP address
    IPAddress gateway(GATEWAY[0], GATEWAY[1], GATEWAY[2], GATEWAY[3]);

    IPAddress subnet(SUBNET[0], SUBNET[1], SUBNET[2], SUBNET[3]);
    IPAddress primaryDNS(PRIMARY_DNS[0], PRIMARY_DNS[1], PRIMARY_DNS[2], PRIMARY_DNS[3]);
    IPAddress secondaryDNS(SECONDARY_DNS[0], SECONDARY_DNS[1], PRIMARY_DNS[2], PRIMARY_DNS[3]);

    Serial.println("Configure IP");
    // Configures static IP address
    if (!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS)) {
        Serial.println("STA Failed to configure");
    }
}

void RemoteControl::connectWifi() {
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

void RemoteControl::init() {
    connectWifi();
}

void RemoteControl::begin() {
    server.begin();
}

void RemoteControl::setRequestHandler(const String request, WebServer::THandlerFunction handler) {
    server.on(request, handler);
}

void RemoteControl::handleClient() {
    server.handleClient();
}

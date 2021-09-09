#ifndef L_CONNECT_H
#define L_CONNECT_H

#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include "L_debug.h"
#include "L_connect.h"

const char* ssid = "v1114";
const char* password = "191371535219";
//const char* ssid = "v1114g";
//const char* password = "ganzeinfach";

unsigned long connectTimestemp;
#define conenctTimeout 20000

bool connectWifi() {
    if (WiFi.status() == WL_CONNECTED) {
        return true;
    }
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    WiFi.setAutoReconnect(true);
    // Wait for connection
    Debug("Wifi","Connect","Start");
    connectTimestemp = millis() + conenctTimeout;
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Debug("Wifi","Connect","Connecting");
        if ( millis() > connectTimestemp) {
            WiFi.reconnect();
            Debug("Wifi","Connect","Reconnect");
            connectTimestemp = millis() + conenctTimeout;
        }
    }
    
    Debug("Wifi","Connect","Connected");
    Debug("Wifi","Connected",WiFi.localIP().toString());
    return true;
}

#endif
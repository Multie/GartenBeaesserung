


#ifndef L_WEBSERVER_H
#define L_WEBSERVER_H

#define CONFIG_ASYNC_TCP_USE_WDT  0
#include <Arduino.h>
#include <WiFi.h>
#include "SPIFFS.h"
#include "ESPAsyncWebServer.h"

#include <ESPmDNS.h>
#include "L_debug.h"
#include "L_connect.h"





#define WebServer_VAR
AsyncWebServer server(80);
// Pages


void SetupWebserver() {
    

disableCore0WDT();
disableCore1WDT();
disableLoopWDT(); // You forgot this one !

      if(!SPIFFS.begin()){
        Serial.println("An Error has occurred while mounting SPIFFS");
        return;
  }
    
    connectWifi();

    if (MDNS.begin("garten")) {
        Debug("Webserver","MDNS","responder started");
    }

  /*server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
  
    request->send(SPIFFS, "/root.html", "text/html");
  });*/


  server.onNotFound([](AsyncWebServerRequest *request){
    request->send(404, "text/plain", "The content you are looking for was not found.");
  });
DefaultHeaders::Instance().addHeader("Access-Control-Allow-Origin", "*");
    server.begin();
    Debug("Webserver","Setup","complete");
}

void LoopWebserver() {

}

#endif
#ifndef L_WEBPAGE_H
#define L_WEBPAGE_H

#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <time.h>
#include "L_webpage_values.h"

#include <ESPmDNS.h>
#include "ESPAsyncWebServer.h"
#include "L_webserverRest.h"

#ifndef WebServer_VAR
AsyncWebServer server(80);
#endif


// Colum: content
String addhtmlColumn(String content) {
    String html = htmlColumn;
    html.replace("[[content]]",content);
    return html;
}
// Row: content
String addhtmlRow(String content) {
    String html = htmlRow;
    html.replace("[[content]]",content);
    return html;
}
// Text: text
String addhtmlText(String text) {
    String html = htmlText;
    html.replace("[[text]]",text);
    return html;
}
// Button: label, name, value
String addhtmlButton(String label,RestElement element) {
    String html = htmlButton;
    html.replace("[[label]]",label);
    html.replace("[[name]]",element.endpoint);
    html.replace("[[value]]", getRestValueString(element));
    return html;
}
// Link: label, link
String addhtmlLink(String label, String link) {
    String html = htmlLink;
    html.replace("[[label]]",label);
    html.replace("[[link]]",link);
    return html;
}
// Item: label, value
String addhtmlItem(String label, String value) {
    String html = htmlItem;
    html.replace("[[label]]",label);
    html.replace("[[value]]",value);
    return html;
}
// Item Value: label, value
String addhtmlItemValue(String label, String value) {
    String html = htmlItemValue;
    html.replace("[[label]]",label);
    html.replace("[[link]]",value);
    return html;
}
// Item Input Text: disabled, name, value
String addhtmlItemInputText(RestElement element,bool disabled=false) {
    String html = htmlItemInputText;
    html.replace("[[name]]",element.endpoint);
    html.replace("[[value]]", getRestValueString(element));
    if (disabled) {
        html.replace("[[disabled]]", "disabled");
    }
    else {
        html.replace("[[disabled]]", "");
    }
    return html;
}
// Item Input Number: disabled, name, value, min, max
String addhtmlItemInputNumber(RestElement element,bool disabled=false) {
    String html = htmlItemInputNumber;
    html.replace("[[name]]",element.endpoint);
    html.replace("[[value]]",getRestValueString(element));
    html.replace("[[min]]",String(element.min));
    html.replace("[[max]]",String(element.max));
    if (disabled) {
        html.replace("[[disabled]]", "disabled");
    }
    else {
        html.replace("[[disabled]]", "");
    }
    return html;
}
// Item Input Slider: disabled, name, value, min, max
String addhtmlItemInputSlider(RestElement element,bool disabled=false) {
    String html = htmlItemInputSlider;
    html.replace("[[name]]",element.endpoint);
    html.replace("[[value]]", getRestValueString(element));
    html.replace("[[min]]",String(element.min));
    html.replace("[[max]]",String(element.max));
    if (disabled) {
        html.replace("[[disabled]]", "disabled");
    }
    else {
        html.replace("[[disabled]]", "");
    }
     return html;
}
// Item Input Checkbox: disabled, name, value
String addhtmlItemInputCheckbox(RestElement element,bool disabled=false) {
    String html = htmlItemInputCheckbox;
    html.replace("[[name]]",element.endpoint);
    html.replace("[[value]]",getRestValueString(element));
    if (disabled) {
        html.replace("[[disabled]]", "disabled");
    }
    else {
        html.replace("[[disabled]]", "");
    }
    return html;
}
// Item Input Date: disabled, name, valueHour, valueMin, valueSec, valueDay, valueMon, valueYear
String addhtmlInputDate(RestElement element,bool disabled=false) {
    String html = htmlInputDate;
    tm time = (*((tm *)element.pointer));

    html.replace("[[name]]",element.endpoint);
    html.replace("[[valueHour]]",String(time.tm_hour));
    html.replace("[[valueMin]]",String(time.tm_min));
    html.replace("[[valueSec]]",String(time.tm_sec));

    html.replace("[[valueDay]]",String(time.tm_mday));
    html.replace("[[valueMon]]",String(time.tm_mon));
    html.replace("[[valueYear]]",String(time.tm_year));
    if (disabled) {
        html.replace("[[disabled]]", "disabled");
    }
    else {
        html.replace("[[disabled]]", "");
    }
    return html;
}
// Toast: name, value
String addhtmlToast(String name, String value) {
    String html = htmlToast;
    html.replace("[[name]]",name);
    html.replace("[[value]]", value);
    return html;
}
// Expandable label, content
String addhtmlExpandable(String label, String content) {
    String html = htmlExpandable;
    html.replace("[[label]]",label);
    html.replace("[[content]]", content);
    return html;
}
// Page: title
String startPage(String title) {
    String html = htmlPageStart;
    html.replace("[[title]]",title);
    return html;
}
String endPage() {
    return htmlPageEnd;
}

void handelRoot(AsyncWebServerRequest *request)
{
    AsyncResponseStream *response = request->beginResponseStream("text/html");
    response->print(startPage("Bewässerung"));

    String colums = "";
    colums += (addhtmlRow(addhtmlLink("Tank","/tank")+ addhtmlLink("Ventile","/ventile")));
    colums += (addhtmlRow(addhtmlLink("Bodenfeuchte","/bodenfeuchte")+ addhtmlLink("Config","/config")));
    response->print(addhtmlColumn(colums));



    response->print(endPage());
    request->send(response);
}

void handelConfig(AsyncWebServerRequest *request)
{
    AsyncResponseStream *response = request->beginResponseStream("text/html");
    response->print(startPage("Bewässerung - Config"));
    
    response->print(addhtmlText("Tank"));
    response->print(addhtmlItem("Pin",addhtmlItemInputNumber(getRestElementByEndpoint("config/Tank/Pin"),true)));
    response->print(addhtmlText("Bodenfeuchte"));
    String content = "";
    for (int a =0; a < 10;a++) {
        content = "";
        content += (addhtmlItem("Id",addhtmlItemInputNumber(getRestElementByEndpoint("config/Soil/"+String(a)+"/Id"))));
        content += (addhtmlItem("Min",addhtmlItemInputNumber(getRestElementByEndpoint("config/Soil/"+String(a)+"/Min"))));
        content += (addhtmlItem("Max",addhtmlItemInputNumber(getRestElementByEndpoint("config/Soil/"+String(a)+"/Max"))));
        content += (addhtmlItem("ActiveTime",addhtmlItemInputNumber(getRestElementByEndpoint("config/Soil/"+String(a)+"/ActiveTime"))));
        content += (addhtmlItem("InactiveTime",addhtmlItemInputNumber(getRestElementByEndpoint("config/Soil/"+String(a)+"/InactiveTime"))));
        response->print(addhtmlExpandable("Sensor " + String(a),content));
    }
    content = "";
    response->print(endPage());
    request->send(response);
}



void SetupWebpage()
{
    server.on("/script.min.js", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(SPIFFS, "/script.min.js", "application/javascript");
    });
    server.on("/styles.min.css", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(SPIFFS, "/styles.min.css", "text/css");
    });

    server.on("/", HTTP_GET, handelRoot);
    server.on("/config", HTTP_GET, handelConfig);
}

void LoopWebPage()
{
}

#endif
#ifndef L_DEBUG_H
#define L_DEBUG_H

#include <Arduino.h>

bool debug = false;
void Debug(String component, String name, String value) {
    Serial.print("C");
    Serial.print(xPortGetCoreID());
    Serial.print(":");
    Serial.print(component);
    Serial.print("-");
    Serial.print(name);
    Serial.print(":");
    Serial.println(value);
}

void SetupDebug() {
    Serial.begin(115200);
    Debug("Debug","Setup","complete");
}

void LoopDebug() {

}

#endif
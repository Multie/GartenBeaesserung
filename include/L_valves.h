
#ifndef VALVES_H
#define VALVES_H
#include <Arduino.h>
#include "L_debug.h"
#include "L_data.h"

void SetupValves() {
    for (int a = 0; a < ValvesCount;a++) {
        pinMode(irrigationConfig.Valves[a].Pin,OUTPUT);
        digitalWrite(irrigationConfig.Valves[a].Pin,irrigationConfig.Valves[a].InitialState);
    }
    Debug("Valves","Setup","complete");
}


void LoopValves() {
    for (int a = 0; a < ValvesCount;a++) {
        digitalWrite(irrigationConfig.Valves[a].Pin,irrigationConfig.Valves[a].Invert == currentIrrigationData.Valves[a].setState);
        currentIrrigationData.Valves[a].State = irrigationConfig.Valves[a].Invert == currentIrrigationData.Valves[a].setState;
    }
}


#endif
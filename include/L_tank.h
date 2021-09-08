#ifndef TANK_H
#define TANK_H

#include <Arduino.h>
#include "L_data.h"
#include "L_time.h"
#include "L_debug.h"

void readTank() {
    currentIrrigationData.Tank.AnalogValue = analogRead(irrigationConfig.Tank.Pin);
    currentIrrigationData.Tank.Height = ((double)currentIrrigationData.Tank.AnalogValue) * 0.000604;
    currentIrrigationData.Tank.Volume = currentIrrigationData.Tank.Height * 1.2;
    currentIrrigationData.Tank.Level = currentIrrigationData.Tank.Height / 2.35 * 100;
    
    copyTimeToTime(&currentIrrigationData.Time, &currentIrrigationData.Tank.nextMesurment);
    addTime(&currentIrrigationData.Tank.nextMesurment,0,5,0,0,0,0);
    
    //Debug("Tank","AnalogValue",String(currentIrrigationData.Tank.AnalogValue));
    //Debug("Tank","Height",String(currentIrrigationData.Tank.Height));
    //Debug("Tank","Volume",String(currentIrrigationData.Tank.Volume));
    //Debug("Tank","Level",String(currentIrrigationData.Tank.Level));
}

void SetupTank() {
    irrigationConfig.Tank.Pin = 34;
    Debug("Tank","Setup","complete");
}

void LoopTank() {
    
    if (isTimeGreatertime(&(currentIrrigationData.Time),&(currentIrrigationData.Tank.nextMesurment))) {
         readTank();
    }
   
}


#endif
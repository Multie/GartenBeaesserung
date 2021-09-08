#ifndef L_SOILHUMIDY_H
#define L_SOILHUMIDY_H

#include "L_time.h"
#include "L_data.h"


void SetupSoilhumidy() {

}
void LoopSoilhumidy() {
    for (int a=0; a <SoilHumidiySensors;a++) {
        if (isTimeGreatertime(&currentIrrigationData.Time,&currentIrrigationData.SoilHumidies[a].Timeout)) {
            currentIrrigationData.SoilHumidies[a].Status = -1;
            currentIrrigationData.SoilHumidies[a].Id = -1;
        }
        else {
            currentIrrigationData.SoilHumidies[a].Status = 1;
        }
    }
}

#endif
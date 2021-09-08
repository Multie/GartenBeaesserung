#ifndef L_CONTROLLER_H
#define L_CONTROLLER_H

#include <Arduino.h>
#include "L_data.h"
#include "L_debug.h"
#include "L_time.h"

int getSoilHumidy(ZoneConfig *config)
{
    int humid = 0;
    for (int a = 0; a < ZoneSoilHumidyCounts; a++)
    {
        for (int b = 0; b < SoilHumidiySensors; b++)
        {
            if (config->SoilhumidiesId[a] == currentIrrigationData.SoilHumidies[b].Id)
            {
                if (currentIrrigationData.SoilHumidies[a].Status < 0)
                {
                    return -1;
                }
                humid += currentIrrigationData.SoilHumidies[a].SoilHumidiy;
            }
        }
    }
    return humid / ZoneSoilHumidyCounts;
}

void ControlZone(ZoneConfig *config, ZoneData *data)
{
    bool start = isTimeGreatertime(&currentIrrigationData.Time, &(config->StartTime));
    bool end = isTimeGreatertime(&currentIrrigationData.Time, &(config->StopTime));
    bool result = false;
    int humid = -1;
    if ((start && !end) || data->startNow)
    { // Time is between start and end
        // Ist im bereich
        humid = getSoilHumidy(config);
        data->Status = 1;
        if (humid > 0 && humid < config->StartSoilHumidy)
        { // Soil is dry
            result = true;
            data->Status = 2;
        }
    }
    if (!start || end)
    { // Time is outside start and end
        result = false;
        data->Status = -1;

        if (humid == -1)
        {
            result = false;
            data->Status = -10;
        }
        else if (humid > 0 && humid > config->StopSoilHumidy)
        { // Soil is wet
            result = false;
            data->Status = -2;
        }
        else if (currentIrrigationData.Tank.Level < config->StopTankLevel)
        { // Tank is empty
            data->Status = -3;
            result = false;
        }
        ///////////////////////////////////////
        if (result && !data->Active)
        { // get active
            data->startVolume = currentIrrigationData.Tank.Volume;
            data->StartSoilHumidy = humid;
        }
        if (!result && data->Active)
        { // get inactive
            data->endVolume = currentIrrigationData.Tank.Volume;
            data->EndSoilHumidy = humid;
        }
        for (int a = 0; a < ZoneValvesCounts; a++)
        {
            if (config->Valves[a] > 0)
            {
                currentIrrigationData.Valves[config->Valves[a]].setState = result;
            }
        }
    }
}

void SetupController()
{
}

void LoopController()
{
}

#endif
#ifndef DATA_H
#define DATA_H

#include <Arduino.h>
#include "time.h"
#include <EEPROM.h>
#define ValvesCount 9
#define SoilHumidiySensors 10
#define ZoneCounts 5
#define ZoneValvesCounts 4
#define ZoneSoilHumidyCounts 4
/////////////////////////////////////////
// Data
struct ZoneData {
    bool Active=false;
    bool startNow=false;
    double startVolume;
    double endVolume;
    int StartSoilHumidy;
    int EndSoilHumidy;
    int Status = 0;
};
struct SoilHumidyData {
    tm Timeout;
    int Id=-1;
    int SoilHumidiy;
    int Status;
};
struct ValveData {
    bool setState;
    bool State;
};
struct TankData {
    tm nextMesurment;
    int AnalogValue;
    double Level; // %
    double Volume; // m³
    double Height; // m
};
struct IrrigationData {
    tm Time;
    SoilHumidyData SoilHumidies[SoilHumidiySensors];
    ValveData Valves[ValvesCount];
    TankData Tank;
    ZoneData Zones[ZoneCounts];
    tm nextTimeSync;
    bool storeConfig=false;
};
/////////////////////////////////////////
// Config
struct ZoneConfig {
    int Valves[ZoneValvesCounts];
    int SoilhumidiesId[ZoneSoilHumidyCounts];
    // Start Condition
    tm StartTime;
    int StartSoilHumidy;
    // Pause Settings
    tm SprayDuration;
    tm SoakDuration;
    // Stop Conditons
    int StopSoilHumidy;
    tm StopTime;
    int StopTankLevel;
};
struct SoilHumidyConfig {
    int Id;
    int Min;
    int Max;
    int ActiveTime;
    int InactiveTime;
};
struct ValveConfig {
    int Pin;
    bool InitialState=0;
    bool Invert=0;
};
struct TankConfig {
    char Pin = 34;
};
struct IrrigationConfig {
    TankConfig Tank;
    SoilHumidyConfig SoilHumidies[SoilHumidiySensors];
    ValveConfig Valves[ValvesCount];
    ZoneConfig Zones[ZoneCounts];
};

IrrigationData currentIrrigationData;
IrrigationConfig irrigationConfig;

EEPROMClass EEPROM_config("eeprom0", sizeof(irrigationConfig));

void LoadConfig() {
    if (EEPROM_config.begin(EEPROM_config.length())) {
        EEPROM_config.get(0, irrigationConfig);

        irrigationConfig.Tank.Pin = 34;
        irrigationConfig.Valves[0].Pin = 4;
        irrigationConfig.Valves[1].Pin = 5;
        irrigationConfig.Valves[2].Pin = 6;
        irrigationConfig.Valves[3].Pin = 7;
        irrigationConfig.Valves[4].Pin = 8;
        irrigationConfig.Valves[5].Pin = 9;
        irrigationConfig.Valves[6].Pin = 10;
        irrigationConfig.Valves[7].Pin = 15;
        irrigationConfig.Valves[8].Pin = 24;

        EEPROM_config.end();
    }
}

void StoreConfig() {
    if (EEPROM_config.begin(EEPROM_config.length())) {
                  irrigationConfig.Tank.Pin = 34;
        irrigationConfig.Valves[0].Pin = 4;
        irrigationConfig.Valves[1].Pin = 5;
        irrigationConfig.Valves[2].Pin = 6;
        irrigationConfig.Valves[3].Pin = 7;
        irrigationConfig.Valves[4].Pin = 8;
        irrigationConfig.Valves[5].Pin = 9;
        irrigationConfig.Valves[6].Pin = 10;
        irrigationConfig.Valves[7].Pin = 15;
        irrigationConfig.Valves[8].Pin = 24;
          
            EEPROM_config.put(0, irrigationConfig);
            EEPROM_config.end();
    }
}

void SetupData() {
   StoreConfig();
    LoadConfig();
    
}

void LoopData() {
    if (currentIrrigationData.storeConfig) {
        currentIrrigationData.storeConfig = false;
        StoreConfig();
    }
}

#endif
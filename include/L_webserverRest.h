#ifndef L_WEBSERVERREST_H
#define L_WEBSERVERREST_H

#include <Arduino.h>
#include <WiFi.h>

#include <ESPmDNS.h>
#include "ESPAsyncWebServer.h"
#include "L_debug.h"
#include "L_connect.h"
#include "L_data.h"
#include "L_time.h"



enum RestType
{
    RestNull = -1,
    RestBool = 1,
    RestByte = 2,
    RestChar = 3,
    RestDouble = 4,
    RestFloat = 5,
    RestInt = 6,
    RestLong = 7,
    RestShort = 8,
    RestUnsignedChar = 9,
    RestUnsignedInt = 10,
    RestUnsignedLong = 11,
    RestWord = 12,
    RestLongLong = 13,
    RestCharArray = 14,
    RestTm = 16
};

// Vars
struct RestElement
{
    String endpoint;
    unsigned int pointer;
    RestType type;
    bool readOnly;
    double min;
    double max;
};

#ifndef WebServer_VAR
AsyncWebServer server(80);
#endif

#define RestAnalogMax 4096
#define TankLevelMax 100
#define TankVolumeMax 3000
#define TankHeightMax 3
#define SoilHumidiesIdMin -1
#define SoilHumidiesIdMax 100
#define SoilHumidiesStateMin 0
#define SoilHumidiesStateMax 100
#define SoilHumidiesStatusMin -10
#define SoilHumidiesStatusMax 10
#define PinMin 0
#define PinMax 50
int RestElementsLength = 218;
RestElement RestElements[] = {
    // Tank
    /* 0*/ {"tank/nextMesurment", (unsigned  int)&currentIrrigationData.Tank.nextMesurment, RestTm, false},
    /* 1*/ {"tank/analogvalue", (unsigned  int)&currentIrrigationData.Tank.AnalogValue, RestInt, true,0,RestAnalogMax},
    /* 2*/ {"tank/level", (unsigned  int)&currentIrrigationData.Tank.Level, RestDouble, true,0,TankLevelMax},
    /* 3*/ {"tank/volume", (unsigned  int)&currentIrrigationData.Tank.Volume, RestDouble, true,0,TankVolumeMax},
    /* 4*/ {"tank/height", (unsigned  int)&currentIrrigationData.Tank.Height, RestDouble, true,0,TankHeightMax},
    // SoilHumidy
    /* 5*/ {"Soil/0/Timeout", (unsigned  int)&currentIrrigationData.SoilHumidies[0].Timeout, RestTm, true},
    /* 6*/ {"Soil/0/Id", (unsigned  int)&currentIrrigationData.SoilHumidies[0].Id, RestInt, false,SoilHumidiesIdMin,SoilHumidiesIdMax},
    /* 7*/ {"Soil/0/SoilHumidiy", (unsigned  int)&currentIrrigationData.SoilHumidies[0].SoilHumidiy, RestInt, false,SoilHumidiesStateMin,SoilHumidiesStateMax},
    /* 8*/ {"Soil/0/Status", (unsigned  int)&currentIrrigationData.SoilHumidies[0].Status, RestInt, true,SoilHumidiesStatusMin,SoilHumidiesStatusMax},

    /* 9*/ {"Soil/1/Timeout", (unsigned  int)&currentIrrigationData.SoilHumidies[1].Timeout, RestTm, true},
    /*10*/ {"Soil/1/Id", (unsigned  int)&currentIrrigationData.SoilHumidies[1].Id, RestInt, false,SoilHumidiesIdMin,SoilHumidiesIdMax},
    /*11*/ {"Soil/1/SoilHumidiy", (unsigned  int)&currentIrrigationData.SoilHumidies[1].SoilHumidiy, RestInt, false,SoilHumidiesStateMin,SoilHumidiesStateMax},
    /*12*/ {"Soil/1/Status", (unsigned  int)&currentIrrigationData.SoilHumidies[1].Status, RestInt, true,SoilHumidiesStatusMin,SoilHumidiesStatusMax},

    /*13*/ {"Soil/2/Timeout", (unsigned  int)&currentIrrigationData.SoilHumidies[2].Timeout, RestTm, true},
    /*14*/ {"Soil/2/Id", (unsigned  int)&currentIrrigationData.SoilHumidies[2].Id, RestInt, false,SoilHumidiesIdMin,SoilHumidiesIdMax},
    /*15*/ {"Soil/2/SoilHumidiy", (unsigned  int)&currentIrrigationData.SoilHumidies[2].SoilHumidiy, RestInt, false,SoilHumidiesStateMin,SoilHumidiesStateMax},
    /*16*/ {"Soil/2/Status", (unsigned  int)&currentIrrigationData.SoilHumidies[2].Status, RestInt, true,SoilHumidiesStatusMin,SoilHumidiesStatusMax},

    /*17*/ {"Soil/3/Timeout", (unsigned  int)&currentIrrigationData.SoilHumidies[3].Timeout, RestTm, true},
    /*18*/ {"Soil/3/Id", (unsigned  int)&currentIrrigationData.SoilHumidies[3].Id, RestInt, false,SoilHumidiesIdMin,SoilHumidiesIdMax},
    /*19*/ {"Soil/3/SoilHumidiy", (unsigned  int)&currentIrrigationData.SoilHumidies[3].SoilHumidiy, RestInt, false,SoilHumidiesStateMin,SoilHumidiesStateMax},
    /*20*/ {"Soil/3/Status", (unsigned  int)&currentIrrigationData.SoilHumidies[3].Status, RestInt, true,SoilHumidiesStatusMin,SoilHumidiesStatusMax},

    /*21*/ {"Soil/4/Timeout", (unsigned  int)&currentIrrigationData.SoilHumidies[4].Timeout, RestTm, true},
    /*22*/ {"Soil/4/Id", (unsigned  int)&currentIrrigationData.SoilHumidies[4].Id, RestInt, false,SoilHumidiesIdMin,SoilHumidiesIdMax},
    /*23*/ {"Soil/4/SoilHumidiy", (unsigned  int)&currentIrrigationData.SoilHumidies[4].SoilHumidiy, RestInt, false,SoilHumidiesStateMin,SoilHumidiesStateMax},
    /*24*/ {"Soil/4/Status", (unsigned  int)&currentIrrigationData.SoilHumidies[4].Status, RestInt, true,SoilHumidiesStatusMin,SoilHumidiesStatusMax},

    /*25*/ {"Soil/5/Timeout", (unsigned  int)&currentIrrigationData.SoilHumidies[5].Timeout, RestTm, true},
    /*26*/ {"Soil/5/Id", (unsigned  int)&currentIrrigationData.SoilHumidies[5].Id, RestInt, false,SoilHumidiesIdMin,SoilHumidiesIdMax},
    /*27*/ {"Soil/5/SoilHumidiy", (unsigned  int)&currentIrrigationData.SoilHumidies[5].SoilHumidiy, RestInt, false,SoilHumidiesStateMin,SoilHumidiesStateMax},
    /*28*/ {"Soil/5/Status", (unsigned  int)&currentIrrigationData.SoilHumidies[5].Status, RestInt, true,SoilHumidiesStatusMin,SoilHumidiesStatusMax},

    /*29*/ {"Soil/6/Timeout", (unsigned  int)&currentIrrigationData.SoilHumidies[6].Timeout, RestTm, true},
    /*30*/ {"Soil/6/Id", (unsigned  int)&currentIrrigationData.SoilHumidies[6].Id, RestInt, false,SoilHumidiesIdMin,SoilHumidiesIdMax},
    /*31*/ {"Soil/6/SoilHumidiy", (unsigned  int)&currentIrrigationData.SoilHumidies[6].SoilHumidiy, RestInt, false,SoilHumidiesStateMin,SoilHumidiesStateMax},
    /*32*/ {"Soil/6/Status", (unsigned  int)&currentIrrigationData.SoilHumidies[6].Status, RestInt, true,SoilHumidiesStatusMin,SoilHumidiesStatusMax},

    /*33*/ {"Soil/7/Timeout", (unsigned  int)&currentIrrigationData.SoilHumidies[7].Timeout, RestTm, true},
    /*34*/ {"Soil/7/Id", (unsigned  int)&currentIrrigationData.SoilHumidies[7].Id, RestInt, false,SoilHumidiesIdMin,SoilHumidiesIdMax},
    /*35*/ {"Soil/7/SoilHumidiy", (unsigned  int)&currentIrrigationData.SoilHumidies[7].SoilHumidiy, RestInt, false,SoilHumidiesStateMin,SoilHumidiesStateMax},
    /*36*/ {"Soil/7/Status", (unsigned  int)&currentIrrigationData.SoilHumidies[7].Status, RestInt, true,SoilHumidiesStatusMin,SoilHumidiesStatusMax},

    /*37*/ {"Soil/8/Timeout", (unsigned  int)&currentIrrigationData.SoilHumidies[8].Timeout, RestTm, true},
    /*38*/ {"Soil/8/Id", (unsigned  int)&currentIrrigationData.SoilHumidies[8].Id, RestInt, false,SoilHumidiesIdMin,SoilHumidiesIdMax},
    /*39*/ {"Soil/8/SoilHumidiy", (unsigned  int)&currentIrrigationData.SoilHumidies[8].SoilHumidiy, RestInt, false,SoilHumidiesStateMin,SoilHumidiesStateMax},
    /*40*/ {"Soil/8/Status", (unsigned  int)&currentIrrigationData.SoilHumidies[8].Status, RestInt, true,SoilHumidiesStatusMin,SoilHumidiesStatusMax},

    /*41*/ {"Soil/9/Timeout", (unsigned  int)&currentIrrigationData.SoilHumidies[9].Timeout, RestTm, true},
    /*42*/ {"Soil/9/Id", (unsigned  int)&currentIrrigationData.SoilHumidies[9].Id, RestInt, false,SoilHumidiesIdMin,SoilHumidiesIdMax},
    /*43*/ {"Soil/9/SoilHumidiy", (unsigned  int)&currentIrrigationData.SoilHumidies[9].SoilHumidiy, RestInt, false,SoilHumidiesStateMin,SoilHumidiesStateMax},
    /*44*/ {"Soil/9/Status", (unsigned  int)&currentIrrigationData.SoilHumidies[9].Status, RestInt, true,SoilHumidiesStatusMin,SoilHumidiesStatusMax},

    // Valves
    /*45*/ {"Valves/0/setstate", (unsigned  int)&currentIrrigationData.Valves[0].setState, RestBool, false,0,1},
    /*46*/ {"Valves/0/state", (unsigned  int)&currentIrrigationData.Valves[0].State, RestBool, true,0,1},
    /*47*/ {"Valves/1/setstate", (unsigned  int)&currentIrrigationData.Valves[1].setState, RestBool, false,0,1},
    /*48*/ {"Valves/1/state", (unsigned  int)&currentIrrigationData.Valves[1].State, RestBool, true,0,1},
    /*49*/ {"Valves/2/setstate", (unsigned  int)&currentIrrigationData.Valves[2].setState, RestBool, false,0,1},
    /*50*/ {"Valves/2/state", (unsigned  int)&currentIrrigationData.Valves[2].State, RestBool, true,0,1},
    /*51*/ {"Valves/3/setstate", (unsigned  int)&currentIrrigationData.Valves[3].setState, RestBool, false,0,1},
    /*52*/ {"Valves/3/state", (unsigned  int)&currentIrrigationData.Valves[3].State, RestBool, true,0,1},
    /*53*/ {"Valves/4/setstate", (unsigned  int)&currentIrrigationData.Valves[4].setState, RestBool, false,0,1},
    /*54*/ {"Valves/4/state", (unsigned  int)&currentIrrigationData.Valves[4].State, RestBool, true,0,1},
    /*55*/ {"Valves/5/setstate", (unsigned  int)&currentIrrigationData.Valves[5].setState, RestBool, false,0,1},
    /*56*/ {"Valves/5/state", (unsigned  int)&currentIrrigationData.Valves[5].State, RestBool, true,0,1},
    /*57*/ {"Valves/6/setstate", (unsigned  int)&currentIrrigationData.Valves[6].setState, RestBool, false,0,1},
    /*58*/ {"Valves/6/state", (unsigned  int)&currentIrrigationData.Valves[6].State, RestBool, true,0,1},
    /*59*/ {"Valves/7/setstate", (unsigned  int)&currentIrrigationData.Valves[7].setState, RestBool, false,0,1},
    /*60*/ {"Valves/7/state", (unsigned  int)&currentIrrigationData.Valves[7].State, RestBool, true,0,1},
    /*61*/ {"Valves/8/setstate", (unsigned  int)&currentIrrigationData.Valves[8].setState, RestBool, false,0,1},
    /*62*/ {"Valves/8/state", (unsigned  int)&currentIrrigationData.Valves[8].State, RestBool, true,0,1},
    /*63*/ {"nextTimeSync", (unsigned  int)&currentIrrigationData.nextTimeSync, RestTm, true},
    /*65*/ {"Time", (unsigned  int)&currentIrrigationData.Time, RestTm, true},
    // Config
    // Tank
    {"config/Tank/Pin", (unsigned  int)&irrigationConfig.Tank.Pin, RestInt, true,PinMin,PinMax},
    //Soil
    {"config/Soil/0/Id", (unsigned  int)&irrigationConfig.SoilHumidies[0].Id, RestInt, false,SoilHumidiesIdMin,SoilHumidiesIdMax},
    {"config/Soil/1/Id", (unsigned  int)&irrigationConfig.SoilHumidies[1].Id, RestInt, false,SoilHumidiesIdMin,SoilHumidiesIdMax},
    {"config/Soil/2/Id", (unsigned  int)&irrigationConfig.SoilHumidies[2].Id, RestInt, false,SoilHumidiesIdMin,SoilHumidiesIdMax},
    {"config/Soil/3/Id", (unsigned  int)&irrigationConfig.SoilHumidies[3].Id, RestInt, false,SoilHumidiesIdMin,SoilHumidiesIdMax},
    {"config/Soil/4/Id", (unsigned  int)&irrigationConfig.SoilHumidies[4].Id, RestInt, false,SoilHumidiesIdMin,SoilHumidiesIdMax},
    {"config/Soil/5/Id", (unsigned  int)&irrigationConfig.SoilHumidies[5].Id, RestInt, false,SoilHumidiesIdMin,SoilHumidiesIdMax},
    {"config/Soil/6/Id", (unsigned  int)&irrigationConfig.SoilHumidies[6].Id, RestInt, false,SoilHumidiesIdMin,SoilHumidiesIdMax},
    {"config/Soil/7/Id", (unsigned  int)&irrigationConfig.SoilHumidies[7].Id, RestInt, false,SoilHumidiesIdMin,SoilHumidiesIdMax},
    {"config/Soil/8/Id", (unsigned  int)&irrigationConfig.SoilHumidies[8].Id, RestInt, false,SoilHumidiesIdMin,SoilHumidiesIdMax},
    {"config/Soil/9/Id", (unsigned  int)&irrigationConfig.SoilHumidies[9].Id, RestInt, false,SoilHumidiesIdMin,SoilHumidiesIdMax},

    {"config/Soil/0/Min", (unsigned  int)&irrigationConfig.SoilHumidies[0].Min, RestInt, false,0,RestAnalogMax},
    {"config/Soil/1/Min", (unsigned  int)&irrigationConfig.SoilHumidies[1].Min, RestInt, false,0,RestAnalogMax},
    {"config/Soil/2/Min", (unsigned  int)&irrigationConfig.SoilHumidies[2].Min, RestInt, false,0,RestAnalogMax},
    {"config/Soil/3/Min", (unsigned  int)&irrigationConfig.SoilHumidies[3].Min, RestInt, false,0,RestAnalogMax},
    {"config/Soil/4/Min", (unsigned  int)&irrigationConfig.SoilHumidies[4].Min, RestInt, false,0,RestAnalogMax},
    {"config/Soil/5/Min", (unsigned  int)&irrigationConfig.SoilHumidies[5].Min, RestInt, false,0,RestAnalogMax},
    {"config/Soil/6/Min", (unsigned  int)&irrigationConfig.SoilHumidies[6].Min, RestInt, false,0,RestAnalogMax},
    {"config/Soil/7/Min", (unsigned  int)&irrigationConfig.SoilHumidies[7].Min, RestInt, false,0,RestAnalogMax},
    {"config/Soil/8/Min", (unsigned  int)&irrigationConfig.SoilHumidies[8].Min, RestInt, false,0,RestAnalogMax},
    {"config/Soil/9/Min", (unsigned  int)&irrigationConfig.SoilHumidies[9].Min, RestInt, false,0,RestAnalogMax},

    {"config/Soil/0/Max", (unsigned  int)&irrigationConfig.SoilHumidies[0].Max, RestInt, false,0,RestAnalogMax},
    {"config/Soil/1/Max", (unsigned  int)&irrigationConfig.SoilHumidies[1].Max, RestInt, false,0,RestAnalogMax},
    {"config/Soil/2/Max", (unsigned  int)&irrigationConfig.SoilHumidies[2].Max, RestInt, false,0,RestAnalogMax},
    {"config/Soil/3/Max", (unsigned  int)&irrigationConfig.SoilHumidies[3].Max, RestInt, false,0,RestAnalogMax},
    {"config/Soil/4/Max", (unsigned  int)&irrigationConfig.SoilHumidies[4].Max, RestInt, false,0,RestAnalogMax},
    {"config/Soil/5/Max", (unsigned  int)&irrigationConfig.SoilHumidies[5].Max, RestInt, false,0,RestAnalogMax},
    {"config/Soil/6/Max", (unsigned  int)&irrigationConfig.SoilHumidies[6].Max, RestInt, false,0,RestAnalogMax},
    {"config/Soil/7/Max", (unsigned  int)&irrigationConfig.SoilHumidies[7].Max, RestInt, false,0,RestAnalogMax},
    {"config/Soil/8/Max", (unsigned  int)&irrigationConfig.SoilHumidies[8].Max, RestInt, false,0,RestAnalogMax},
    {"config/Soil/9/Max", (unsigned  int)&irrigationConfig.SoilHumidies[9].Max, RestInt, false,0,RestAnalogMax},

    {"config/Soil/0/ActiveTime", (unsigned  int)&irrigationConfig.SoilHumidies[0].ActiveTime, RestInt, false,1,180},
    {"config/Soil/1/ActiveTime", (unsigned  int)&irrigationConfig.SoilHumidies[1].ActiveTime, RestInt, false,1,180},
    {"config/Soil/2/ActiveTime", (unsigned  int)&irrigationConfig.SoilHumidies[2].ActiveTime, RestInt, false,1,180},
    {"config/Soil/3/ActiveTime", (unsigned  int)&irrigationConfig.SoilHumidies[3].ActiveTime, RestInt, false,1,180},
    {"config/Soil/4/ActiveTime", (unsigned  int)&irrigationConfig.SoilHumidies[4].ActiveTime, RestInt, false,1,180},
    {"config/Soil/5/ActiveTime", (unsigned  int)&irrigationConfig.SoilHumidies[5].ActiveTime, RestInt, false,1,180},
    {"config/Soil/6/ActiveTime", (unsigned  int)&irrigationConfig.SoilHumidies[6].ActiveTime, RestInt, false,1,180},
    {"config/Soil/7/ActiveTime", (unsigned  int)&irrigationConfig.SoilHumidies[7].ActiveTime, RestInt, false,1,180},
    {"config/Soil/8/ActiveTime", (unsigned  int)&irrigationConfig.SoilHumidies[8].ActiveTime, RestInt, false,1,180},
    {"config/Soil/9/ActiveTime", (unsigned  int)&irrigationConfig.SoilHumidies[9].ActiveTime, RestInt, false,1,180},

    {"config/Soil/0/InactiveTime", (unsigned  int)&irrigationConfig.SoilHumidies[0].InactiveTime, RestInt, false,1,180},
    {"config/Soil/1/InactiveTime", (unsigned  int)&irrigationConfig.SoilHumidies[1].InactiveTime, RestInt, false,1,180},
    {"config/Soil/2/InactiveTime", (unsigned  int)&irrigationConfig.SoilHumidies[2].InactiveTime, RestInt, false,1,180},
    {"config/Soil/3/InactiveTime", (unsigned  int)&irrigationConfig.SoilHumidies[3].InactiveTime, RestInt, false,1,180},
    {"config/Soil/4/InactiveTime", (unsigned  int)&irrigationConfig.SoilHumidies[4].InactiveTime, RestInt, false,1,180},
    {"config/Soil/5/InactiveTime", (unsigned  int)&irrigationConfig.SoilHumidies[5].InactiveTime, RestInt, false,1,180},
    {"config/Soil/6/InactiveTime", (unsigned  int)&irrigationConfig.SoilHumidies[6].InactiveTime, RestInt, false,1,180},
    {"config/Soil/7/InactiveTime", (unsigned  int)&irrigationConfig.SoilHumidies[7].InactiveTime, RestInt, false,1,180},
    {"config/Soil/8/InactiveTime", (unsigned  int)&irrigationConfig.SoilHumidies[8].InactiveTime, RestInt, false,1,180},
    {"config/Soil/9/InactiveTime", (unsigned  int)&irrigationConfig.SoilHumidies[9].InactiveTime, RestInt, false,1,180},
    // Valves
    {"config/Valves/0/Pin", (unsigned  int)&irrigationConfig.Valves[0].Pin, RestInt, true,PinMin,PinMax},
    {"config/Valves/1/Pin", (unsigned  int)&irrigationConfig.Valves[1].Pin, RestInt, true,PinMin,PinMax},
    {"config/Valves/2/Pin", (unsigned  int)&irrigationConfig.Valves[2].Pin, RestInt, true,PinMin,PinMax},
    {"config/Valves/3/Pin", (unsigned  int)&irrigationConfig.Valves[3].Pin, RestInt, true,PinMin,PinMax},
    {"config/Valves/4/Pin", (unsigned  int)&irrigationConfig.Valves[4].Pin, RestInt, true,PinMin,PinMax},
    {"config/Valves/5/Pin", (unsigned  int)&irrigationConfig.Valves[5].Pin, RestInt, true,PinMin,PinMax},
    {"config/Valves/6/Pin", (unsigned  int)&irrigationConfig.Valves[6].Pin, RestInt, true,PinMin,PinMax},
    {"config/Valves/7/Pin", (unsigned  int)&irrigationConfig.Valves[7].Pin, RestInt, true,PinMin,PinMax},
    {"config/Valves/8/Pin", (unsigned  int)&irrigationConfig.Valves[8].Pin, RestInt, true,PinMin,PinMax},

    {"config/Valves/0/Init", (unsigned  int)&(irrigationConfig.Valves[0].InitialState), RestBool, false, 0, 1},
    {"config/Valves/1/Init", (unsigned  int)&(irrigationConfig.Valves[1].InitialState), RestBool, false, 0, 1},
    {"config/Valves/2/Init", (unsigned  int)&(irrigationConfig.Valves[2].InitialState), RestBool, false, 0, 1},
    {"config/Valves/3/Init", (unsigned  int)&(irrigationConfig.Valves[3].InitialState), RestBool, false, 0, 1},
    {"config/Valves/4/Init", (unsigned  int)&(irrigationConfig.Valves[4].InitialState), RestBool, false, 0, 1},
    {"config/Valves/5/Init", (unsigned  int)&(irrigationConfig.Valves[5].InitialState), RestBool, false, 0, 1},
    {"config/Valves/6/Init", (unsigned  int)&(irrigationConfig.Valves[6].InitialState), RestBool, false, 0, 1},
    {"config/Valves/7/Init", (unsigned  int)&(irrigationConfig.Valves[7].InitialState), RestBool, false, 0, 1},
    {"config/Valves/8/Init", (unsigned  int)&(irrigationConfig.Valves[8].InitialState), RestBool, false, 0, 1},

    {"config/Valves/0/Invert", (unsigned  int)&(irrigationConfig.Valves[0].Invert), RestBool, false, 0, 1},
    {"config/Valves/1/Invert", (unsigned  int)&(irrigationConfig.Valves[1].Invert), RestBool, false, 0, 1},
    {"config/Valves/2/Invert", (unsigned  int)&(irrigationConfig.Valves[2].Invert), RestBool, false, 0, 1},
    {"config/Valves/3/Invert", (unsigned  int)&(irrigationConfig.Valves[3].Invert), RestBool, false, 0, 1},
    {"config/Valves/4/Invert", (unsigned  int)&(irrigationConfig.Valves[4].Invert), RestBool, false, 0, 1},
    {"config/Valves/5/Invert", (unsigned  int)&(irrigationConfig.Valves[5].Invert), RestBool, false, 0, 1},
    {"config/Valves/6/Invert", (unsigned  int)&(irrigationConfig.Valves[6].Invert), RestBool, false, 0, 1},
    {"config/Valves/7/Invert", (unsigned  int)&(irrigationConfig.Valves[7].Invert), RestBool, false, 0, 1},
    {"config/Valves/8/Invert", (unsigned  int)&(irrigationConfig.Valves[8].Invert), RestBool, false, 0, 1},
    // Zones
    {"config/Zones/0/Valves/0", (unsigned  int)&irrigationConfig.Zones[0].Valves[0], RestInt, false,PinMin,PinMax},
    {"config/Zones/0/Valves/1", (unsigned  int)&irrigationConfig.Zones[0].Valves[1], RestInt, false,PinMin,PinMax},
    {"config/Zones/0/Valves/2", (unsigned  int)&irrigationConfig.Zones[0].Valves[2], RestInt, false,PinMin,PinMax},
    {"config/Zones/0/Valves/3", (unsigned  int)&irrigationConfig.Zones[0].Valves[3], RestInt, false,PinMin,PinMax},

    {"config/Zones/1/Valves/0", (unsigned  int)&irrigationConfig.Zones[1].Valves[0], RestInt, false,PinMin,PinMax},
    {"config/Zones/1/Valves/1", (unsigned  int)&irrigationConfig.Zones[1].Valves[1], RestInt, false,PinMin,PinMax},
    {"config/Zones/1/Valves/2", (unsigned  int)&irrigationConfig.Zones[1].Valves[2], RestInt, false,PinMin,PinMax},
    {"config/Zones/1/Valves/3", (unsigned  int)&irrigationConfig.Zones[1].Valves[3], RestInt, false,PinMin,PinMax},

    {"config/Zones/2/Valves/0", (unsigned  int)&irrigationConfig.Zones[2].Valves[0], RestInt, false,PinMin,PinMax},
    {"config/Zones/2/Valves/1", (unsigned  int)&irrigationConfig.Zones[2].Valves[1], RestInt, false,PinMin,PinMax},
    {"config/Zones/2/Valves/2", (unsigned  int)&irrigationConfig.Zones[2].Valves[2], RestInt, false,PinMin,PinMax},
    {"config/Zones/2/Valves/3", (unsigned  int)&irrigationConfig.Zones[2].Valves[3], RestInt, false,PinMin,PinMax},

    {"config/Zones/3/Valves/0", (unsigned  int)&irrigationConfig.Zones[3].Valves[0], RestInt, false,PinMin,PinMax},
    {"config/Zones/3/Valves/1", (unsigned  int)&irrigationConfig.Zones[3].Valves[1], RestInt, false,PinMin,PinMax},
    {"config/Zones/3/Valves/2", (unsigned  int)&irrigationConfig.Zones[3].Valves[2], RestInt, false,PinMin,PinMax},
    {"config/Zones/3/Valves/3", (unsigned  int)&irrigationConfig.Zones[3].Valves[3], RestInt, false,PinMin,PinMax},

    {"config/Zones/4/Valves/0", (unsigned  int)&irrigationConfig.Zones[4].Valves[0], RestInt, false,PinMin,PinMax},
    {"config/Zones/4/Valves/1", (unsigned  int)&irrigationConfig.Zones[4].Valves[1], RestInt, false,PinMin,PinMax},
    {"config/Zones/4/Valves/2", (unsigned  int)&irrigationConfig.Zones[4].Valves[2], RestInt, false,PinMin,PinMax},
    {"config/Zones/4/Valves/3", (unsigned  int)&irrigationConfig.Zones[4].Valves[3], RestInt, false,PinMin,PinMax},
    //
    {"config/Zones/0/Soil/0", (unsigned  int)&irrigationConfig.Zones[0].SoilhumidiesId[0], RestInt, false,SoilHumidiesIdMin,SoilHumidiesIdMax},
    {"config/Zones/0/Soil/1", (unsigned  int)&irrigationConfig.Zones[0].SoilhumidiesId[1], RestInt, false,SoilHumidiesIdMin,SoilHumidiesIdMax},
    {"config/Zones/0/Soil/2", (unsigned  int)&irrigationConfig.Zones[0].SoilhumidiesId[2], RestInt, false,SoilHumidiesIdMin,SoilHumidiesIdMax},
    {"config/Zones/0/Soil/3", (unsigned  int)&irrigationConfig.Zones[0].SoilhumidiesId[3], RestInt, false,SoilHumidiesIdMin,SoilHumidiesIdMax},

    {"config/Zones/1/Soil/0", (unsigned  int)&irrigationConfig.Zones[1].SoilhumidiesId[0], RestInt, false,SoilHumidiesIdMin,SoilHumidiesIdMax},
    {"config/Zones/1/Soil/1", (unsigned  int)&irrigationConfig.Zones[1].SoilhumidiesId[1], RestInt, false,SoilHumidiesIdMin,SoilHumidiesIdMax},
    {"config/Zones/1/Soil/2", (unsigned  int)&irrigationConfig.Zones[1].SoilhumidiesId[2], RestInt, false,SoilHumidiesIdMin,SoilHumidiesIdMax},
    {"config/Zones/1/Soil/3", (unsigned  int)&irrigationConfig.Zones[1].SoilhumidiesId[3], RestInt, false,SoilHumidiesIdMin,SoilHumidiesIdMax},

    {"config/Zones/2/Soil/0", (unsigned  int)&irrigationConfig.Zones[2].SoilhumidiesId[0], RestInt, false,SoilHumidiesIdMin,SoilHumidiesIdMax},
    {"config/Zones/2/Soil/1", (unsigned  int)&irrigationConfig.Zones[2].SoilhumidiesId[1], RestInt, false,SoilHumidiesIdMin,SoilHumidiesIdMax},
    {"config/Zones/2/Soil/2", (unsigned  int)&irrigationConfig.Zones[2].SoilhumidiesId[2], RestInt, false,SoilHumidiesIdMin,SoilHumidiesIdMax},
    {"config/Zones/2/Soil/3", (unsigned  int)&irrigationConfig.Zones[2].SoilhumidiesId[3], RestInt, false,SoilHumidiesIdMin,SoilHumidiesIdMax},

    {"config/Zones/3/Soil/0", (unsigned  int)&irrigationConfig.Zones[3].SoilhumidiesId[0], RestInt, false,SoilHumidiesIdMin,SoilHumidiesIdMax},
    {"config/Zones/3/Soil/1", (unsigned  int)&irrigationConfig.Zones[3].SoilhumidiesId[1], RestInt, false,SoilHumidiesIdMin,SoilHumidiesIdMax},
    {"config/Zones/3/Soil/2", (unsigned  int)&irrigationConfig.Zones[3].SoilhumidiesId[2], RestInt, false,SoilHumidiesIdMin,SoilHumidiesIdMax},
    {"config/Zones/3/Soil/3", (unsigned  int)&irrigationConfig.Zones[3].SoilhumidiesId[3], RestInt, false,SoilHumidiesIdMin,SoilHumidiesIdMax},

    {"config/Zones/4/Soil/0", (unsigned  int)&irrigationConfig.Zones[4].SoilhumidiesId[0], RestInt, false,SoilHumidiesIdMin,SoilHumidiesIdMax},
    {"config/Zones/4/Soil/1", (unsigned  int)&irrigationConfig.Zones[4].SoilhumidiesId[1], RestInt, false,SoilHumidiesIdMin,SoilHumidiesIdMax},
    {"config/Zones/4/Soil/2", (unsigned  int)&irrigationConfig.Zones[4].SoilhumidiesId[2], RestInt, false,SoilHumidiesIdMin,SoilHumidiesIdMax},
    {"config/Zones/4/Soil/3", (unsigned  int)&irrigationConfig.Zones[4].SoilhumidiesId[3], RestInt, false,SoilHumidiesIdMin,SoilHumidiesIdMax},

    {"config/Zones/0/StartTime", (unsigned  int)&irrigationConfig.Zones[0].StartTime, RestTm, false},
    {"config/Zones/1/StartTime", (unsigned  int)&irrigationConfig.Zones[1].StartTime, RestTm, false},
    {"config/Zones/2/StartTime", (unsigned  int)&irrigationConfig.Zones[2].StartTime, RestTm, false},
    {"config/Zones/3/StartTime", (unsigned  int)&irrigationConfig.Zones[3].StartTime, RestTm, false},
    {"config/Zones/4/StartTime", (unsigned  int)&irrigationConfig.Zones[4].StartTime, RestTm, false},

    {"config/Zones/0/StartSoil", (unsigned  int)&irrigationConfig.Zones[0].StartSoilHumidy, RestInt, false,SoilHumidiesStateMin,SoilHumidiesStateMax},
    {"config/Zones/1/StartSoil", (unsigned  int)&irrigationConfig.Zones[1].StartSoilHumidy, RestInt, false,SoilHumidiesStateMin,SoilHumidiesStateMax},
    {"config/Zones/2/StartSoil", (unsigned  int)&irrigationConfig.Zones[2].StartSoilHumidy, RestInt, false,SoilHumidiesStateMin,SoilHumidiesStateMax},
    {"config/Zones/3/StartSoil", (unsigned  int)&irrigationConfig.Zones[3].StartSoilHumidy, RestInt, false,SoilHumidiesStateMin,SoilHumidiesStateMax},
    {"config/Zones/4/StartSoil", (unsigned  int)&irrigationConfig.Zones[4].StartSoilHumidy, RestInt, false,SoilHumidiesStateMin,SoilHumidiesStateMax},

    {"config/Zones/0/Spray", (unsigned  int)&irrigationConfig.Zones[0].SprayDuration, RestTm, false},
    {"config/Zones/1/Spray", (unsigned  int)&irrigationConfig.Zones[1].SprayDuration, RestTm, false},
    {"config/Zones/2/Spray", (unsigned  int)&irrigationConfig.Zones[2].SprayDuration, RestTm, false},
    {"config/Zones/3/Spray", (unsigned  int)&irrigationConfig.Zones[3].SprayDuration, RestTm, false},
    {"config/Zones/4/Spray", (unsigned  int)&irrigationConfig.Zones[4].SprayDuration, RestTm, false},

    {"config/Zones/0/Soak", (unsigned  int)&irrigationConfig.Zones[0].SoakDuration, RestTm, false},
    {"config/Zones/1/Soak", (unsigned  int)&irrigationConfig.Zones[1].SoakDuration, RestTm, false},
    {"config/Zones/2/Soak", (unsigned  int)&irrigationConfig.Zones[2].SoakDuration, RestTm, false},
    {"config/Zones/3/Soak", (unsigned  int)&irrigationConfig.Zones[3].SoakDuration, RestTm, false},
    {"config/Zones/4/Soak", (unsigned  int)&irrigationConfig.Zones[4].SoakDuration, RestTm, false},

    {"config/Zones/0/StopSoil", (unsigned  int)&irrigationConfig.Zones[0].StopSoilHumidy, RestInt, false,SoilHumidiesStateMin,SoilHumidiesStateMax},
    {"config/Zones/1/StopSoil", (unsigned  int)&irrigationConfig.Zones[1].StopSoilHumidy, RestInt, false,SoilHumidiesStateMin,SoilHumidiesStateMax},
    {"config/Zones/2/StopSoil", (unsigned  int)&irrigationConfig.Zones[2].StopSoilHumidy, RestInt, false,SoilHumidiesStateMin,SoilHumidiesStateMax},
    {"config/Zones/3/StopSoil", (unsigned  int)&irrigationConfig.Zones[3].StopSoilHumidy, RestInt, false,SoilHumidiesStateMin,SoilHumidiesStateMax},
    {"config/Zones/4/StopSoil", (unsigned  int)&irrigationConfig.Zones[4].StopSoilHumidy, RestInt, false,SoilHumidiesStateMin,SoilHumidiesStateMax},

    {"config/Zones/0/StopTime", (unsigned  int)&irrigationConfig.Zones[0].StopTime, RestTm, false},
    {"config/Zones/1/StopTime", (unsigned  int)&irrigationConfig.Zones[1].StopTime, RestTm, false},
    {"config/Zones/2/StopTime", (unsigned  int)&irrigationConfig.Zones[2].StopTime, RestTm, false},
    {"config/Zones/3/StopTime", (unsigned  int)&irrigationConfig.Zones[3].StopTime, RestTm, false},
    {"config/Zones/4/StopTime", (unsigned  int)&irrigationConfig.Zones[4].StopTime, RestTm, false},

    {"config/Zones/0/StopTank", (unsigned  int)&irrigationConfig.Zones[0].StopTankLevel, RestInt, false, 0, TankLevelMax},
    {"config/Zones/1/StopTank", (unsigned  int)&irrigationConfig.Zones[1].StopTankLevel, RestInt, false, 0, TankLevelMax},
    {"config/Zones/2/StopTank", (unsigned  int)&irrigationConfig.Zones[2].StopTankLevel, RestInt, false, 0, TankLevelMax},
    {"config/Zones/3/StopTank", (unsigned  int)&irrigationConfig.Zones[3].StopTankLevel, RestInt, false, 0, TankLevelMax},
    {"config/Zones/4/StopTank", (unsigned  int)&irrigationConfig.Zones[4].StopTankLevel, RestInt, false, 0, TankLevelMax}
};

RestElement AddElement(String endpoint,unsigned int pointer, RestType type, bool readOnly, double min, double max) {
    RestElement ret;
    ret.endpoint = endpoint;
    ret.pointer = pointer;
    ret.type = type;
    ret.readOnly = readOnly;
    ret.min = min;
    ret.max = max;
    return ret;
}

String restJSON = "{\"value\": valValue, \"type\": valType, \"readOnly\": valRead, \"min\": valMin, \"max\": valMax}";

String getRestValueString(RestElement element)
{
    String value = "";
    switch (element.type)
    {
        case RestNull:
        value = "null";
        break;
    case RestBool:
        if( (*((bool *)element.pointer))!=0) {
            value = "1";
        }
        else {
            value = "0";
        }
        break;
    case RestByte:
        value = String(*((byte *)element.pointer));
        break;
    case RestChar:
        value = String(*((char *)element.pointer));
        break;
    case RestDouble:
        value = String(*((double *)element.pointer));
        break;
    case RestFloat:
        value = String(*((float *)element.pointer));
        break;
    case RestInt:
        value = String(*((int *)element.pointer));
        break;
    case RestLong:
        value = String(*((long *)element.pointer));
        break;
    case RestShort:
        value = String(*((short *)element.pointer));
        break;
    case RestCharArray:
        value = String(*((char **)element.pointer));
        break;
    case RestUnsignedChar:
        value = String(*((unsigned char *)element.pointer));
        break;
    case RestUnsignedInt:
        value = String(*((unsigned int *)element.pointer));
        break;
    case RestUnsignedLong:
        value = String(*((unsigned long *)element.pointer));
        break;
    case RestWord:
        value = String(*((word *)element.pointer));
        break;
    case RestLongLong:
        value = ""; //String(*((long long *)(RestElements[index].pointer));
        break;
    case RestTm:
        tm time = (*((tm *)element.pointer));
        char buffer[20];
        // 00:00:00 00:00:0000
        sprintf(buffer, "%02d:%02d:%02d %02d.%02d.%04d", time.tm_hour, time.tm_min, time.tm_sec, time.tm_mday, time.tm_mon, time.tm_year);
        value = String(buffer);
        break;
    }
    return value;
}

RestElement getRestElementByEndpoint(String endpoint) {
    for (int a=0; a < RestElementsLength;a++) {
        if (RestElements[a].endpoint == endpoint) {
            return RestElements[a];
        }
    }
    RestElement ret;
    ret.type = RestNull;
    return ret;
}

bool setRestValue(RestElement element, String text)
{
    switch (element.type)
    {
        case RestNull:
        return true;
        break;
    case RestBool:
        *((bool *)element.pointer) = text == "1";
        return true;
    case RestByte:
        *((byte *)element.pointer) = (byte)text.toInt();
        return true;
    case RestChar:
        *((char *)element.pointer) = (char)text.toInt();
        return true;
    case RestDouble:
        *((double *)element.pointer) = text.toDouble();
        return true;
    case RestFloat:
        *((float *)element.pointer) = text.toFloat();
        return true;
    case RestInt:
        *((int *)element.pointer) = text.toInt();
        return true;
    case RestLong:
        *((long *)element.pointer) = (long)text.toInt();
        return true;
    case RestShort:
        *((short *)element.pointer) = (short)text.toInt();
        return true;
    case RestCharArray:
        for (int a=0; a < element.max && a < text.length();a++) {
            (*((char **)element.pointer))[a] = text.charAt(a);
        }
        return true;
    case RestUnsignedChar:
        *((unsigned char *)element.pointer) = (unsigned char)text.toInt();
        return true;
    case RestUnsignedInt:
        *((unsigned int *)element.pointer) = (unsigned int)text.toInt();
        return true;
    case RestUnsignedLong:
        *((unsigned long *)element.pointer) = (unsigned long)text.toInt();
        return true;
    case RestWord:
        *((word *)element.pointer) = (word)text.toInt();
        return true;
    case RestLongLong:
        *((long long *)element.pointer) = (long long)text.toInt();
        return true;

    case RestTm:
        // 0123456789012345678
        // 00:00:00 00.00.0000
        if (text.length() == 19)
        {
            (*((tm *)element.pointer)).tm_hour = text.substring(0, 2).toInt();
            (*((tm *)element.pointer)).tm_min = text.substring(3, 5).toInt();
            (*((tm *)element.pointer)).tm_sec = text.substring(6, 8).toInt();

            (*((tm *)element.pointer)).tm_mday = text.substring(9, 11).toInt();
            (*((tm *)element.pointer)).tm_mon = text.substring(12, 14).toInt();
            (*((tm *)element.pointer)).tm_year = text.substring(15).toInt();
            return true;
        }
        return false;
    }
    return false;
}

String getRestValueJSON(int index) {
    String value = getRestValueString(RestElements[index]);
     //Debug("rest","get",uri + ":" + text);
    String text = restJSON;
    text.replace("valValue",value);
    text.replace("valType",String(RestElements[index].type));
    text.replace("valRead",String(RestElements[index].readOnly));
    text.replace("valMin",String(RestElements[index].min));
    text.replace("valMax",String(RestElements[index].max));
    return text;
}

void HandleGetRest(AsyncWebServerRequest *request)
{
    String uri = request->url();
   
    // find entrie;
    uri.replace("/rest/","");
    int elementIndex = -1;
    for (int a = 0; a < RestElementsLength; a++)
    {
        if (RestElements[a].endpoint == uri)
        {
            elementIndex = a;
            break;
        }
        
    }
    if (index < 0)
    {
        request->send(404, "text/plain", "RestElement not found");
        
        return;
    }
    // GET
    //Debug("RestGet",RestElements[elementIndex].endpoint, getRestValueString(RestElements[elementIndex]));
   String text = getRestValueString(RestElements[elementIndex]);
    
    request->send(200, "text/plain", text);
}

void HandlePostRest(AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total)
{
    String uri = request->url();
    uri.replace("/rest/","");
    // find entrie;
    int elementIndex = -1;
    for (int a = 0; a < RestElementsLength; a++)
    {
        if (RestElements[a].endpoint == uri)
        {
            elementIndex = a;
            break;
        }
    }
    if (elementIndex < 0)
    {
        request->send(404, "text/plain", "RestElement not found");
        return;
    }

    if (RestElements[elementIndex].readOnly)
    {
        request->send(400, "text/plain", "RestElement is read only");
        return;
    }
    String text;
    for (int a = 0; a < len; a++)
    {
        text += String((char)data[a]);
    }
    bool setValue = setRestValue(RestElements[elementIndex], text);
    text = "";
    if (setValue)
    {
        // Extra Rules      0123456789012345
        if (uri.startsWith("Soil/"))
        {
            int sensorIndex = String(uri.charAt(16)).toInt();
            copyTimeToTime(&currentIrrigationData.Time, &currentIrrigationData.SoilHumidies[sensorIndex].Timeout);
            addTime(&currentIrrigationData.SoilHumidies[sensorIndex].Timeout, 0, 5, 0, 0, 0, 0);
        }
        text = getRestValueString(RestElements[elementIndex]);
        request->send(200, "text/plain", text);
    }
    else
    {
        request->send(404, "text/plain", "cannot set Value");
    }
}

void SetupRest()
{
    for (int a = 0; a < RestElementsLength; a++)
    {
        server.on(String("/rest/" + RestElements[a].endpoint).c_str(), HTTP_GET, HandleGetRest);
        server.on(
            String("/rest/" + RestElements[a].endpoint).c_str(), HTTP_POST, [](AsyncWebServerRequest *request) {}, NULL,
            HandlePostRest);
    }
}

void LoopRest()
{
}

#endif
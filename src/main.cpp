#include <Arduino.h>

#include "L_time.h"
#include "L_debug.h"
#include "L_tank.h"
#include "L_soilhumidy.h"
#include "L_valves.h"
#include "L_webserver.h"
#include "L_webserverRest.h"
#include "L_webpage.h"
#include "L_controller.h"







void setup()
{
  SetupDebug();
  SetupData();
  SetupWebserver();
  SetupRest();
  SetupWebpage();
  SetupTime();
  SetupSoilhumidy();
  SetupTank();
  SetupController();
  //Debug("Task","Main",String(xPortGetCoreID()));
}
void loop()
{
  // put your main code here, to run repeatedly:
  //Utility
  LoopTime();
   yield();
  LoopWebserver();
   yield();
  // Sensoren
  LoopSoilhumidy();
   yield();
  LoopTank();
   yield();
  // Controller
  LoopController();
   yield();
  // Aktoren

  //
  LoopData();

  LoopDebug();


  //LoopRest();
  yield();
}
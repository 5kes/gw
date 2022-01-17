#ifndef MY_THERMOCOUPLE_H
#define MY_THERMOCOUPLE_H

#include <Arduino.h>
#include "Adafruit_MAX31855.h"
#include "TickTwo.h"

class Thermocouple {
  
  private:
    Adafruit_MAX31855 *thermocouple;
    TickTwo *runTick;
    void runFunc();
    double currentTemp;
    double tempThresh;
    double tempHyst;
    bool tempAlarmState;
    void handleTempAlarm();
    void handleTempDisalarm();
    void handleLogTemp();
    
  public:
    Thermocouple(
      const int8_t DO, 
      const int8_t CS,
      const int8_t CLK,
      double tempThresh,
      double tempHyst
    );
    void updateTimer();
    void setInterval(uint32_t);
    void getInterval();
};

#endif

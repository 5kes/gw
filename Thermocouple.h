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
    
  public:
    Thermocouple(
      const int8_t DO, 
      const int8_t CS,
      const int8_t CLK);
    void updateTimer();
};

#endif

#ifndef MY_INVERTER_H
#define MY_INVERTER_H

#include <Arduino.h>


class Inverter {
  
  private:
    int atsPin; // pin 4 = D2 input pullup, triggers when connected to GND of NodeMCU
    static bool atsState;
//    static void readAtsPin();
    static void handleAtsChange();
    
  public:
    Inverter(int atsPin);
    bool getAtsState();
    void setupInterrupt(void (*)());
//    static void setAtsState(bool newState);

};

#endif

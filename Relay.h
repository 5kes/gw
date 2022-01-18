#ifndef MY_RELAY_H
#define MY_RELAY_H

#include <Arduino.h>

class Relay {
  
  private:
    static bool relayState;
    byte pin;
    
  public:
    Relay(byte pin);
    void turnOn();
    void turnOff();
};

#endif

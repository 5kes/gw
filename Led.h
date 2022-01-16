#ifndef MY_LED_H
#define MY_LED_H

#include <Arduino.h>
//#include <Ticker.h>

class Led {
  
  private:
    byte pin;
    byte state;
//    Ticker tickit;
    
  public:
    Led(byte pin);
    void init();
    void on();
    void off();
    void blinky();
    byte getState();
};

#endif

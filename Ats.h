#ifndef MY_ATS_H
#define MY_ATS_H

#include <Arduino.h>

class Ats {
  
  private:
    static bool atsState;
    
  public:
    Ats();
    bool getAtsState();
    static void setAtsState(bool newState);

};

#endif

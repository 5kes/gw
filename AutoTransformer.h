#ifndef MY_ATX_H
#define MY_ATX_H

#include <Arduino.h>
#include "Ats.h"

class Ats;

class AutoTransformer {
  
  private:
    Ats ats;
    int id;
    
  public:
    AutoTransformer(Ats atsSwitch, int id);
    bool getAtsState();
    int getId();
};

#endif

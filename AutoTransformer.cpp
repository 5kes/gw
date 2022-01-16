#include "AutoTransformer.h"
#include "Ats.h"

class Ats;

AutoTransformer::AutoTransformer(Ats atsSwitch) {
  this->ats = atsSwitch;
}

bool AutoTransformer::getAtsState() {
  Serial.println("Getting ATS state from AT");
  return ats.getAtsState();
}

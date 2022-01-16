#include "AutoTransformer.h"
#include "Ats.h"

class Ats;

AutoTransformer::AutoTransformer(Ats atsSwitch, int id) {
  this->ats = atsSwitch;
  this->id = id;
}

bool AutoTransformer::getAtsState() {
  Serial.println("Getting ATS state from AT");
  return ats.getAtsState();
}

int AutoTransformer::getId() {
  Serial.println("getting AT id");
  return this->id;
}

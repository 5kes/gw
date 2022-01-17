#include "AutoTransformer.h"
#include "Ats.h"

class Ats;

AutoTransformer::AutoTransformer(Ats ats, int id) {
  this->ats = ats;
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

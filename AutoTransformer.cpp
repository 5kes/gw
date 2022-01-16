#include "AutoTransformer.h"
#include "Ats.h"

class Ats;

AutoTransformer::AutoTransformer(Ats atsSwitch) {
  this->ats = atsSwitch;
}

bool AutoTransformer::getAtsState() {
  return ats.getAtsState();
}

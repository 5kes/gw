#include "Ats.h"

bool Ats::atsState{ true };

bool Ats::getAtsState() {
//  Serial.println("Getting ATS state: " + String(this->atsState));
  Serial.println("getting ATS state");
  return this->atsState;
//  return true;
}

void Ats::setAtsState(bool newState) {
  Serial.println("Setting ATS state to: " + String(newState));
  Ats::atsState = newState;
}

Ats::Ats() {
//  Ats::atsState = false;
}

#include "Inverter.h"

// Important! Static class members can only be SET by static class functions, but can be READ by
// either static or instance functions

// assume we're on grid upon boot
bool Inverter::atsState{ true };

bool Inverter::getAtsState() {
  Serial.println("getting inverter ATS state");
  return this->atsState;
}
//
//void Inverter::setAtsState(bool newState) {
//  Serial.println("Setting inverter ATS state to: " + String(newState));
//  Inverter::atsState = newState;
//}
//
//void Inverter::readAtsPin() {
//  Serial.println("reading ATS pin");
//  Inverter::setAtsState(digitalRead(Inverter::atsPin));
//}
//
void ICACHE_RAM_ATTR Inverter::handleAtsChange() {
  Serial.println("handling ATS change");
}

void Inverter::setupInterrupt(void (*handleChange)()) {
  attachInterrupt(digitalPinToInterrupt(atsPin), handleChange, CHANGE);
}

Inverter::Inverter(int atsPin) {
  Serial.println("Making new inverter object");
  this->atsPin = atsPin;
  pinMode(this->atsPin, INPUT_PULLUP);
//  Inverter::readAtsPin();
//  atsState = digitalRead(atsPin);
//  attachInterrupt(digitalPinToInterrupt(atsPin), Inverter::handleAtsChange, CHANGE);
}

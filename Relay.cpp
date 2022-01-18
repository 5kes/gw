#include "Relay.h"

bool Relay::relayState{ false }; // start with relays OFF

Relay::Relay(byte pin) {
  this->pin = pin;
}

void Relay::turnOn() {
  Serial.println("Relay turning ON");
}

void Relay::turnOff() {
  Serial.println("Relay turning ON");
}

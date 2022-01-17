#include "Thermocouple.h"

void Thermocouple::runFunc() {
  Serial.println("runfunc called");
  this->thermocouple->readFahrenheit();
}

Thermocouple::Thermocouple(
      const int8_t CLK,
      const int8_t CS,
      const int8_t DO) {
  Serial.println("Making new thermocouple");
  this->thermocouple = new Adafruit_MAX31855(CLK, CS, DO);
  this->runTick = new TickTwo([](){ Serial.println("hello"); }, 1000, 0, MILLIS);
  this->runTick->start();
//  this->thermocouple->readFahrenheit();
}

void Thermocouple::updateTimer() {
  this->runTick->update();
}

//bool AutoTransformer::getAtsState() {
//  Serial.println("Getting ATS state from AT");
//  return ats.getAtsState();
//}
//
//int AutoTransformer::getId() {
//  Serial.println("getting AT id");
//  return this->id;
//}
//
//Adafruit_MAX31855 thermocouple(MAXCLK, MAXCS, MAXDO);

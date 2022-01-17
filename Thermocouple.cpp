#include "Thermocouple.h"

void Thermocouple::runFunc() {
  Serial.println("runfunc called");
  this->thermocouple->readFahrenheit();
}

Thermocouple::Thermocouple(
      const int8_t CLK,
      const int8_t CS,
      const int8_t DO,
      double tempThresh,
      double tempHyst
  ) {
    
  Serial.println("Making new thermocouple");
  
  this->currentTemp = NULL;
  this->tempAlarmState = false; // assume a cold-start isn't over-temp
  this->tempThresh = tempThresh;
  this->tempHyst = tempHyst;
  
  this->thermocouple = new Adafruit_MAX31855(CLK, CS, DO);
  this->runTick = new TickTwo([this](){
    
    this->currentTemp = this->thermocouple->readFahrenheit();

    if (this->currentTemp == NULL) {
      Serial.println("Unable to get temp from thermocouple");
    } else {
      // Temp alarm: over temp and not in an alarmed state
      if ((this->currentTemp > this->tempThresh) && !this->tempAlarmState) {
        this->handleTempAlarm();
      // Temp disalarm: under temp - hyst, in an alarmed state
      } else if ((this->currentTemp < (this->tempThresh - this->tempHyst)) && this->tempAlarmState) {
        this->handleTempDisalarm();
      } else {
        this->handleLogTemp();
      } 
    }
    }, 1000, 0, MILLIS);
  this->runTick->start();
//  this->thermocouple->readFahrenheit();
}

void Thermocouple::handleTempAlarm() {
  Serial.println("Handling over temp alarm");
}

void Thermocouple::handleTempDisalarm() {
  Serial.println("Handling over temp disalarm");
}

void Thermocouple::handleLogTemp() {
  Serial.println("Handling temp logging");
}

void Thermocouple::updateTimer() {
  this->runTick->update();
}

void Thermocouple::setInterval(uint32_t timer) {
  this->runTick->interval(timer);
}

void Thermocouple::getInterval() {
  Serial.println("Interval is: " + String(this->runTick->interval()));
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

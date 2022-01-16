#include "Led.h"

//#include <Ticker.h>

//Led::Led(byte pin) {
//  this->pin = pin;
//  this->state = state;
////  TickTwo tickit(this->blinky, 500, 0, MILLIS);
//  init();
//}

Led::Led(byte pin) {
  this->pin = pin;
  this->state = state;
//  TickTwo tickit(this->blinky, 500, 0, MILLIS);
//  this->tickit = tickit;
  init();
}


void Led::init() {
  pinMode(pin, OUTPUT);
  state = LOW;
//  Ticker tickit(blinky, 400, 0, MICROS);
//  TickTwo tickit (*this::blinky);
//  TickTwo ledTick(getTemp, 250, 40, MILLIS);
  off();
}

void Led::on() { digitalWrite(pin, LOW);}
void Led::off() { digitalWrite(pin, HIGH); }

void Led::blinky() {
  digitalWrite(pin, state);
  state = !state;
}

byte Led::getState() { return state; }

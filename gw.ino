#include <SPI.h>
#include <TickTwo.h>
//#include <Ticker.h>
#include "Led.h"
#include "Adafruit_MAX31855.h"

/* ATS: Automatic Transfer Switch - dry contacts for the growatt
 * ATX / AT: AutoTransformer
 * NSC: Neutral Safety Contactor
 */

// Pins
const int MAXDO = 12; // D6 of NodeMCU connects to 'DO' data out of MAX31855
const int MAXCS = 15; // D8 of NodeMCU connects to 'CS' of MAX31855
const int MAXCLK = 14; // D5 of NodeMCU connects to 'CLK' of MAX31855
Adafruit_MAX31855 thermocouple(MAXCLK, MAXCS, MAXDO);

 // TESTING
#include "Ats.h"
#include "AutoTransformer.h"
#include "Thermocouple.h"
#include "Inverter.h"
#include "Relay.h"

Ats myAts;
AutoTransformer myAt69(myAts, 69);
AutoTransformer myAt88(myAts, 88);
Thermocouple myTherm(MAXDO, MAXCS, MAXCLK, 80, 1.5);
Inverter myInv(4);

void ICACHE_RAM_ATTR atsChangeHandler() {
  Serial.println("handling ATS change with setup defined function 1");
}


// Timers
void getTemp(); // thermocouple
void getAmps(); // neutral current
void goOffGrid();
void ledBlink(); // visual indicator for when system transitions to off-grid mode (on grid = steady, off = blinking)
TickTwo cronTemp(getTemp, 2000, 0, MILLIS); // temp read every 2s, indefinitely
TickTwo cronAmps(getAmps, 500, 0, MILLIS); // neutral current read every 1/2s, indefinitely (sensor updates every second)
TickTwo cronTempBoot(getTemp, 250, 40, MILLIS); // read temp every 1/4s, 40 times (10s for bootup)
TickTwo cronGoOffGrid(goOffGrid, 250, 40, MILLIS); // bootstrap atx read every 1/4s, 40 times (10s for bootup)
TickTwo cronLed(ledBlink, 500, 0, MILLIS); // blink led every 1/2s, indefinitely (off-grid indicator led)

// Globals
const int ledEsp = 2; // by the antenna
const int ledMcu = 16; // by the mini usb connector
//Ticker tickit2(Led::blinky, 888, 0, MICROS);
Led ledUsb(ledMcu);
bool ledEspState;
bool ledMcuState;

volatile bool tempAlarmState = false; // true = in alarm state
double currentTemp; // MAX31855 will read 0.0F if it is disconnected
double tempThresh = 80.0; // temp above which alarm is triggered
double tempHyst = 1.5; // hysteresis, must be positive double that is < tempThresh

volatile bool ampsAlarmState = false; // true = in alarm state
double currentAmps;
double ampsThresh = 25.0; // amps above which alarm is triggered
double ampsHyst = 3.0; // hysteresis, must be positive double that is < ampsThresh

const int atsPin = 4; // D2 input pullup, triggers when connected to GND of NodeMCU
volatile bool atsState; // true = on-grid (dry contact loop open)
const int atsDebounceDelay = 50; // 50ms debounce filter
volatile long lastAtsDebounceTime = 0; // last millis() time ats debounce was triggered

volatile bool nscState = false; // neutral safety contactor state, default this to false (disconnected)

bool atxState = false; // autotransformer state, true = on, false = off

void ledOn(){
//  Serial.println("led on");
  digitalWrite(ledEsp, LOW);
}

void ledOff(){
//  Serial.println("led off");
  digitalWrite(ledEsp, HIGH);
}

void ledBlink() {
  digitalWrite(ledEsp, ledEspState);
  ledEspState = !ledEspState;
}

class Foo {
  private:
    bool a;

  public:
    Foo(bool inita);
    void printa();
};

Foo::Foo(bool inita) {
  this->a = inita;
}

void Foo::printa() {
  Serial.println("a is:");
  Serial.println(String(a));
}


void setup() {
  
  pinMode(ledEsp, OUTPUT);
//  pinMode(atsPin, INPUT_PULLUP);
//  
//  atsState = digitalRead(atsPin);
//  attachInterrupt(digitalPinToInterrupt(atsPin), atsAction, CHANGE);

  Serial.begin(9600);
  while (!Serial) delay(1); // wait for Serial on Leonardo/Zero, etc
  Serial.println("Booting...");
  delay(2000);

  Serial.println("My inverter atsState: " + String(myInv.getAtsState()));
  myInv.setupInterrupt(atsChangeHandler);

  Serial.println("My ats state: " + String(myAts.getAtsState()));
  Serial.println("My ats state via AutoTransformer 69: " + String(myAt69.getAtsState()));
  Serial.println("My ats state via AutoTransformer 88: " + String(myAt88.getAtsState()));
  Serial.println("My AT ID: " + String(myAt69.getId()));
  Serial.println("My AT ID: " + String(myAt88.getId()));
  Serial.println("Changing ats state");
  Ats::setAtsState(false);
  Serial.println("Done changing ats state");
  Serial.println("My NEW ats state via AutoTransformer 69: " + String(myAt69.getAtsState()));
  Serial.println("My NEW ats state via AutoTransformer 88: " + String(myAt88.getAtsState()));
  
    
  // if dry contact is open, attempt to auto-bootstrap system
  if (!atsState) {
    Serial.println("System booted with dry contact open, attempting to auto-bootstrap...");
    cronTempBoot.start();
    cronGoOffGrid.start();
  }

  cronTemp.start();
  cronAmps.start();
  
  if (!thermocouple.begin()) {
    Serial.println("Unable to start thermocouple");
    while (1) delay(10);
  }
  myTherm.getInterval();
  myTherm.setInterval(5000);
  myTherm.getInterval();
  Serial.println("Booting complete");
}

void loop() {
  cronTemp.update();
  cronAmps.update();
  cronTempBoot.update();
  cronGoOffGrid.update();
  cronLed.update();
  myTherm.updateTimer();
}

ICACHE_RAM_ATTR void atsAction(){
  int atsReading = digitalRead(atsPin);
  if (atsReading == atsState) {
    return;
  }
  boolean debounce = false;
  if ((millis() - lastAtsDebounceTime) <= atsDebounceDelay) {
    debounce = true;
  }
  lastAtsDebounceTime = millis();
  if (debounce) {
    Serial.println("less than debounce time, keeping state at: " + String(atsState));
    return;
  } else {
    Serial.println("setting state to: " + String(atsReading));
    atsState = atsReading;
    if (atsState) {
      Serial.println("ON grid");
      goOnGrid();
    } else {
      Serial.println("OFF grid");
      goOffGrid();
    }
  }
}

void getTemp() {
//  Serial.println(thermocouple.readInternal()); // sensor appears to have an additional internal temp sensor. neat
  currentTemp = thermocouple.readFahrenheit();
  if (isnan(currentTemp)) {
    Serial.println("Something wrong with thermocouple!");
  } else {
    Serial.print("F = ");
    Serial.println(currentTemp);

    if (tempAlarmState == false) {
      if (currentTemp > tempThresh) {
        handleTempAlarm();
      }
    } else {
      if (currentTemp < (tempThresh - tempHyst)) {
        handleTempDisAlarm();
      }
    }
  }
}

void handleTempAlarm() {
  Serial.println("Over temp!");
  tempAlarmState = true;
  disconnectAt();
  disconnectNsc();
}

void handleTempDisAlarm() {
  Serial.println("Resetting from overtemp state");
  tempAlarmState = false;
  connectAt();
  connectNsc();
}

void getAmps() {
  // TODO: implement method
//  Serial.println("Getting amps...");
  // TODO: null check from sensor
  if (ampsAlarmState == false) {
    if (currentAmps > ampsThresh) {
      handleAmpsAlarm();
    }
  } else {
    if (currentAmps < (ampsThresh - ampsHyst)) {
      handleAmpsDisAlarm();
    }
  }
}

void handleAmpsAlarm() {
  Serial.println("Over current!");
  ampsAlarmState = true;
  disconnectAt();
  disconnectNsc();
}

void handleAmpsDisAlarm() {
  Serial.println("Resetting from over current state");
  ampsAlarmState = false;
  connectAt();
  connectNsc();
}

void goOnGrid() {
  disconnectAt();
  connectNsc();
  cronLed.stop();
  ledUsb.off(); // TODO: remove for testing
  ledOn();
}

void goOffGrid() {
  connectAt();
  connectNsc();
  ledOff();
  ledUsb.blinky(); // TODO: remove for testing
  Serial.println("USB led state is: " + String(ledUsb.getState()));
  cronLed.start();
}

void connectAt() {
  if (!currentTemp) {
    Serial.println("Cannot turn on AT without a valid temp reading");
    return;
  }
  if (atsState) {
    Serial.println("Cannot turn on AT while GW is on-grid");
    return;
  }
  if (!atxState) {
    // TODO: flip AT relay pin ON
    Serial.println("Connecting AT relay");
    atxState = true;
    cronTempBoot.stop();
    cronGoOffGrid.stop();
  }
}

void disconnectAt() {
  if (atxState) {
    Serial.println("Disconnecting AT relay");
    // TODO: flip AT relay pin OFF
    atxState = false;
  } else {
    Serial.println("AT already disconnected");
  }
}

void connectNsc() {
  if (!nscState) {
    Serial.println("Connecting NSC");
    // TODO: flip NSC relay pin ON
    nscState = true; 
  } else {
    Serial.println("NSC already connected, doing nothing...");
  }
}

void disconnectNsc() {
  if (nscState) {
    Serial.println("Disonnecting NSC");
    // TODO: flip NSC relay pin OFF
    nscState = false;
  } else {
    Serial.println("NSC already disconnected, doing nothing...");
  }
}

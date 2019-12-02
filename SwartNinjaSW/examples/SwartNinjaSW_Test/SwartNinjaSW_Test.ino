#include <Arduino.h>
#include <SwartNinjaSW.h>

#define SWITCH_PIN 5 // D1 on nodemcu

// initialize the switch objects
SwartNinjaSW mySwitch(SIREN_PIN);

void setup()
{
  Serial.begin(115200);
  // switch setup
  mySwitch.setup();
}

void loop()
{
  // if the state changed it will setState will return true.
  if(mySwitch.setState(true)) {
    Serial.print("New Status:");
    Serial.println(mySwitch.getState());
  };

  delay(3000);

  if(mySwitch.setState(false)) {
    Serial.print("New Status:");
    Serial.println(mySwitch.getState());
  };
}
#include <Arduino.h>
#include <SwartNinjaPIR.h>

#define PIR_SENSOR_PIN 16 // D5 on nodemcu

///////////////////////////////////////////////////////////////////////////
//  SwartNinjaPIR
///////////////////////////////////////////////////////////////////////////
// function declaration
void handleSwartNinjaSensorUpdate(char *value, int pin, const char *event);
// initialize the SwartNinjaPIR object
SwartNinjaPIR motionSensor(PIR_SENSOR_PIN, handleSwartNinjaSensorUpdate);


///////////////////////////////////////////////////////////////////////////
//  MAIN SETUP AND LOOP
///////////////////////////////////////////////////////////////////////////
void setup()
{
  Serial.begin(115200);

  // motion sensor setup
  motionSensor.setup();
}

void loop()
{
  // motion sensor loop
  motionSensor.loop();
}

///////////////////////////////////////////////////////////////////////////
//  SwartNinjaPIR
///////////////////////////////////////////////////////////////////////////
void handleSwartNinjaSensorUpdate(char *value, int pin, const char *event)
{
  if (event == SN_PIR_SENSOR_EVT)
  {
    Serial.print("New value:");
    Serial.println(value);
  }
}
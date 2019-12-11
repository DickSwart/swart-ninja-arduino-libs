#include <Arduino.h>
#include <SwartNinjaDHT.h>

#define DHT_PIN 12 // D6 on nodemcu

///////////////////////////////////////////////////////////////////////////
//  SwartNinjaDHT
///////////////////////////////////////////////////////////////////////////
// function declaration
void handleSwartNinjaSensorUpdate(char *value, int pin, const char *event);
// initialize the SwartNinjaDHT object
SwartNinjaDHT dht(DHT_PIN, handleSwartNinjaSensorUpdate);


///////////////////////////////////////////////////////////////////////////
//  MAIN SETUP AND LOOP
///////////////////////////////////////////////////////////////////////////
void setup()
{
  Serial.begin(115200);

  // DHT sensor setup
  dht.setup();
}

void loop()
{
  // DHT sensor loop
  dht.loop();
}

///////////////////////////////////////////////////////////////////////////
//  SwartNinjaDHT
///////////////////////////////////////////////////////////////////////////
void handleSwartNinjaSensorUpdate(char *value, int pin, const char *event)
{
  if (event == SN_DHT_TEMPERATURE_EVT)
  {
    Serial.print("New temperature value:");
    Serial.println(value);
  }
  else if (event == SN_DHT_HUMIDITY_EVT)
  {
    Serial.print("New humidity value:");
    Serial.println(value);
  }
  else if (event == SN_DHT_REALFEEL_EVT)
  {
    Serial.print("New real feel value:");
    Serial.println(value);
  }
}
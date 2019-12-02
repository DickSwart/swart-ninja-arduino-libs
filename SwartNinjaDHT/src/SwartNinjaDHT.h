#ifndef SwartNinjaDHT_H
#define SwartNinjaDHT_H

#include "Arduino.h"
#include "DHT.h"

#define SNDHT_DEBUG_PRINTER Serial /**< Define where debug output will be printed. */

/* Setup debug printing macros. */
#ifdef SNDHT_DEBUG
  #define SNDHT_PRINT(...) { SNDHT_DEBUG_PRINTER.print(__VA_ARGS__); }
  #define SNDHT_PRINTLN(...) { SNDHT_DEBUG_PRINTER.println(__VA_ARGS__); }
#else
  #define SNDHT_PRINT(...) {} /**< Debug Print Placeholder if Debug is disabled */
  #define SNDHT_PRINTLN(...) {} /**< Debug Print Line Placeholder if Debug is disabled */
#endif

#define DHT_TEMPERATURE_OFFSET_VALUE 0.2 // < min temparature offset value [°C]
#define DHT_HUMIDITY_OFFSET_VALUE 0.5    // < min humidity offset value [%]
#define DHT_MEASURE_INTERVAL 30000       // < min interval value [ms]

/* Define events. */
#define SN_DHT_TEMPERATURE_EVT "SN_DHT_TEMPERATURE_EVT"
#define SN_DHT_HUMIDITY_EVT "SN_DHT_HUMIDITY_EVT"
#define SN_DHT_REALFEEL_EVT "SN_DHT_REALFEEL_EVT"

class SwartNinjaDHT : private DHT
{
public:
  SwartNinjaDHT(uint8_t pin, uint8_t type, void (*callback)(char *value, int pin, const char *event));
  // SwartNinjaDHT(uint8_t pin, uint8_t type, void (*callback)(uint8_t, float));
  void setup(void);
  void loop(void);
  float getTemperature(void);
  float getHumidity(void);
  float getRealFeel(void);
  uint8_t getPinNumber(void);

private:
  uint8_t _pin;
  void (*_callback)(char *, int , const char *);
  bool _checkBoundSensor(float newValue, float prevValue, float maxDiff);
  float _readTemperature(bool S=false, bool force=false);
  float _readRealFeel(bool isFahrenheit=false);
  float _readHumidity(bool force=false);
  float _realFeel = NAN;
  float _temperature = NAN;
  float _humidity = NAN;
};

#endif
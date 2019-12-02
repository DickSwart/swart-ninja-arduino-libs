#ifndef SwartNinjaLDR_H
#define SwartNinjaLDR_H

#include "Arduino.h"

#define SNLDR_DEBUG_PRINTER Serial /**< Define where debug output will be printed. */

/* Setup debug printing macros. */
#ifdef SNLDR_DEBUG
  #define SNLDR_PRINT(...) { SNLDR_DEBUG_PRINTER.print(__VA_ARGS__); }
  #define SNLDR_PRINTLN(...) { SNLDR_DEBUG_PRINTER.println(__VA_ARGS__); }
#else
  #define SNLDR_PRINT(...) {} /**< Debug Print Placeholder if Debug is disabled */
  #define SNLDR_PRINTLN(...) {} /**< Debug Print Line Placeholder if Debug is disabled */
#endif

#define LDR_MEASURE_INTERVAL 5000   // [ms]
#define REFERENCE_VOLTAGE 5         // [v]
#define ADC_PRECISION 1024.0        // 10 bits
#define LDR_RESISTOR_VALUE 10000.0  // [Ohms]
#define LDR_OFFSET_VALUE 25
#define SN_LDR_SENSOR_EVT "SN_LUX_SENSOR_EVT"

class SwartNinjaLDR
{
public:
  SwartNinjaLDR(int pin, void (*callback)(char * value, int pin, const char * event));
  void setup(void);
  void loop(void);
  uint16_t getCurrentValueInt(void);
  char * getCurrentValueChar(void);
  int getPinNumber(void);

private:
  int _pin;
  uint16_t _currentValue;
  void (*_callback)(char *, int, const char *);
  uint16_t _read(void);
  void _setCurrentValue(uint16_t value);
  bool _checkBoundSensor(float newValue, float prevValue, float maxDiff);
};

#endif
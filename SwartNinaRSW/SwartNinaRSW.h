#ifndef SwartNinaRSW_H
#define SwartNinaRSW_H

#include "Arduino.h"

#define SNRS_DEBUG_PRINTER Serial /**< Define where debug output will be printed. */

/* Setup debug printing macros. */
#ifdef SNRS_DEBUG
  #define SNRS_PRINT(...) { SNRS_DEBUG_PRINTER.print(__VA_ARGS__); }
  #define SNRS_PRINTLN(...) { SNRS_DEBUG_PRINTER.println(__VA_ARGS__); }
#else
  #define SNRS_PRINT(...) {} /**< Debug Print Placeholder if Debug is disabled */
  #define SNRS_PRINTLN(...) {} /**< Debug Print Line Placeholder if Debug is disabled */
#endif

#define SNRS_MEASURE_INTERVAL 500       // < min interval value [ms]
#define SN_RSW_SENSOR_EVT "SN_RSW_SENSOR_EVT"

class SwartNinaRSW
{
public:
  SwartNinaRSW(int pin, void (*callback)(char *value, int pin, const char *event), int pin_input_type = INPUT_PULLUP);
  void setup(void);
  void loop(void);
  char* getCurrentState(void);
  int getPinNumber(void);

private:
  int _pin;
  int _pin_input_type;
  bool _currentState;
  void (*_callback)(char *, int , const char *);
  bool _readState(void);
};

#endif
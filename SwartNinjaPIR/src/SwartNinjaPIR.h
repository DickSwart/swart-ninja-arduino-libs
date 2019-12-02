#ifndef SwartNinjaPIR_H
#define SwartNinjaPIR_H

#include "Arduino.h"

#define SNPIR_DEBUG_PRINTER Serial /**< Define where debug output will be printed. */

/* Setup debug printing macros. */
#ifdef SNPIR_DEBUG
  #define SNPIR_PRINT(...) { SNPIR_DEBUG_PRINTER.print(__VA_ARGS__); }
  #define SNPIR_PRINTLN(...) { SNPIR_DEBUG_PRINTER.println(__VA_ARGS__); }
#else
  #define SNPIR_PRINT(...) {} /**< Debug Print Placeholder if Debug is disabled */
  #define SNPIR_PRINTLN(...) {} /**< Debug Print Line Placeholder if Debug is disabled */
#endif

#define SN_PIR_SENSOR_EVT "SN_PIR_SENSOR_EVT"

class SwartNinjaPIR
{
public:
  SwartNinjaPIR(int pin, void (*callback)(char *value, int pin, const char *event));
  void setup(void);
  void loop(void);
  char * getState(void);
  int getPinNumber(void);

private:
  int _pin;
  bool _currentState;
  void (*_callback)(char *, int, const char *);
  void _motionSensorISR(void);
  bool _readMotionState(void);
  void _setMotionState(bool value);
};
#endif

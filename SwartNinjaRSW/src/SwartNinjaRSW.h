#pragma once
#ifndef SwartNinjaRSW_H
#define SwartNinjaRSW_H

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

#define SNRS_MEASURE_INTERVAL 500 // < min interval value [ms]
#define SN_RSW_SENSOR_EVT "SN_RSW_SENSOR_EVT"

class SwartNinjaRSW
{
public:
  SwartNinjaRSW(int pin, void (*callback)(char *value, int pin, const char *event), bool force_initial_callback = true, int pin_input_type = INPUT_PULLUP);
  void setup(void);
  void loop(void);
  char *getCurrentState(void);
  bool getCurrentRawState(void);
  int getPinNumber(void);

private:
  int _pin;
  int _pin_input_type;
  bool _currentState;
  bool _force_initial_callback;
  void (*_callback)(char *, int, const char *);
  bool _readState(void);
};

#endif
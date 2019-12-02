#ifndef SwartNinjaSW_H
#define SwartNinjaSW_H

#include "Arduino.h"

#define SNSW_DEBUG_PRINTER Serial /**< Define where debug output will be printed. */

/* Setup debug printing macros. */
#ifdef SNSW_DEBUG
  #define SNSW_PRINT(...) { SNSW_DEBUG_PRINTER.print(__VA_ARGS__); }
  #define SNSW_PRINTLN(...) { SNSW_DEBUG_PRINTER.println(__VA_ARGS__); }
#else
  #define SNSW_PRINT(...) {} /**< Debug Print Placeholder if Debug is disabled */
  #define SNSW_PRINTLN(...) {} /**< Debug Print Line Placeholder if Debug is disabled */
#endif

#define SNRS_MEASURE_INTERVAL 500       // < min interval value [ms]

class SwartNinjaSW
{
public:
  SwartNinjaSW(int);
  void setup(void);
  char* getState(void);
  bool getRawState(void);
  bool setState(bool);
  int getPinNumber(void);

private:
  int _pin;
  bool _currentState;
  void _setState(uint8_t);
};

#endif
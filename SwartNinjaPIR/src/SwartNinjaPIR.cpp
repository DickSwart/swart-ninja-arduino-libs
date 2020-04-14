//include the declaration for this class
#include "SwartNinjaPIR.h"

bool SwartNinjaPIRChanged = false;

//  ISRs
void ICACHE_RAM_ATTR motionSensorISR(void)
{
  SwartNinjaPIRChanged = true;
}

///////////////////////////////////////////////////////////////////////////
//  Constructor, init() & loop()
///////////////////////////////////////////////////////////////////////////
SwartNinjaPIR::SwartNinjaPIR(int pin, void (*callback)(char *value, int pin, const char *event))
{
  this->_pin = pin;
  this->_callback = callback;
}

void SwartNinjaPIR::setup(void)
{
  pinMode(this->_pin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(this->_pin), motionSensorISR, CHANGE);
  // set to the oposite of actual reading to force callback function to trigger.
  this->_setMotionState(!this->_readMotionState());

  SNPIR_PRINTLN("[SwartNinjaPIR]: Main setup");
}

void SwartNinjaPIR::loop(void)
{
  if (SwartNinjaPIRChanged)
  {
    SNPIR_PRINTLN("[SwartNinjaPIR]: SwartNinjaPIRChanged");

    bool currentState = _readMotionState();
    if (currentState != this->_currentState)
    {
      this->_setMotionState(currentState);

      char *value = strdup((currentState) ? "ON" : "OFF");
      this->_callback(value, this->getPinNumber(), SN_PIR_SENSOR_EVT);

      SNPIR_PRINT("[SwartNinjaPIR]: Event ");
      SNPIR_PRINT(SN_PIR_SENSOR_EVT);
      SNPIR_PRINT(" ( PIN: ");
      SNPIR_PRINT(this->getPinNumber());
      SNPIR_PRINT(" -> ");
      SNPIR_PRINT(value);
      SNPIR_PRINTLN(" )");
    }
    SwartNinjaPIRChanged = false;
  }
}

///////////////////////////////////////////////////////////////////////////
//  Getters
///////////////////////////////////////////////////////////////////////////
int SwartNinjaPIR::getPinNumber(void)
{
  return this->_pin;
}

char *SwartNinjaPIR::getState(void)
{
  char *value = strdup((this->getStateRaw()) ? "ON" : "OFF");
  return value;
}

bool SwartNinjaPIR::getStateRaw(void)
{
  return this->_currentState;
}

///////////////////////////////////////////////////////////////////////////
//  PRIVATE METHODS
///////////////////////////////////////////////////////////////////////////

// read the pin
bool SwartNinjaPIR::_readMotionState(void)
{
  return digitalRead(this->_pin);
}

// read the pin
void SwartNinjaPIR::_setMotionState(bool value)
{
  this->_currentState = value;
}
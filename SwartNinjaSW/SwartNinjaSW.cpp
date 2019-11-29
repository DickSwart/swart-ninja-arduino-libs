//include the declaration for this class
#include "SwartNinjaSW.h"

/*!
 *  @brief  Instantiates a new SwartNinjaSW class
 *  @param  pin
 *          pin number that sensor is connected
 *  @param  callback
 *          callback method
 */
SwartNinjaSW::SwartNinjaSW(int pin)
{
  this->_pin = pin;
}

///////////////////////////////////////////////////////////////////////////
//  Public methods
///////////////////////////////////////////////////////////////////////////


void SwartNinjaSW::setup(void)
{
  SNSW_PRINTLN("[SwartNinjaSW]: Main setup");
  
  pinMode(this->_pin, OUTPUT);
  SNSW_PRINT("[SwartNinjaSW]: Pin: ");
  SNSW_PRINTLN(this->_pin);

  this->setState(LOW);
  SNSW_PRINT("[SwartNinjaSW]: Current State: ");
  SNSW_PRINTLN(this->_currentState);
}

char * SwartNinjaSW::getState(void)
{
  return strdup((this->_currentState) ? "ON" : "OFF");
}

bool SwartNinjaSW::setState(bool state)
{
  SNSW_PRINT("[SwartNinjaSW]: NEW State: ");
  SNSW_PRINTLN(state);
  SNSW_PRINT("[SwartNinjaSW]: OLD State: ");
  SNSW_PRINTLN(this->_currentState);

  // checks if the given state is different from the actual state
  if (state == this->_currentState)
    return false;

  this->_setState(state);

  return true;
}

int SwartNinjaSW::getPinNumber(void)
{
  return this->_pin;
}

///////////////////////////////////////////////////////////////////////////
//  Private methods
///////////////////////////////////////////////////////////////////////////
void SwartNinjaSW::_setState(uint8_t state)
{
  // saves the new state value
  this->_currentState = state;

  if (this->_currentState == 1) {
    SNSW_PRINTLN("[SwartNinjaSW]: _setState: HIGH");
    digitalWrite(this->_pin, HIGH);
  } else {
    SNSW_PRINTLN("[SwartNinjaSW]: _setState: LOW");
    digitalWrite(this->_pin, LOW);
  }
}
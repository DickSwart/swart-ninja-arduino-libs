//include the declaration for this class
#include "SwartNinaRSW.h"

/*!
 *  @brief  Instantiates a new SwartNinaRSW class
 *  @param  pin
 *          pin number that sensor is connected
 *  @param  callback
 *          callback method
 */
SwartNinaRSW::SwartNinaRSW(int pin, void (*callback)(char *, int , const char *), int pin_input_type)
{
  this->_pin = pin;
  this->_pin_input_type = pin_input_type;
  this->_callback = callback;
}

///////////////////////////////////////////////////////////////////////////
//  Public methods
///////////////////////////////////////////////////////////////////////////


void SwartNinaRSW::setup(void)
{
  SNRS_PRINTLN("[SwartNinaRSW]: Main setup");
  
  pinMode(this->_pin, this->_pin_input_type);
  SNRS_PRINT("[SwartNinaRSW]: Pin: ");
  SNRS_PRINTLN(this->_pin);

  // set to the oposite of actual reading to force callback function to trigger.
  this->_currentState = !this->_readState();
}

//Setup the reed switch
void SwartNinaRSW::loop(void)
{

  static unsigned long lastSensorCheck = 0;
  if (lastSensorCheck + SNRS_MEASURE_INTERVAL <= millis())
  {
    lastSensorCheck = millis();

    bool newStatus = this->_readState();
    // Check if the value changed since last time
    // we checked
    if (newStatus != this->_currentState)
    {
      this->_currentState = newStatus;

      char *value = strdup((newStatus) ? "OFF" : "ON");
      this->_callback(value, this->getPinNumber(), SN_RSW_SENSOR_EVT);

      SNRS_PRINT("[SwartNinaRSW]: Event ");
      SNRS_PRINT(SN_RSW_SENSOR_EVT);
      SNRS_PRINT(" ( PIN: ");
      SNRS_PRINT(this->getPinNumber());
      SNRS_PRINT(" -> ");
      SNRS_PRINT(value);
      SNRS_PRINTLN(" )");
    }
  }
}

char* SwartNinaRSW::getCurrentState(void)
{
  return strdup((this->_currentState) ? "OFF" : "ON");
}

int SwartNinaRSW::getPinNumber(void)
{
  return this->_pin;
}

///////////////////////////////////////////////////////////////////////////
//  Private methods
///////////////////////////////////////////////////////////////////////////

bool SwartNinaRSW::_readState(void)
{
  return digitalRead(this->_pin);
}
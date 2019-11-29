//include the declaration for this class
#include "SwartNinjaLDR.h"

char buffer [sizeof(int)*8+1];

/*!
 *  @brief  Instantiates a new SwartNinjaLDR class
 *  @param  pin
 *          pin number that sensor is connected
 *  @param  callback
 *          callback method
 */
SwartNinjaLDR::SwartNinjaLDR(int pin, void (*callback)(char *, int, const char *))
{
  this->_pin = pin;
  this->_callback = callback;
}

///////////////////////////////////////////////////////////////////////////
//  Public methods
///////////////////////////////////////////////////////////////////////////


void SwartNinjaLDR::setup(void)
{
  SNLDR_PRINT("[SwartNinjaLDR]: Setup PIN: ");
  SNLDR_PRINTLN(this->_pin);

  pinMode(this->_pin, INPUT);
}

// Setup the photoresistor
void SwartNinjaLDR::loop(void)
{

  static unsigned long lastLdrSensorMeasure = 0;
  if (lastLdrSensorMeasure + LDR_MEASURE_INTERVAL <= millis())
  {
    lastLdrSensorMeasure = millis();
    uint16_t currentLdrValue = this->_read();
    if (_checkBoundSensor(currentLdrValue, this->getCurrentValueInt(), LDR_OFFSET_VALUE))
    {
      this->_setCurrentValue(currentLdrValue);
      this->_callback(this->getCurrentValueChar(), this->getPinNumber(), SN_LDR_SENSOR_EVT);

      SNLDR_PRINT("[SwartNinjaLDR]: Event ");
      SNLDR_PRINT(SN_LDR_SENSOR_EVT);
      SNLDR_PRINT(" ( PIN: ");
      SNLDR_PRINT(this->getPinNumber());
      SNLDR_PRINT(" -> ");
      SNLDR_PRINT(this->getCurrentValueChar());
      SNLDR_PRINTLN(" )");
    }
  }
}

char * SwartNinjaLDR::getCurrentValueChar(void)
{
  itoa (this->getCurrentValueInt(), buffer, 10);
  return buffer;
}

uint16_t SwartNinjaLDR::getCurrentValueInt(void)
{
  return this->_currentValue;
}

int SwartNinjaLDR::getPinNumber(void)
{
  return this->_pin;
}

///////////////////////////////////////////////////////////////////////////
//  Private methods
///////////////////////////////////////////////////////////////////////////

uint16_t SwartNinjaLDR::_read(void)
{
  // http://forum.arduino.cc/index.php?topic=37555.0
  // https://forum.arduino.cc/index.php?topic=185158.0
  float volts = analogRead(this->_pin) * (REFERENCE_VOLTAGE / ADC_PRECISION);
  float amps = volts / LDR_RESISTOR_VALUE;
  float lux = amps * 1000000 * 2.0;
  return uint16_t(lux);
}

void SwartNinjaLDR::_setCurrentValue(uint16_t value)
{
  this->_currentValue = value;
}

///////////////////////////////////////////////////////////////////////////
//  Helpers
///////////////////////////////////////////////////////////////////////////
bool SwartNinjaLDR::_checkBoundSensor(float newValue, float prevValue, float maxDiff)
{
  return isnan(prevValue) || newValue <= prevValue - maxDiff || newValue >= prevValue + maxDiff;
}
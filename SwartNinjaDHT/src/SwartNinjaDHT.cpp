//include the declaration for this class
#include "SwartNinjaDHT.h"
#include "DHT.h"

char PAYLOAD[8] = {0};

/*!
 *  @brief  Instantiates a new SwartNinjaDHT class
 *  @param  pin
 *          pin number that sensor is connected
 *  @param  type
 *          type of sensor
 *  @param  callback
 *          callback method
 */
SwartNinjaDHT::SwartNinjaDHT(uint8_t pin, uint8_t type, void (*callback)(char *, int, const char *)) : DHT(pin, type)
{
  this->_pin = pin;
  this->_callback = callback;
}

/*!
 *  @brief  Setup sensor pins and set pull timings
 */
void SwartNinjaDHT::setup(void)
{
  SNDHT_PRINTLN("[SwartNinjaDHT]: Main setup");
  // initialize base class.
  DHT::begin();
}

/*!
 *  @brief  Read temperature, Humidity and Real Feel in the main loop
 */
void SwartNinjaDHT::loop(void)
{
  static unsigned long lastTemperatureSensorMeasure = 0;
  if (lastTemperatureSensorMeasure + DHT_MEASURE_INTERVAL <= millis())
  {
    lastTemperatureSensorMeasure = millis();
    float currentTemperature = this->_readTemperature();
    if (_checkBoundSensor(currentTemperature, this->_temperature, DHT_TEMPERATURE_OFFSET_VALUE))
    {
      this->_temperature = currentTemperature;
      this->_callback(this->getTemperatureState(), this->getPinNumber(), SN_DHT_TEMPERATURE_EVT);
      SNDHT_PRINT("[SwartNinjaDHT]: Temperature = ");
      SNDHT_PRINTLN(this->_temperature);
    }
  }

  static unsigned long lastHumiditySensorMeasure = 0;
  if (lastHumiditySensorMeasure + DHT_MEASURE_INTERVAL <= millis())
  {
    lastHumiditySensorMeasure = millis();
    float currentHumidity = this->_readHumidity();
    if (_checkBoundSensor(currentHumidity, this->_humidity, DHT_HUMIDITY_OFFSET_VALUE))
    {
      this->_humidity = currentHumidity;
      this->_callback(this->getHumidityState(), this->getPinNumber(), SN_DHT_HUMIDITY_EVT);
      SNDHT_PRINT("[SwartNinjaDHT]: Humidity = ");
      SNDHT_PRINTLN(this->_humidity);
    }
  }

  static unsigned long lastRealFeelSensorMeasure = 0;
  if (lastRealFeelSensorMeasure + DHT_MEASURE_INTERVAL <= millis())
  {
    lastRealFeelSensorMeasure = millis();
    float currentRealFeel = this->_readRealFeel();
    if (_checkBoundSensor(currentRealFeel, this->_realFeel, DHT_TEMPERATURE_OFFSET_VALUE))
    {
      this->_realFeel = currentRealFeel;
      this->_callback(this->getRealFeelState(), this->getPinNumber(), SN_DHT_REALFEEL_EVT);
      SNDHT_PRINT("[SwartNinjaDHT]: Real Feel = ");
      SNDHT_PRINTLN(this->_realFeel);
    }
  }
}

char *SwartNinjaDHT::getTemperatureState(void)
{
  dtostrf(this->_readTemperature(), 2, 2, PAYLOAD);
  return PAYLOAD;
}
char *SwartNinjaDHT::getHumidityState(void)
{
  dtostrf(this->_readHumidity(), 2, 2, PAYLOAD);
  return PAYLOAD;
}
char *SwartNinjaDHT::getRealFeelState(void)
{
  dtostrf(this->_readRealFeel(), 2, 2, PAYLOAD);
  return PAYLOAD;
}

float SwartNinjaDHT::getTemperature(void)
{
  return this->_temperature;
}

float SwartNinjaDHT::getHumidity(void)
{
  return this->_humidity;
}
float SwartNinjaDHT::getRealFeel(void)
{
  return this->_realFeel;
}

uint8_t SwartNinjaDHT::getPinNumber(void)
{
  return this->_pin;
}

///////////////////////////////////////////////////////////////////////////
//  Private Methods
///////////////////////////////////////////////////////////////////////////

float SwartNinjaDHT::_readTemperature(bool S, bool force)
{
  float temperature = DHT::readTemperature(S, force);
  if (isnan(temperature))
  {
    return this->_temperature;
  }
  return temperature;
}

float SwartNinjaDHT::_readRealFeel(bool isFahrenheit)
{
  float realFeel = DHT::computeHeatIndex(isFahrenheit);
  if (isnan(realFeel))
  {
    return this->_realFeel;
  }
  return realFeel;
}

float SwartNinjaDHT::_readHumidity(bool force)
{
  float humidity = DHT::readHumidity(force);
  if (isnan(humidity))
  {
    return this->_humidity;
  }
  return humidity;
}

bool SwartNinjaDHT::_checkBoundSensor(float newValue, float prevValue, float maxDiff)
{
  return isnan(prevValue) || newValue <= prevValue - maxDiff || newValue >= prevValue + maxDiff;
}
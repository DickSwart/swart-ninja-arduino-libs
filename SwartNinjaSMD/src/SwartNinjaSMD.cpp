#include "Arduino.h"
#include "SwartNinjaSMD.h"

///////////////////////////////////////////////////////////////////////////
//  Constructors
///////////////////////////////////////////////////////////////////////////

/*!
 *  @brief  Instantiates a new SwartNinjaSMD class
 *  @param  mode
 *          Defines the micro step mode
 *  @param  dirPin
 *          Direction pin number
 *  @param  pulPin
 *          Pulse pin number
 *  @param  speedRPM
 *          (optional) Speed in RPM, rotations per minute
 */
SwartNinjaSMD::SwartNinjaSMD(SwartNinjaSMDMode mode, int dirPin, int pulPin, int enaPin)
{
  this->_dirPin = dirPin;
  this->_pulPin = pulPin;
  this->_enaPin = enaPin;
  this->setMicroStepMode(mode);

  pinMode(this->_dirPin, OUTPUT);
  pinMode(this->_pulPin, OUTPUT);
  pinMode(this->_enaPin, OUTPUT);

  this->_stepDelay = 0;
}

/*!
 *  @brief  Instantiates a new SwartNinjaSMD class
 *  @param  mode
 *          Defines the micro step mode
 *  @param  dirPin
 *          Direction pin number
 *  @param  pulPin
 *          Pulse pin number
 *  @param  speedRPM
 *          (optional) Speed in RPM, rotations per minute
 */
SwartNinjaSMD::SwartNinjaSMD(SwartNinjaSMDMode mode, int dirPin, int pulPin, int enaPin, int speedRPM)
{
  this->_dirPin = dirPin;
  this->_pulPin = pulPin;
  this->_enaPin = enaPin;
  this->setMicroStepMode(mode);

  pinMode(this->_dirPin, OUTPUT);
  pinMode(this->_pulPin, OUTPUT);
  pinMode(this->_enaPin, OUTPUT);

  setDelayRPM(speedRPM);
}

///////////////////////////////////////////////////////////////////////////
//  Public methods
///////////////////////////////////////////////////////////////////////////

void SwartNinjaSMD::setDelayRPM(int rpm)
{
  long delay = 60L * 1000000L / (rpm * this->_resolution * this->_steppingFactor);
  this->_stepDelay = (delay < 0) ? 0 : delay;
}

void SwartNinjaSMD::enableDriver()
{
  setEnable(LOW);
}

void SwartNinjaSMD::disableDriver()
{
  setEnable(HIGH);
}

void SwartNinjaSMD::move(int numberOfSteps)
{
  int steps = abs(numberOfSteps);

  if (numberOfSteps > 0)
  {
    setDirection(FORWARD);
  }
  else if (numberOfSteps < 0)
  {
    setDirection(BACKWARD);
  }

  while (steps > 0)
  {
    if (micros() - this->_lastStepTime >= this->_stepDelay)
    {
      this->_lastStepTime = micros();
      steps--;
      stepMotor();
    }
  }
}

void SwartNinjaSMD::move(int numberOfSteps, boolean direction)
{
  int steps = abs(numberOfSteps);
  setDirection(direction);

  while (steps > 0)
  {
    if (micros() - this->_lastStepTime >= this->_stepDelay)
    {
      this->_lastStepTime = micros();
      steps--;
      stepMotor();
    }
  }
}

void SwartNinjaSMD::rotate(float degrees)
{

  int stepsToMove = (int)((degrees * this->_resolution * this->_steppingFactor) / 360);
  move(stepsToMove);
}

void SwartNinjaSMD::revolve(float times)
{

  int stepsToMove = (int)(times * this->_resolution * this->_steppingFactor);
  move(stepsToMove);
}

///////////////////////////////////////////////////////////////////////////
//  Private methods
///////////////////////////////////////////////////////////////////////////
void SwartNinjaSMD::setMicroStepMode(SwartNinjaSMDMode mode)
{

  switch (mode)
  {
  case SwartNinjaSMDMode::TB6600_one:
    this->_steppingFactor = 1;
    this->_resolution = 200;
    break;
  case SwartNinjaSMDMode::TB6600_twoA:
  case SwartNinjaSMDMode::TB6600_twoB:
    this->_steppingFactor = 2;
    this->_resolution = 200;
    break;
  case SwartNinjaSMDMode::TB6600_four:
    this->_steppingFactor = 4;
    this->_resolution = 200;
    break;
  case SwartNinjaSMDMode::TB6600_eight:
    this->_steppingFactor = 8;
    this->_resolution = 200;
    break;
  case SwartNinjaSMDMode::TB6600_sixteen:
    this->_steppingFactor = 16;
    this->_resolution = 200;
    break;
  case SwartNinjaSMDMode::TB6600_thirtyTwo:
    this->_steppingFactor = 32;
    this->_resolution = 200;
    break;
  default:
    this->_steppingFactor = 1;
    this->_resolution = 200;
  }
}

void SwartNinjaSMD::stepMotor()
{
  digitalWrite(this->_pulPin, HIGH);
  digitalWrite(this->_pulPin, LOW);
}

void SwartNinjaSMD::setDirection(boolean direction)
{
  digitalWrite(this->_dirPin, direction);
  delayMicroseconds(100);
}

void SwartNinjaSMD::setEnable(boolean value)
{
  digitalWrite(this->_enaPin, value);
  delayMicroseconds(100);
}

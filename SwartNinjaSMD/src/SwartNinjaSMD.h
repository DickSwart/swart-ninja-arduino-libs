#ifndef SwartNinjaSMD_H
#define SwartNinjaSMD_H

#include "Arduino.h"

#define FORWARD true
#define BACKWARD false

enum SwartNinjaSMDMode
{
  TB6600_one,
  TB6600_twoA,
  TB6600_twoB,
  TB6600_four,
  TB6600_eight,
  TB6600_sixteen,
  TB6600_thirtyTwo
};

class SwartNinjaSMD
{
public:
  SwartNinjaSMD(SwartNinjaSMDMode mode, int dirPin, int pulPin, int enaPin);
  SwartNinjaSMD(SwartNinjaSMDMode mode, int dirPin, int pulPin, int enaPin, int speedRPM);

  void setDelayRPM(int rpm);

  void enableDriver();
  void disableDriver();

  void move(int numberOfSteps);
  void move(int numberOfSteps, boolean direction);
  void rotate(float degrees);
  void revolve(float times);

private:
  void setMicroStepMode(SwartNinjaSMDMode mode);
  void stepMotor();
  void setDirection(boolean direction);
  void setEnable(boolean value);

  unsigned long _stepDelay;
  long _lastStepTime;

  int _resolution;
  int _steppingFactor;

  int _dirPin;
  int _pulPin;
  int _enaPin;
};

#endif

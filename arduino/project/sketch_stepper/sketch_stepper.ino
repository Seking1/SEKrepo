#include <Stepper.h>

const int STEPS_PER_ROTOR_REV = 32;
const int GEAR_REDUCTION = 64;
const int STEPS_PER_REVOLUTION = STEPS_PER_ROTOR_REV * GEAR_REDUCTION;
int StepsRequired = 2048;
Stepper steppermotor(STEPS_PER_ROTOR_REV, D5, D7, D6, D8);  // IN1, IN3, IN2, IN4

void setup()
{
  Serial.begin(9600);
  steppermotor.setSpeed(800);
}

void loop()
{
  StepsRequired  =  512;
  Serial.println(StepsRequired);
  steppermotor.step(StepsRequired);
  yield();
  steppermotor.step(StepsRequired);
delay(1000);
}

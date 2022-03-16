
#ifndef MOTOR_H
#define MOTOR_H
#include "Config.h"
#include "Pins.h"
#include <Arduino.h>
#include <TMCStepper.h>
class Motor
{
private:
    TMC2130Stepper stepper = TMC2130Stepper(CS_PIN,R_SENSE);
public:
    Motor(/* args */);
    void configure();
    void drive(double,bool);
    void setSpeed(double);  
    int motorSpeed;
};

#endif
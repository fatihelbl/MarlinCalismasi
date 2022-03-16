#include "Motor.h"

Motor::Motor(/* args */)
{
    pinMode(EN_PIN, OUTPUT);
    pinMode(DIR_PIN, OUTPUT);
    pinMode(STEP_PIN, OUTPUT);
    pinMode(CS_PIN, OUTPUT);
    digitalWrite(EN_PIN, LOW);
    motorSpeed = DEFAULT_PRINT_SPEED;
}

void Motor::configure()
{
    stepper.begin();
    stepper.microsteps(8);
    stepper.en_pwm_mode(true);
    stepper.pwm_autoscale(true);
    stepper.toff(5);
    stepper.rms_current(RMS_CURRENT);
}

void Motor ::drive(double distance, bool check)
{
    digitalWrite(EN_PIN, LOW);
    if (distance > 0)
    {
        digitalWrite(DIR_PIN, HIGH);
    }
    else
    {
        digitalWrite(DIR_PIN, LOW);
    }
    for (unsigned long i = 0; i < round(STEPS_PER_MM * distance); i++)
    {
        if (check)
        {
            if (digitalRead(LIMIT_SWITCH_PIN) == HIGH)
            {
                break;
            }
        }

        digitalWrite(STEP_PIN, HIGH);
        delayMicroseconds(motorSpeed);
        digitalWrite(STEP_PIN, LOW);
        delayMicroseconds(motorSpeed);
        /* port manipulation
        PORTD |= B01000000; // digitalWrite(STEP_PIN, LOW);
        delayMicroseconds(motorSpeed);
        PORTD &= B10111111;
        delayMicroseconds(motorSpeed); // digitalWrite(STEP_PIN, HIGH);
        */
    }
}
void Motor::setSpeed(double speed)
{
    motorSpeed = speed;
}
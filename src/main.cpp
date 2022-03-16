#include "Motor/Motor.h"
#include <GCode/queue.h>
#include <RingBuffer/RingBuffer.h>
Motor iMotor;
GCodeQueue iController(iMotor);

void setup()
{
  Serial.begin(115200);
  Serial1.begin(115200);
  iMotor.configure();
}

void loop()
{
  
  iController.get_serial_commands();
}

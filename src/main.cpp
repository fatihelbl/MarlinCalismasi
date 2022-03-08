
#include <GCode/queue.h>
#include <RingBuffer/RingBuffer.h>
GCodeQueue queue;


void setup()
{
  Serial.begin(115200);
  Serial1.begin(115200);
}

void loop()
{
  queue.get_serial_commands();
}

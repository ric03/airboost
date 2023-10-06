#include <Arduino.h>
#include "scd30.h"

#define LOOP_DEPLAY 250

void setup()
{
  Serial.begin(115200);
  while (!Serial)
    delay(10); // will pause until serial console opens, use the RESET button to start monitoring

  scd30::setup();
}

void loop()
{
  scd30::Data *data = scd30::readData();
  if (data)
  {
    scd30::printSerial(data);
  }

  delay(LOOP_DEPLAY);
}

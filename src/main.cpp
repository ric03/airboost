#include <Arduino.h>
#include "scd30.h"

#define SCD30_ENABLED true
#define LOOP_DEPLAY 250

void setup()
{
  Serial.begin(115200);
  while (!Serial)
    delay(10); // will pause until serial console opens, use the RESET button to start monitoring

#if SCD30_ENABLED == true
  scd30::setup();
#endif
}

void loop()
{
#if SCD30_ENABLED == true
  scd30::Data *data = scd30::readData();
  if (data)
  {
    scd30::printSerial(data);
  }
#endif

  delay(LOOP_DEPLAY);
}

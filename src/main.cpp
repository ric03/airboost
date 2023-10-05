#include <Arduino.h>
#include "scd30.h"

// put function declarations here:

void setup()
{
  Serial.begin(115200);
  while (!Serial)
    delay(10); // will pause until serial console opens, use the RESET button to start monitoring

  setupSDC30();
}

void loop()
{
  Adafruit_SCD30_Data *data = readScd30Data();
  if (data)
  {
    printScd30Data(data);
  }

  delay(100);
}

// put function definitions here:

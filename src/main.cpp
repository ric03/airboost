#include <Arduino.h>
#include "scd30.h"

// put function declarations here:

void setup()
{

  Serial.begin(115200);
  setupSDC30();

  while (!Serial)
    delay(10); // will pause until serial console opens, use the RESET button to start monitoring
}

void loop()
{
  readScd30Data();
  delay(100);
}

// put function definitions here:

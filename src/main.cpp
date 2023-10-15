#include <Arduino.h>
#include "scd30.h"
#include "oled_display_sh1106.h"
#include "display_service.h"

#define LOOP_DEPLAY 250

void setup()
{
  Serial.begin(115200);
  while (!Serial)
    delay(10); // will pause until serial console opens, use the RESET button to start monitoring

  scd30::setup();
  display::setup();
}

void loop()
{
  scd30::Data *data = scd30::readData();
  if (data)
  {
    scd30::printSerial(data);
    display_service::displaySCD30Data(data);
  }

  delay(LOOP_DEPLAY);
}

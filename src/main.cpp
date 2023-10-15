#include <Arduino.h>
#include "sensor_scd30.h"
#include "oled_display_sh1106.h"
#include "display_service.h"

#define LOOP_DEPLAY 250

void setup()
{
  Serial.begin(115200);
  while (!Serial)
    delay(10); // will pause until serial console opens, use the RESET button to start monitoring

  sensor_scd30::setup();
  display::setup();
}

void loop()
{
  sensor_scd30::SensorData *data = sensor_scd30::readData();
  if (data)
  {
    sensor_scd30::printSerial(data);
    display_service::displaySCD30Data(data);
  }

  delay(LOOP_DEPLAY);
}

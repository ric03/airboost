#include <Arduino.h>

#include "components/sensor_scd30.h"
#include "components/oled_display_sh1106.h"
#include "components/traffic_light.h"
#include "traffic_light_service.h"
#include "components/button.h"
#include "components/buzzer.h"

#include "view_service.h"

#define LOOP_DEPLAY 250

void setup()
{
  Serial.begin(115200);
  while (!Serial)
    delay(10); // will pause until serial console opens, use the RESET button to start monitoring

  sensor_scd30::setup();
  display::setup();
  traffic_light::setup();
  button::setup();
  buzzer::setup();
}

void loop()
{
  Serial.println();

  sensor_scd30::updateDataWithInterval();
  sensor_scd30::SensorData *data = &sensor_scd30::sensorData;
  sensor_scd30::printSerial(data);

  // traffic light
  auto light = traffic_light_service::getMatchingLight(data->CO2);
  traffic_light::changeLight(light);
  traffic_light::printSerial();

  // buzzer
  if (data->CO2 > 1100)
  {
    buzzer::playWarning();
  }

  view::viewService.render(data);

  delay(LOOP_DEPLAY);
}

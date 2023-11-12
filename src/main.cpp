#include <Arduino.h>

#include "sensor_scd30.h"
#include "oled_display_sh1106.h"
#include "traffic_light.h"
#include "traffic_light_service.h"
#include "button.h"
#include "buzzer.h"

#include "views/view_controller.h"

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
  buzzer::playTone();
}

void loop()
{
  sensor_scd30::SensorData *data = sensor_scd30::readData();
  if (data)
  {
    traffic_light_service::updateLight(data);
    traffic_light::printSerial();

    sensor_scd30::printSerial(data);
    Serial.println();

    view::viewController.render(data);
  }

  delay(LOOP_DEPLAY);
}

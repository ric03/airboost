#include <Arduino.h>

#include "components/sensor_scd30.h"
#include "components/oled_display_sh1106.h"
#include "components/traffic_light.h"
#include "components/button.h"
#include "components/buzzer.h"

#include "view_service.h"

#define LOOP_DEPLAY 250

void setup()
{
  Serial.begin(115200);
  while (!Serial)
    delay(10); // will pause until serial console opens, use the RESET button to start monitoring

  display::setup();
  display::printWelcomeMessage();

  sensor_scd30::setup();
  sensor_scd30::waitUntilDataReady();

  traffic_light::setup();
  traffic_light::powerOnSelfTest();

  buzzer::setup();
  buzzer::playWelcomeTone();

  button::setup();
}

void loop()
{
  const auto *data = &sensor_scd30::sensorData;
  auto now = millis();

  // variable to keep track of the timing of recent update
  static unsigned long last_update_time = 0;
  if (now - last_update_time > 2500 /*ms*/)
  {
    last_update_time = now;

    sensor_scd30::updateData();
    traffic_light::updateLight(data->CO2);

    Serial.println();
    sensor_scd30::printSerial();
    traffic_light::printSerial();
  }

  static unsigned long last_buzzer_time = 0;
  if (now - last_buzzer_time > 10000 /*ms*/)
  {
    last_buzzer_time = now;

    if (data->CO2 > 1100)
    {
      buzzer::playWarning();
    }
  }

  view::viewService.render(data);

  delay(LOOP_DEPLAY);
}

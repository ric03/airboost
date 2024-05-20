#include <Arduino.h>

#include "components/sensor_scd30.h"
#include "components/oled_display_sh1106.h"
#include "components/light_indicator.h"
#include "components/button.h"
#include "components/buzzer.h"
#include "views/view_service.h"
#include "interrupt_flags.h"

void setup()
{
  Serial.begin(115200);

#if defined(WAIT_FOR_SERIAL_MONITOR)
  // Requires active monitoring, use the RESET button to start monitoring
  // will wait until serial console opens
  while (!Serial)
    delay(10);
#endif

  display::setup();
  display::printWelcomeMessage();

  sensor_scd30::setup();
  sensor_scd30::waitUntilDataReady();

  light_indicator::setup();
  light_indicator::powerOnSelfTest();

  buzzer::setup();
  buzzer::playWelcomeTone();

  button::setup();
}

void loop()
{
  auto now = millis();

  // variable to keep track of the timing of recent update
  static unsigned long last_update_time = 0;
  if (now - last_update_time > 2500 /*ms*/)
  {
    last_update_time = now;

    sensor_scd30::updateData();
    light_indicator::updateLight(sensor_scd30::sensorData.CO2);

    Serial.println();
    sensor_scd30::printSerial();
    light_indicator::printSerial();

    updateViewImmediatly = false;
    view::viewService.render();
  }

  // Play a warning 'buzz' every 10sec if co2 > 1100 ppm
  static unsigned long last_buzzer_time = 0;
  if ((sensor_scd30::sensorData.CO2 > 1100 /*ppm*/) && (now - last_buzzer_time > 10000 /*ms*/))
  {
    last_buzzer_time = now;

    buzzer::playWarning();
  }

  /**
   * The flag is updated by an ISR when a button is pressed.
   * This will update the display immediatly, and is not bound to any other condition.
   * Otherwise the view is updated only every ~2.5sec, which feels very laggy
   */
  if (updateViewImmediatly)
  {
    updateViewImmediatly = false;
    view::viewService.render();
  }

  delay(250);
}

#pragma once

#include <Arduino.h>
#include <Adafruit_SCD30.h>

namespace sensor_scd30
{

    Adafruit_SCD30 scd30;

    struct SensorData
    {
        float temperature = 0;
        float CO2 = 0;
        float relative_humidity = 0;
    } sensorData;

    void setup()
    {

        Serial.println("Adafruit SCD30 Sensor adjustment test!");
        Serial.println("Attempting to find SCD30 chip (CO2-Sensor)");

        if (!scd30.begin())
        {
            Serial.println("Failed to find SCD30 chip");
            while (1)
            {
                delay(10);
            }
        }
        Serial.println("Success. SCD30 Found!");

        /***
         * The code below will report the current settings for each of the
         * settings that can be changed. To see how they work, uncomment the setting
         * code above a status message and adjust the value
         *
         * **Note:** Since Automatic self calibration and forcing recalibration with
         * a reference value overwrite each other, you should only set one or the other
         ***/

        /*** Adjust the rate at which measurements are taken, from 2-1800 seconds */
        // if (!scd30.setMeasurementInterval(5)) {
        //   Serial.println("Failed to set measurement interval");
        //   while(1){ delay(10);}
        // }
        Serial.print("Measurement interval: ");
        Serial.print(scd30.getMeasurementInterval());
        Serial.println(" seconds");

        /*** Restart continuous measurement with a pressure offset from 700 to 1400 millibar.
         * Giving no argument or setting the offset to 0 will disable offset correction
         */
        // if (!scd30.startContinuousMeasurement(15)){
        //   Serial.println("Failed to set ambient pressure offset");
        //   while(1){ delay(10);}
        // }
        Serial.print("Ambient pressure offset: ");
        Serial.print(scd30.getAmbientPressureOffset());
        Serial.println(" mBar");

        /*** Set an altitude offset in meters above sea level.
         * Offset value stored in non-volatile memory of SCD30.
         * Setting an altitude offset will override any pressure offset.
         */
        // if (!scd30.setAltitudeOffset(110)){
        //   Serial.println("Failed to set altitude offset");
        //   while(1){ delay(10);}
        // }
        Serial.print("Altitude offset: ");
        Serial.print(scd30.getAltitudeOffset());
        Serial.println(" meters");

        /*** Set a temperature offset in hundredths of a degree celcius.
         * Offset value stored in non-volatile memory of SCD30.
         */
        // if (!scd30.setTemperatureOffset(1984)){ // 19.84 degrees celcius
        //   Serial.println("Failed to set temperature offset");
        //   while(1){ delay(10);}
        // }
        Serial.print("Temperature offset: ");
        Serial.print((float)scd30.getTemperatureOffset() / 100.0);
        Serial.println(" degrees C");

        /*** Force the sensor to recalibrate with the given reference value
         * from 400-2000 ppm. Writing a recalibration reference will overwrite
         * any previous self calibration values.
         * Reference value stored in non-volatile memory of SCD30.
         */
        // if (!scd30.forceRecalibrationWithReference(400)){
        //   Serial.println("Failed to force recalibration with reference");
        //   while(1) { delay(10); }
        // }
        Serial.print("Forced Recalibration reference: ");
        Serial.print(scd30.getForcedCalibrationReference());
        Serial.println(" ppm");

        /*** Enable or disable automatic self calibration (ASC).
         * Parameter stored in non-volatile memory of SCD30.
         * Enabling self calibration will override any previously set
         * forced calibration value.
         * ASC needs continuous operation with at least 1 hour
         * 400ppm CO2 concentration daily.
         */
        // if (!scd30.selfCalibrationEnabled(true)){
        //   Serial.println("Failed to enable or disable self calibration");
        //   while(1) { delay(10); }
        // }
        if (scd30.selfCalibrationEnabled())
        {
            Serial.print("Self calibration enabled");
        }
        else
        {
            Serial.print("Self calibration disabled");
        }

        Serial.println("\n\n");
    }

    /**
     * Reading the data takes some time
     */
    void updateData()
    {
        if (scd30.dataReady() && scd30.read())
        {
            sensorData.temperature = scd30.temperature;
            sensorData.CO2 = scd30.CO2;
            sensorData.relative_humidity = scd30.relative_humidity;
        }
    }

    void updateDataWithInterval()
    {
        // variable to keep track of the timing of recent update
        static unsigned long last_update_time = 0;
        const unsigned long INTERVAL_MS = 2500;

        auto now = millis();
        if (now - last_update_time > INTERVAL_MS)
        {
            last_update_time = now;
            updateData();
        }
    }

    void printSerial(SensorData *data)
    {
        if (!data)
        {
            Serial.println("Error reading sensor data");
            return;
        }

        Serial.print("Temperature: ");
        Serial.print(data->temperature);
        Serial.println(" °C");

        Serial.print("Relative Humidity: ");
        Serial.print(data->relative_humidity);
        Serial.println(" %");

        Serial.print("CO2: ");
        Serial.print(data->CO2, 3);
        Serial.println(" ppm");
    }

}

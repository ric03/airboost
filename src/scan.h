#include <Arduino.h>
#include <Wire.h>

#define SDA1 21
#define SCL1 22

#define SDA2 17
#define SCL2 16

TwoWire I2Cone = TwoWire(0);
TwoWire I2Ctwo = TwoWire(1);

void scan1()
{
    Serial.println("Scanning I2C Addresses Channel 1");
    uint8_t cnt = 0;
    for (uint8_t i = 0; i < 128; i++)
    {
        I2Cone.beginTransmission(i);
        uint8_t ec = I2Cone.endTransmission(true);
        if (ec == 0)
        {
            if (i < 16)
                Serial.print('0');
            Serial.print(i, HEX);
            cnt++;
        }
        else
            Serial.print("..");
        Serial.print(' ');
        if ((i & 0x0f) == 0x0f)
            Serial.println();
    }
    Serial.print("Scan Completed, ");
    Serial.print(cnt);
    Serial.println(" I2C Devices found.");
}

void scan2()
{
    Serial.println("Scanning I2C Addresses Channel 2");
    uint8_t cnt = 0;
    for (uint8_t i = 0; i < 128; i++)
    {
        I2Ctwo.beginTransmission(i);
        uint8_t ec = I2Ctwo.endTransmission(true);
        if (ec == 0)
        {
            if (i < 16)
                Serial.print('0');
            Serial.print(i, HEX);
            cnt++;
        }
        else
            Serial.print("..");
        Serial.print(' ');
        if ((i & 0x0f) == 0x0f)
            Serial.println();
    }
    Serial.print("Scan Completed, ");
    Serial.print(cnt);
    Serial.println(" I2C Devices found.");
}

void setupI2C()
{
    Serial.begin(115200);
    I2Cone.begin(SDA1, SCL1, 400000); // SDA pin 21, SCL pin 22 TTGO TQ
    I2Ctwo.begin(SDA2, SCL2, 400000); // SDA2 pin 17, SCL2 pin 16
}

void loopI2C()
{
    scan1();
    Serial.println();
    delay(100);
    scan2();
    Serial.println();
    delay(5000);
}

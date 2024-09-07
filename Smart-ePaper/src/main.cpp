#include <Arduino.h>

// base class GxEPD2_GFX can be used to pass references or pointers to the display instance as parameter, uses ~1.2k more code
// enable or disable GxEPD2_GFX base class
#define ENABLE_GxEPD2_GFX 0

#include <U8g2_for_Adafruit_GFX.h>
#include <GxEPD2_BW.h>
#include <Fonts/FreeMonoBold9pt7b.h>

#include "GB2312.h"
#include "BaseDisplay.h"

// wiring for ESP32 S3
// SS/CS 10 MOSI/SDA 11 MISO 13 SCK/SCL 12
GxEPD2_BW<GxEPD2_154_D67, GxEPD2_154_D67::HEIGHT> display(GxEPD2_154_D67(/*CS=10*/ 10, /*DC=*/ 8, /*RST=*/ 7, /*BUSY=*/ 9));

// GB2312
extern const uint8_t gb2312[239032] U8G2_FONT_SECTION("gb2312");
U8G2_FOR_ADAFRUIT_GFX u8g2dp;

void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println("setup");
  delay(100);
  display.init(115200);
  u8g2dp.begin(display);


  helloWorld();
  delay(1000);
  helloWorld_GB2312();
  delay(1000);
  helloWorld_PartialMode();
  delay(1000);
  helloWorld_GB2312_PartialMode();
  delay(1000);
  clearScreen();
  delay(1000);


  Serial.println("setup done");
  display.end();
}

void loop()
{
}

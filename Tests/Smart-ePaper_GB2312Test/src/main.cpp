#include <Arduino.h>

// base class GxEPD2_GFX can be used to pass references or pointers to the display instance as parameter, uses ~1.2k more code
// enable or disable GxEPD2_GFX base class
#define ENABLE_GxEPD2_GFX 0

#include <U8g2_for_Adafruit_GFX.h>
#include <GxEPD2_BW.h>
#include <Fonts/FreeMonoBold9pt7b.h>

#include "GB2312.h"

// wiring for ESP32 S3
// SS/CS 10 MOSI/SDA 11 MISO 13 SCK/SCL 12
GxEPD2_BW<GxEPD2_154_D67, GxEPD2_154_D67::HEIGHT> display(GxEPD2_154_D67(/*CS=10*/ 10, /*DC=*/ 8, /*RST=*/ 7, /*BUSY=*/ 9));

// GB2312
extern const uint8_t gb2312[239032] U8G2_FONT_SECTION("gb2312");
U8G2_FOR_ADAFRUIT_GFX u8g2dp;

void helloWorld_GB2312();
void displayCenterFullWindow(const char *str);
void clearScreen();

void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println("setup");
  delay(100);
  display.init(115200);
  u8g2dp.begin(display);

  displayCenterFullWindow("Hello World!");
  delay(1000);
  helloWorld_GB2312();
  delay(3000);
  clearScreen();
  delay(1000);


  Serial.println("setup done");
  display.end();
}

void loop()
{
}

void helloWorld_GB2312()
{
  Serial.println("helloWorld_GB2312");
  display.setRotation(0);
  display.setFullWindow();
  u8g2dp.setFont(gb2312);
  u8g2dp.setForegroundColor(GxEPD_BLACK);
  u8g2dp.setBackgroundColor(GxEPD_WHITE);

  display.firstPage();
  do
  {
    u8g2dp.setCursor(65, 90);
    u8g2dp.println("你好，世界！");
  }
  while (display.nextPage());
  Serial.println("helloWorld_GB2312 done");
}

void displayCenterFullWindow(const char *str)
{
  Serial.println("displayCenterFullWindow");
  display.setRotation(0);
  display.setFont(&FreeMonoBold9pt7b);
  display.setTextColor(GxEPD_BLACK);
  int16_t tbx, tby; uint16_t tbw, tbh;
  display.getTextBounds(str, 0, 0, &tbx, &tby, &tbw, &tbh);
  // center bounding box by transposition of origin:
  uint16_t x = ((display.width() - tbw) / 2) - tbx;
  uint16_t y = ((display.height() - tbh) / 2) - tby;
  display.setFullWindow();

  display.firstPage();
  do
  {
    display.fillScreen(GxEPD_WHITE);
    display.setCursor(x, y);
    display.print(str);
  }
  while (display.nextPage());
  Serial.println("displayCenterFullWindow done");
}

void clearScreen()
{
  Serial.println("clearScreen");
  display.setRotation(0);
  display.setFullWindow();

  display.firstPage();
  do
  {
    display.fillScreen(GxEPD_WHITE);
  }
  while (display.nextPage());
  Serial.println("clearScreen done");
}

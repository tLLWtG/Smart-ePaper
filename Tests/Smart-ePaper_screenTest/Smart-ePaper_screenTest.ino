// base class GxEPD2_GFX can be used to pass references or pointers to the display instance as parameter, uses ~1.2k more code
// enable or disable GxEPD2_GFX base class
#define ENABLE_GxEPD2_GFX 0

#include <GxEPD2_BW.h>
#include <Fonts/FreeMonoBold9pt7b.h>

// wiring for ESP32 S3
// SS/CS 10 MOSI/SDA 11 MISO 13 SCK/SCL 12
GxEPD2_BW<GxEPD2_154_D67, GxEPD2_154_D67::HEIGHT> display(GxEPD2_154_D67(/*CS=10*/ 10, /*DC=*/ 8, /*RST=*/ 7, /*BUSY=*/ 9));

void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println("setup");
  delay(100);
  display.init(115200);


  helloWorld();
  delay(1000);
  displayCenterFullWindow("Hello World!2");
  delay(1000);
  helloWorld_PartialMode();
  delay(1000);
  displayCenterPartialWindow("Hello World!2");
  delay(1000);
  clearScreen();
  delay(1000);
  display.hibernate();
  delay(5000);
  displayCenterFullWindow("Woke Up!");
  delay(1000);
  clearScreen();


  Serial.println("setup done");
  display.end();
}

void loop()
{
}

void helloWorld()
{
  Serial.println("helloWorld");
  const char HelloWorld[] = "Hello World!";
  display.setRotation(0);
  display.setFont(&FreeMonoBold9pt7b);
  display.setTextColor(GxEPD_BLACK);
  int16_t tbx, tby; uint16_t tbw, tbh;
  display.getTextBounds(HelloWorld, 0, 0, &tbx, &tby, &tbw, &tbh);
  // center bounding box by transposition of origin:
  uint16_t x = ((display.width() - tbw) / 2) - tbx;
  uint16_t y = ((display.height() - tbh) / 2) - tby;
  display.setFullWindow();

  display.firstPage();
  do
  {
    display.fillScreen(GxEPD_WHITE);
    display.setCursor(x, y);
    display.print(HelloWorld);
  }
  while (display.nextPage());
  Serial.println("helloWorld done");
}

void helloWorld_PartialMode()
{
  Serial.println("helloWorld_PartialMode");
  const char HelloWorld[] = "Hello World!";
  display.setPartialWindow(0, 0, display.width(), display.height());
  display.setRotation(0);
  display.setFont(&FreeMonoBold9pt7b);
  display.setTextColor(GxEPD_BLACK);
  int16_t tbx, tby; uint16_t tbw, tbh;
  display.getTextBounds(HelloWorld, 0, 0, &tbx, &tby, &tbw, &tbh);
  uint16_t umx = ((display.width() - tbw) / 2) - tbx;
  uint16_t umy = ((display.height() / 2) - tbh / 2) - tby;

  display.firstPage();
  do
  {
    display.fillScreen(GxEPD_WHITE);
    display.setCursor(umx, umy);
    display.print(HelloWorld);
  }
  while (display.nextPage());
  Serial.println("helloWorld_PartialMode done");
}

void displayCenterFullWindow(char *str)
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

void displayCenterPartialWindow(char *str)
{
  Serial.println("displayCenterPartialWindow");
  display.setPartialWindow(0, 0, display.width(), display.height());
  display.setRotation(0);
  display.setFont(&FreeMonoBold9pt7b);
  display.setTextColor(GxEPD_BLACK);
  int16_t tbx, tby; uint16_t tbw, tbh;
  display.getTextBounds(str, 0, 0, &tbx, &tby, &tbw, &tbh);
  uint16_t umx = ((display.width() - tbw) / 2) - tbx;
  uint16_t umy = ((display.height() / 2) - tbh / 2) - tby;

  display.firstPage();
  do
  {
    display.fillScreen(GxEPD_WHITE);
    display.setCursor(umx, umy);
    display.print(str);
  }
  while (display.nextPage());
  Serial.println("displayCenterPartialWindow done");
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

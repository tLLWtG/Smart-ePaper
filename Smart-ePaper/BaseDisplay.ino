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
    u8g2dp.setCursor(65, 100);
    u8g2dp.println("你好，世界！");
  }
  while (display.nextPage());
  Serial.println("helloWorld_GB2312 done");
}

void helloWorld_GB2312_PartialMode()
{
  Serial.println("helloWorld_GB2312");
  display.setRotation(0);
  display.setPartialWindow(0, 0, display.width(), display.height());
  u8g2dp.setFont(gb2312);
  u8g2dp.setForegroundColor(GxEPD_BLACK);
  u8g2dp.setBackgroundColor(GxEPD_WHITE);

  display.firstPage();
  do
  {
    u8g2dp.setCursor(65, 100);
    u8g2dp.println("你好，世界！");
  }
  while (display.nextPage());
  Serial.println("helloWorld_GB2312 done");
}
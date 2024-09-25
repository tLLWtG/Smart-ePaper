#include "SeP.h"
#include "BaseDisplay.h"
#include "Key.h"
#include "SDop.h"
#include "Player.h"
#include "WiFiInterface.h"

void display_setup()
{
  display.init(115200);
  u8g2dp.begin(display);
  display_Logo();
  key_setup();
}

void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println("setup");
  delay(50);
  display_setup();
  if (!SD_setup())
  {
    Serial.println("SD open fail.");
  }
  Player_setup();

  pageStatus = PageStatus_Index;
  Index_sel = PageStatus_Reader_Sel;

  Serial.println("setup done");
  delay(1000);
}

void loop()
{
  switch (pageStatus)
  {
    case PageStatus_Index:
      if (reDraw)
      {
        reDraw = false;
        if (++partDrawCnt >= 50)
        {
          partDrawCnt = 0;
          display_clearScreen();
        }
        display_Index();
      }
      break;
    case PageStatus_Reader_Sel:
      if (reDraw)
      {
        reDraw = false;
        if (++partDrawCnt >= 50)
        {
          partDrawCnt = 0;
          display_clearScreen();
        }
        display_Reader_Sel();
      }
      break;
    case PageStatus_MP3_Sel:
      if (reDraw)
      {
        reDraw = false;
        if (++partDrawCnt >= 50)
        {
          partDrawCnt = 0;
          display_clearScreen();
        }
        display_MP3_Sel();
      }
      break;
    case PageStatus_Weather:
      if (reDraw)
      {
        reDraw = false;
        if (++partDrawCnt >= 50)
        {
          partDrawCnt = 0;
          display_clearScreen();
        }
        display_Weather();
      }
      if (WiFi.status() == WL_CONNECTED)
      {
        if (connecting_wifi)
        {
          connecting_wifi = false;
          reDraw = true;
          delay(300);
        }
      }
      else
      {
        if (connecting_wifi)
        {
          checkDNS_HTTP();
          checkConnect();
        }
        else
        {
          connectToWiFi();
          connecting_wifi = true;
        }
      }
      break;
    case PageStatus_Hitokoto:
      if (reDraw)
      {
        reDraw = false;
        if (++partDrawCnt >= 50)
        {
          partDrawCnt = 0;
          display_clearScreen();
        }
        display_Hitokoto();
      }
      if (WiFi.status() == WL_CONNECTED)
      {
        if (connecting_wifi)
        {
          connecting_wifi = false;
          reDraw = true;
          delay(300);
        }
      }
      else
      {
        if (connecting_wifi)
        {
          checkDNS_HTTP();
          checkConnect();
        }
        else
        {
          connectToWiFi();
          connecting_wifi = true;
        }
      }
      break;
    case PageStatus_MP3_Play:
      // redraw for auto next
      if (mlist_loc != source.index())
      {
        mlist_l += source.index() - mlist_loc;
        mlist_r += source.index() - mlist_loc;
        mlist_loc = source.index();
        reDraw = true;
      }
      if (reDraw)
      {
        reDraw = false;
        if (++partDrawCnt >= 50)
        {
          partDrawCnt = 0;
          display_clearScreen();
        }
        display_MP3_Play();
        display.hibernate();
      }
      player.copy();
      break;
    case PageStatus_Reader:
      if (reDraw)
      {
        reDraw = false;
        if (++partDrawCnt >= 50)
        {
          partDrawCnt = 0;
          display_clearScreen();
        }
        display_Reader();
        display.hibernate();
      }
      break;
  }
  action.processActions();
}

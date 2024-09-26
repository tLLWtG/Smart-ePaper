#include "SeP.h"
#include "BaseDisplay.h"
#include "Key.h"
#include "SDop.h"
#include "Player.h"
#include "WiFiInterface.h"

void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println("setup");
  delay(50);

  display.init(115200);
  u8g2dp.begin(display);
  display_Logo();
  if (!SD_setup())
  {
    Serial.println("SD open fail.");
  }
  Player_setup();
  delay(1000);
  
  pageStatus = PageStatus_Index;
  Index_sel = PageStatus_Reader_Sel;
  key_setup();

  Serial.println("setup done");
}

void handleDisplayUpdate(void foo());
void handleWiFiConnection();

void loop()
{
  switch (pageStatus)
  {
    case PageStatus_Index:
      handleDisplayUpdate(display_Index);
      break;
    case PageStatus_Reader_Sel:
      handleDisplayUpdate(display_Reader_Sel);
      break;
    case PageStatus_MP3_Sel:
      handleDisplayUpdate(display_MP3_Sel);
      break;
    case PageStatus_Weather:
      handleDisplayUpdate(display_Weather);
      handleWiFiConnection();
      break;
    case PageStatus_Hitokoto:
      handleDisplayUpdate(display_Hitokoto);
      handleWiFiConnection();
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
      handleDisplayUpdate(display_MP3_Play);
      player.copy();
      break;
    case PageStatus_Reader:
      handleDisplayUpdate(display_Reader);
      break;
  }
  action.processActions();
}

void handleDisplayUpdate(void foo())
{
  if (reDraw)
  {
    reDraw = false;
    if (++partDrawCnt >= 50)
    {
      partDrawCnt = 0;
      display_clearScreen();
    }
    foo();
  }
}

void handleWiFiConnection()
{
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
}

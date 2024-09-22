#include "SeP.h"
#include "BaseDisplay.h"
#include "Key.h"
#include "SDop.h"
#include "Player.h"

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
  Index_sel = PageStatus_Reader;

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
    case PageStatus_Reader:
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
      
      break;
    case PageStatus_Hitokoto:
      
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
  }
  action.processActions();
}

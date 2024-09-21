#include "SeP.h"
#include "BaseDisplay.h"
#include "Key.h"
#include "SDop.h"

void display_setup()
{
  display.init(115200);
  u8g2dp.begin(display);
  // display_Logo();
  key_setup();
  // delay(1000);
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

  pageStatus = PageStatus_Index;
  Index_sel = PageStatus_Reader;

  Serial.println("setup done");
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
      
      break;
  }
  action.processActions();
}

#include <Arduino.h>

#include "SeP.h"
#include "Key.h"

void display_setup()
{
  display.init(115200);
  u8g2dp.begin(display);
  display_Logo();
  key_Index_setup();
  delay(1000);
}

void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println("setup");
  delay(50);
  display_setup();
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
      Index_action.processActions();
      break;
    case PageStatus_Reader:
      
      break;
    case PageStatus_MP3_Sel:
      
      break;
    case PageStatus_Weather:
      
      break;
    case PageStatus_Hitokoto:
      
      break;
    case PageStatus_MP3_Play:
      
      break;
  }
}

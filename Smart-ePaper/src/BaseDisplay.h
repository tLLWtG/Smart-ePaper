#ifndef __BASEDISPLAY_H
#define __BASEDISPLAY_H

#include <U8g2_for_Adafruit_GFX.h>
#include <GxEPD2_BW.h>
#include <Fonts/FreeMonoBold9pt7b.h>

#include "GB2312.h"

// base class GxEPD2_GFX can be used to pass references or pointers to the display instance as parameter, uses ~1.2k more code
// enable or disable GxEPD2_GFX base class
#define ENABLE_GxEPD2_GFX 0

extern GxEPD2_BW<GxEPD2_154_D67, GxEPD2_154_D67::HEIGHT> display;

// GB2312
extern const uint8_t gb2312[239032] U8G2_FONT_SECTION("gb2312");
extern U8G2_FOR_ADAFRUIT_GFX u8g2dp;

void displayCenterFullWindow(char *str);
void displayCenterPartialWindow(char *str);
void clearScreen();
void helloWorld();
void helloWorld_PartialMode();
void helloWorld_GB2312();
void helloWorld_GB2312_PartialMode();

#endif

#ifndef __BASEDISPLAY_H
#define __BASEDISPLAY_H

#include "SeP.h"

extern GxEPD2_BW<GxEPD2_154_D67, GxEPD2_154_D67::HEIGHT> display;

// GB2312
extern const uint8_t gb2312[239032] U8G2_FONT_SECTION("gb2312");
extern U8G2_FOR_ADAFRUIT_GFX u8g2dp;

extern const uint8_t LOGO[] PROGMEM;
extern const uint8_t ICON_BOOK[] PROGMEM;
extern const uint8_t ICON_MUSIC[] PROGMEM;
extern const uint8_t ICON_WEATHER[] PROGMEM;
extern const uint8_t ICON_QUOTE[] PROGMEM;
extern const uint8_t ICON_ARROW[] PROGMEM;

void display_CenterFullWindow(const char *str);
void display_CenterPartialWindow(const char *str);
void display_clearScreen();
void display_helloWorld();
void display_helloWorld_PartialMode();
void display_helloWorld_GB2312();
void display_helloWorld_GB2312_PartialMode();

void display_Logo();
void display_Index();

#endif

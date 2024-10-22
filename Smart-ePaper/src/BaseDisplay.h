#ifndef __BASEDISPLAY_H
#define __BASEDISPLAY_H

#include "SeP.h"
#include "Weather.h"
#include "Hitokoto.h"

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
extern const uint8_t ICON_STARTSTOP[] PROGMEM;
extern const uint8_t ICON_NEXT[] PROGMEM;
extern const uint8_t ICON_PREVIOUS[] PROGMEM;
extern const uint8_t ICON_PLUS[] PROGMEM;
extern const uint8_t ICON_SUB[] PROGMEM;

void display_CenterFullWindow(const char *str);
void display_CenterPartialWindow(const char *str);
void display_clearScreen();
void display_helloWorld();
void display_helloWorld_PartialMode();
void display_helloWorld_GB2312();
void display_helloWorld_GB2312_PartialMode();

void display_Logo();
void display_Index();
void display_MP3_Sel();
void display_MP3_Play();
void display_Weather();
void display_Hitokoto();
void display_Reader_Sel();
void display_Reader();

#endif

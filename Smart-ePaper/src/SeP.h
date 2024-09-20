#ifndef __SEP_H
#define __SEP_H

// for AudioActions.h
#ifndef DEBOUNCE_DELAY
#define DEBOUNCE_DELAY 300
#endif

#include <U8g2_for_Adafruit_GFX.h>
#include <GxEPD2_BW.h>
#include <Fonts/FreeMonoBold9pt7b.h>
#include <SdFat.h>

#include "AudioTools.h"
#include "GB2312.h"
#include "BaseDisplay.h"

extern GxEPD2_BW<GxEPD2_154_D67, GxEPD2_154_D67::HEIGHT> display;

// GB2312
extern const uint8_t gb2312[239032] U8G2_FONT_SECTION("gb2312");
extern U8G2_FOR_ADAFRUIT_GFX u8g2dp;

enum PageStatus
{
    PageStatus_Index,
    PageStatus_Reader,
    PageStatus_MP3_Sel,
    PageStatus_Weather,
    PageStatus_Hitokoto,
    PageStatus_MP3_Play,
};

extern enum PageStatus pageStatus, Index_sel;

extern bool reDraw;
extern uint8_t partDrawCnt;

extern AudioActions Index_action;

#endif

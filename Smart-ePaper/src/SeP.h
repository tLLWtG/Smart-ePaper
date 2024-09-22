#ifndef __SEP_H
#define __SEP_H

// for AudioActions.h
#ifndef DEBOUNCE_DELAY
#define DEBOUNCE_DELAY 300
#endif

#include <Arduino.h>
#include <U8g2_for_Adafruit_GFX.h>
#include <GxEPD2_BW.h>
#include <Fonts/FreeMonoBold9pt7b.h>
#include <SPI.h>
#include <SdFat.h>

#include "AudioTools.h"
#include "AudioLibs/AudioSourceSDFAT.h"
#include "AudioCodecs/CodecMP3Helix.h"
#include "GB2312.h"

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

extern SdFs sd;
extern SPIClass SPI2;
extern Vector<String> music_list;

extern uint16_t mlist_l, mlist_r, mlist_loc;

extern AudioActions action;

// player

extern const uint8_t Player_chipSelect;

extern float myVolume;
extern const char *startFilePath;
extern const char* ext;

extern SdSpiConfig sdSPICFG;
extern AudioSourceSDFAT source;
extern I2SStream i2s;
extern MP3DecoderHelix decoder;
extern AudioPlayer player;

#endif

#include "SeP.h"

// SS/CS 10, MOSI/SDA 11, MISO 13, SCK/SCL 12
GxEPD2_BW<GxEPD2_154_D67, GxEPD2_154_D67::HEIGHT> display(GxEPD2_154_D67(/*CS=10*/ 10, /*DC=*/ 8, /*RST=*/ 7, /*BUSY=*/ 9));

U8G2_FOR_ADAFRUIT_GFX u8g2dp;

enum PageStatus pageStatus, Index_sel;

bool reDraw = true;
uint8_t partDrawCnt = 0;

SdFs sd;
SPIClass SPI2(HSPI);
Vector<String> music_list;
Vector<String> txt_list;

uint16_t mlist_l = 0, mlist_r = 8, mlist_loc = 0;
uint16_t tlist_l = 0, tlist_r = 8, tlist_loc = 0;

AudioActions action;

// player

const uint8_t Player_chipSelect = 39;

float myVolume = 0.1;
const char *startFilePath="/music";
const char* ext="mp3";

SdSpiConfig sdSPICFG(Player_chipSelect, SHARED_SPI, 10000000, &SPI2);
AudioSourceSDFAT source(startFilePath, ext, sdSPICFG);
I2SStream i2s;
MP3DecoderHelix decoder;
AudioPlayer player(source, i2s, decoder);

// WiFi

bool connecting_wifi = false;

// GZIP Buffer
#define BUFFER_SIZE 5000
uint8_t inBuffer[BUFFER_SIZE];
uint8_t *outBuffer;

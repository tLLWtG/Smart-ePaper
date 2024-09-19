#include <Arduino.h>

#include "AudioTools.h"
#include "AudioLibs/AudioSourceSDFAT.h"
#include "AudioCodecs/CodecMP3Helix.h"

const int chipSelect = 39;
const char *startFilePath="/music";
const char* ext="mp3";

float myVolume = 0.1;

SdSpiConfig sdSPICFG(chipSelect, SHARED_SPI, 10000000, &SPI);
AudioSourceSDFAT source(startFilePath, ext, sdSPICFG);
I2SStream i2s;
MP3DecoderHelix decoder;
AudioPlayer player(source, i2s, decoder);
AudioActions action;

void printMetaData(MetaDataType type, const char* str, int len){
  Serial.print("==> ");
  Serial.print(toStr(type));
  Serial.print(": ");
  Serial.println(str);
}

void Player_next(bool, int, void*)
{
  Serial.println("Player_next");
  player.next();
}

void Player_previous(bool, int, void*)
{
  Serial.println("Player_previous");
  player.previous();
}

void Player_volumeH(bool, int, void*) 
{
  Serial.println("Player_volumeH");
  myVolume = min(1.0, myVolume + 0.05);
  player.setVolume(myVolume);
  Serial.printf("Current Volume: %f", myVolume);
  Serial.println();
}

void Player_volumeL(bool, int, void*)
{
  Serial.println("Player_volumeL");
  myVolume = max(0.0, myVolume - 0.05);
  player.setVolume(myVolume);
  Serial.printf("Current Volume: %f", myVolume);
  Serial.println();
}

void Player_startStop(bool, int, void*)
{
  Serial.println("Player_startStop");
  player.setActive(!player.isActive());
  Serial.printf("Current Status: %s", (player.isActive() ? "Active" : "Inactive"));
  Serial.println();
}

void setupActions()
{
  action.add(15, Player_next, AudioActions::ActiveLow);
  action.add(16, Player_previous, AudioActions::ActiveLow);
  action.add(17, Player_volumeH, AudioActions::ActiveLow);
  action.add(18, Player_volumeL, AudioActions::ActiveLow);
  action.add(47, Player_startStop, AudioActions::ActiveLow);
}

void setup() {
  Serial.begin(115200);
  AudioLogger::instance().begin(Serial, AudioLogger::Info);
  // void SPIClass::begin(int8_t sck, int8_t miso, int8_t mosi, int8_t ss)
  SPI.begin(40, 42, 41, chipSelect);

  // setup output
  auto cfg = i2s.defaultConfig(TX_MODE);
  // Custom I2S output pins
  cfg.pin_bck = 6;
  cfg.pin_ws = 4; // LCK
  cfg.pin_data = 5; // DIN
  i2s.begin(cfg);

  // setup player
  player.setMetadataCallback(printMetaData);
  player.setVolume(myVolume);
  player.begin();

  setupActions();
}

void loop() {
  player.copy();
  action.processActions();
}
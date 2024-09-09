#include "AudioTools.h"
#include "StarWars30.h"

AudioInfo info(22050, 1, 16);
I2SStream i2s;  // Output to I2S
MemoryStream music(StarWars30_raw, StarWars30_raw_len);
StreamCopy copier(i2s, music); // copies sound into i2s

void setup()
{
  Serial.begin(115200);
  AudioLogger::instance().begin(Serial, AudioLogger::Info);

  auto config = i2s.defaultConfig(TX_MODE);
  // Custom I2S output pins
  config.pin_bck = 6;
  config.pin_ws = 4; // LCK
  config.pin_data = 5; // DIN
  config.copyFrom(info);
  i2s.begin(config);
}

void loop(){
  if (!copier.copy())
  {
    i2s.end();
    stop();
  }
}
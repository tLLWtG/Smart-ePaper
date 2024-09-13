#include "AudioTools.h"
#include "AudioCodecs/CodecMP3Helix.h"
// 单车_part.mp3
// #include "zero.h"
// 离人_part.mp3
#include "zero2.h"

MemoryStream mp3(zero_mp3, zero_mp3_len);
I2SStream i2s;  
VolumeStream volume(i2s);
MP3DecoderHelix helix;
EncodedAudioStream dec(&volume, &helix);
StreamCopy copier(dec, mp3); // copy in to i2s

void setup()
{
  Serial.begin(115200);
  AudioLogger::instance().begin(Serial, AudioLogger::Info);  

  // config
  auto cfg = i2s.defaultConfig();
  cfg.sample_rate = 44100;
  cfg.channels = 2;
  cfg.bits_per_sample = 16;
  // Custom I2S output pins
  cfg.pin_bck = 6;
  cfg.pin_ws = 4; // LCK
  cfg.pin_data = 5; // DIN

  i2s.begin(cfg);

  dec.begin();

  volume.begin(cfg);
  volume.setVolume(0.1);
}

void loop()
{
  if (mp3.available())
  {
    copier.copy();
  }
  else
  {
    helix.end(); // flush output
    auto info = dec.decoder().audioInfo();
    LOGI("The audio rate from the mp3 file is %d", info.sample_rate);
    LOGI("The channels from the mp3 file is %d", info.channels);
    i2s.end();
    stop();
  }
}
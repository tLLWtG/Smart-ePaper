#include <Arduino.h>
#include <SPI.h>

#include "SdFat.h"
#include "AudioTools.h"
#include "AudioCodecs/CodecMP3Helix.h"

const int chipSelect = 39;

SdFs sd;
FsFile audioFile;

I2SStream i2s; // final output of decoded stream
VolumeStream volume(i2s);
EncodedAudioStream decoder(&volume, new MP3DecoderHelix()); // Decoding stream
StreamCopy copier;

void listFiles(FsFile *dir, int level)
{
  FsFile file;
  while (file.openNext(dir, O_RDONLY))
  {
    char filename[256];
    if (file.getName(filename, sizeof(filename)) > 0)
    {
      for (int i = 0; i < level; i++)
        Serial.print("  ");
      Serial.println(filename);
      if (file.isDir())
        listFiles(&file, level + 1);
    }
    file.close();
  }
}

void setup()
{
  Serial.begin(115200);

  AudioLogger::instance().begin(Serial, AudioLogger::Info);  

  // void SPIClass::begin(int8_t sck, int8_t miso, int8_t mosi, int8_t ss)
  SPI.begin(40, 42, 41, chipSelect);
  // delay(500);
  // SdSpiConfig(SdCsPin_t cs, uint8_t opt, uint32_t maxSpeed, SpiPort_t* port)
  if (!sd.begin(SdSpiConfig(chipSelect, SHARED_SPI, 4000000, &SPI)))
  {
    Serial.println("SD open fail.");
    return;
  }

  FsFile root;
  root.open("/");
  listFiles(&root, 0);
  root.close();
  Serial.println("----------");

  // setup file
  if (!audioFile.open("/example.mp3"))
  {
    sd.end();
    Serial.println("mp3 file open fail.");
    return;
  }
  Serial.print("File size: ");
  Serial.println(audioFile.size());
  // Serial.print(audioFile.readString());

  // setup i2s
  auto config = i2s.defaultConfig(TX_MODE);
  // Custom I2S output pins
  config.pin_bck = 6;
  config.pin_ws = 4; // LCK
  config.pin_data = 5; // DIN
  i2s.begin(config);
  
  decoder.addNotifyAudioChange(i2s);
  // setup I2S based on sampling rate provided by decoder
  decoder.begin();

  volume.begin(config); // we need to provide the bits_per_sample and channels
  volume.setVolume(0.2);

  // begin copy
  copier.begin(decoder, audioFile);
}

void loop()
{
  if (!copier.copy())
  {
    stop();
  }
}
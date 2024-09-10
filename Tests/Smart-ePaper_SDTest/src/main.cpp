#include <Arduino.h>
#include <SPI.h>
#include "SdFat.h"

SdFs sd;
SPIClass hspi(HSPI);

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
  // void SPIClass::begin(int8_t sck, int8_t miso, int8_t mosi, int8_t ss)
  hspi.begin(35, 36, 37, 38);
  delay(3000);
  // SdSpiConfig(SdCsPin_t cs, uint8_t opt, uint32_t maxSpeed, SpiPort_t* port)
  if (!sd.begin(SdSpiConfig(5, SHARED_SPI, 10000000, &hspi)))
  {
    Serial.println("SD open fail.");
    return;
  }

  Serial.print("FileSystem Type: ");
  auto fstype = sd.fatType();  
  switch (fstype)
  {
    case FAT_TYPE_EXFAT:
      Serial.println("ExFat");
      break;
    case FAT_TYPE_FAT32:
      Serial.println("Fat32");
      break;
    case FAT_TYPE_FAT16:
      Serial.println("Fat16");
      break;
    case 0:
      Serial.println("error");
      break;
  }

  auto size = sd.card()->sectorCount() * 512e-9;
  Serial.printf("Size: %f GB \r\n", size);
  Serial.println("----------");

  FsFile root;
  root.open("/");
  listFiles(&root, 0);
  root.close();
  Serial.println("----------");
}

void loop()
{
}

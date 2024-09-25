#include "SDop.h"

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

void make_music_list(FsFile *dir)
{
  FsFile file;
  while (file.openNext(dir, O_RDONLY))
  {
    char filename[256];
    if (file.getName(filename, sizeof(filename)) > 0)
    {
      String fileNameStr = String(filename);
      if (fileNameStr.endsWith(".mp3"))
      {
        music_list.push_back(fileNameStr);
      }
    }
    file.close();
  }
}

void make_txt_list(FsFile *dir)
{
  FsFile file;
  while (file.openNext(dir, O_RDONLY))
  {
    char filename[256];
    if (file.getName(filename, sizeof(filename)) > 0)
    {
      String fileNameStr = String(filename);
      if (fileNameStr.endsWith(".txt"))
      {
        txt_list.push_back(fileNameStr);
      }
    }
    file.close();
  }
}

bool SD_setup()
{
  Serial.println("SD_setup");
  // void SPIClass::begin(int8_t sck, int8_t miso, int8_t mosi, int8_t ss)
  SPI2.begin(40, 42, 41, chipSelect);
  // SdSpiConfig(SdCsPin_t cs, uint8_t opt, uint32_t maxSpeed, SpiPort_t* port)
  if (!sd.begin(SdSpiConfig(chipSelect, SHARED_SPI, 4000000, &SPI2)))
  {
    // Serial.println("SD open fail.");
    return false;
  }
  FsFile root;
  root.open("/");
  listFiles(&root, 0);
  root.close();
  Serial.println("----------");

  root.open("/music");
  make_music_list(&root);
  root.open("/docs");
  make_txt_list(&root);
  root.close();

  sd.end();
  SPI2.end();
  SPI2.begin(40, 42, 41, chipSelect);
  for (auto x: music_list)
  {
    Serial.println(x);
  }
  return true;
}

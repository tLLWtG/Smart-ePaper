#include "SeP.h"

void printMetaData(MetaDataType type, const char* str, int len){
  Serial.print("==> ");
  Serial.print(toStr(type));
  Serial.print(": ");
  Serial.println(str);
}

void Player_setup()
{
    // AudioLogger::instance().begin(Serial, AudioLogger::Info);
    AudioLogger::instance().begin(Serial, AudioLogger::Error);
    // setup output
    auto cfg = i2s.defaultConfig(TX_MODE);
    cfg.pin_bck = 6;
    cfg.pin_ws = 4;
    cfg.pin_data = 5;
    i2s.begin(cfg);

    player.setMetadataCallback(printMetaData);
    player.setVolume(myVolume);
    
    player.begin(0, false);
}

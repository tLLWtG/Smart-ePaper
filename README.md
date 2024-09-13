# Smart-ePaper

An ePaper MP3 player with WiFi. (Under development)

* **Board**: ESP32-S3-WROOM-1-N16R8
* **Framework**: Arduino
* **Modules**:
  * 1.54-inch 200x200 e-paper display (ZJY200200-0154DAAMFGN, driver: SSD1681)
  * PCM5102 (DAC)
  * MAX98357 (功放)
  * 3520 薄型侧发声腔体喇叭 (8Ω, 1W)
  * MicroSD Card Adapter (SPI)
  * ...
* **Arduino Libraries**:
  * zinggjm/GxEPD2
  * olikraus/U8g2_for_Adafruit_GFX
  * bblanchon/ArduinoJson
  * greiman/SdFat
* **Extra Libraries**:
  * [ArduinoUZlib](https://github.com/tignioj/ArduinoUZlib)
  * [arduino-audio-tools](https://github.com/pschatzmann/arduino-audio-tools)

## Tests

> Pre-integration functional testing.
>
> The term "extra lib" refers to PIO's "project specific (private) libraries.", which are not included in platformio.ini.

1. **Smart-ePaper_screenTest**



2. **Smart-ePaper_GB2312Test**



3. **Smart-ePaper_HTTPTest**

    Extra lib: 

    * ArduinoUZlib

4. **Smart-ePaper_AudioTest**
    
    Extra lib: 
    
    * arduino-audio-tools

5. **Smart-ePaper_SDTest**
    


6. **Smart-ePaper_MemoryMP3Test**

    Extra lib: 
    
    * arduino-audio-tools
    * arduino-libhelix
  
## License

This project is licensed under the MIT license. External libraries used by Smart-ePaper are licensed under their own licenses.

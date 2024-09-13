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
  * [arduino-libhelix](https://github.com/pschatzmann/arduino-libhelix)

## Pin Assignments

> You can refer to projects in the "Tests" folder to modify the pins yourself.

* **ePaper**
  
  | Function | Pin |
  |----------|-----|
  | CS       | G10 |
  | MOSI/SDA | G11 |
  | MISO     | G13 |
  | SCK/SCL  | G12 |
  | DC       | G8  |
  | RST      | G7  |
  | BUSY     | G9  |

* **PCM5102**
  
  | Function | Pin  |
  |----------|------|
  | BCK      | G6   |
  | WS/LCK   | G4   |
  | DIN      | G5   |
  | FMT      | GND  |
  | XMT      | 3.3V |

  > DMP - De-emphasis control for 44.1kHz sampling rate(1): Off (Low) / On (High)
  >
  > FLT - Filter select : Normal latency (Low) / Low latency (High)
  >
  > SCL(I left it floating) - System clock input (probably SCL on your board).
  >
  > FMT - Audio format selection : I2S (Low) / Left justified (High)
  >
  > XMT - Soft mute control(1): Soft mute (Low) / soft un-mute (High)

* **MicroSD Card Adapter**
  
  | Function | Pin |
  |----------|-----|
  | SCK      | G35 |
  | MISO     | G36 |
  | MOSI     | G37 |
  | SS       | G38 |


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

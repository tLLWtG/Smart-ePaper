# Smart-ePaper

An ePaper MP3 player with WiFi. (Under development)

* **Board**: ESP32-S3-WROOM-1-N16R8
* **Framework**: Arduino (PlatformIO IDE)
* **Other Hardware Components**:
  * 1.54-inch 200x200 e-paper display (ZJY200200-0154DAAMFGN, driver: SSD1681)
  * PCM5102 (DAC)
  * PAM8406 (功放)
  * 3520 薄型侧发声腔体喇叭 (8Ω, 1W)
  * MicroSD Card Adapter (SPI, support 32GB SDHC)
  * ...
* **Libraries**
  * **Arduino Lib**:
    * zinggjm/GxEPD2
    * olikraus/U8g2_for_Adafruit_GFX
    * bblanchon/ArduinoJson
    * greiman/SdFat
  * **Extra Lib**:
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

  > Optional Pins
  > 
  >   * **DMP** - De-emphasis control for 44.1kHz sampling rate(1): Off (Low) / On (High)
  >
  >   * **FLT** - Filter select : Normal latency (Low) / Low latency (High)
  >
  >   * **SCL** (left floating is ok) - System clock input (probably SCL on your board).
  >
  >   * **FMT** - Audio format selection : I2S (Low) / Left justified (High)
  >
  >   * **XMT** - Soft mute control(1): Soft mute (Low) / soft un-mute (High)

* **MicroSD Card Adapter**
  
  | Function | Pin |
  |----------|-----|
  | SCK      | G40 |
  | MISO     | G42 |
  | MOSI     | G41 |
  | SS       | G39 |

## Notes

* 对于 SdFat 库，需要将其 SdFatConfig.h 中的宏定义 `USE_UTF8_LONG_NAMES` 的值改为 1，才能正常读取中文路径。
* 电源不稳定时（比如我的电脑在插电状态下的 USB 供电），DAC 效果极差，同时也会导致 SD 卡读取异常。
* 某些 SD 卡读写模块虽然标 3.3~5V，但实际上一定要接 5V 才能正常使用。

## Tests

> Pre-integration functional testing.
>
> The term "Extra Lib" refers to PIO's "project specific (private) libraries.", which are not included in "platformio.ini".

1. **Smart-ePaper_screenTest**

    * Arduino Lib: GxEPD2

2. **Smart-ePaper_GB2312Test**

    * Arduino Lib: GxEPD2, U8g2_for_Adafruit_GFX

3. **Smart-ePaper_HTTPTest**

    * Arduino Lib: ArduinoJson
    * Extra Lib: ArduinoUZlib

4. **Smart-ePaper_AudioTest**
    
    * Extra Lib: arduino-audio-tools

5. **Smart-ePaper_SDTest**
    
    * Arduino Lib: SdFat

6. **Smart-ePaper_MemoryMP3Test**

    * Extra Lib: arduino-audio-tools, arduino-libhelix

7. **Smart-ePaper_SDMP3Test**

    * Arduino Lib: SdFat
    * Extra Lib: arduino-audio-tools, arduino-libhelix
  
## License

This project is licensed under the MIT license. External libraries used by Smart-ePaper are licensed under their own licenses.

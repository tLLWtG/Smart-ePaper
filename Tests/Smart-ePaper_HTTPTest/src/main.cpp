#include <Arduino.h>

#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <ArduinoUZlib.h> // 解压 GZIP

#include "WiFiInterface.h"

// 设置重置按键引脚，用于删除WiFi信息
const int resetPin = 17;

// GZIP Buffer
#define BUFFER_SIZE 5000
uint8_t inBuffer[BUFFER_SIZE];
uint8_t *outBuffer;

String get_weather();
// void wifi_init();

void setup()
{
  pinMode(resetPin, INPUT_PULLUP);
  Serial.begin(115200);
  Serial.println();
  Serial.println("setup");
  delay(100);


  // wifi_init()
  connectToWiFi();

  if (WiFi.status() == WL_CONNECTED)
  {
    Serial.println(get_weather());
  }
  else
  {
    Serial.println("WiFi 未连接，无法获取天气信息。");
  }

  Serial.println("setup done");
}

void loop()
{
  if (digitalRead(resetPin) == 0)
  {
    delay(3000);
    if (digitalRead(resetPin) == 0) 
    {
      Serial.println("正在清空网络配置信息。");
      restoreWiFi();
      ESP.restart();
    }
  }
  
  if (WiFi.status() != WL_CONNECTED)
  {
    checkDNS_HTTP();
    checkConnect();
  }
  delay(30);
}

String get_weather()
{
  String url = "https://devapi.qweather.com/v7/weather/now";
  String APIKEY = ""; // 和风天气 APIKEY
  String LocationID = "101230201"; // 厦门市

  HTTPClient http;
  http.begin(url + "?key=" + APIKEY + "&location=" + LocationID);
  int httpCode = http.GET();
  Serial.printf("HTTP Code: %d\n", httpCode);
  if (httpCode != 200)
  {
    Serial.println("GET Failed.");
    return "";
  }
  String responseGZIP = http.getString();
  Serial.println("responseGZIP: ");
  Serial.println(responseGZIP);
  http.end();

  int inBuffer_len = responseGZIP.length();
  Serial.println("responseGZIP_len:" + String(inBuffer_len));
  for (int i = 0; i < inBuffer_len; ++i)
  {
    inBuffer[i] = responseGZIP[i];
  }
  outBuffer = NULL;
  uint32_t outBuffer_len = 0;
  int GZIPresult = ArduinoUZlib::decompress(inBuffer, inBuffer_len, outBuffer, outBuffer_len);
  Serial.println("outBuffer_len: " + String(outBuffer_len));
  Serial.write(outBuffer, outBuffer_len);
  Serial.println();
  String response;
  response.reserve(outBuffer_len);
  for (int i = 0; i < outBuffer_len; ++i) {
    response.concat((char)outBuffer[i]);
  }
  if (outBuffer != NULL)
  {
    free(outBuffer);
    outBuffer = NULL;
  }
  Serial.println("response: ");
  Serial.println(response);

  JsonDocument doc;
  deserializeJson(doc, response);
  String weather = doc["now"]["text"].as<String>();
  int temp = doc["now"]["temp"].as<int>();
  int humidity = doc["now"]["humidity"].as<int>();
  String updateTime = doc["updateTime"].as<String>();

  return "weather: " + weather + "\n" + "temp: " + String(temp) + "\n"
  + "humidity: " + String(humidity) + "\n" + "updateTime: " + updateTime + "\n";
}

// 固定配网
// void wifi_init()
// {
//   const char* ssid = "";
//   const char* password = "";
//   uint8_t flag = 0, timeout = 0;
//   WiFi.begin(ssid, password);
//   Serial.println();
//   Serial.printf("Connecting to %s", ssid);
//   Serial.println();
//   while (flag != WL_CONNECTED || ++timeout > 60)
//   {
//     flag = WiFi.status();
//     delay(500);
//     Serial.printf(".");
//   }
//   if (WiFi.status() == WL_CONNECTED)
//   {
//     Serial.printf("Connected to %s", ssid);
//     Serial.println();
//     Serial.printf("IP address: %s", WiFi.localIP().toString().c_str());
//     Serial.println();
//   }
//   else
//   {
//     Serial.println("wifi_init failed");
//   }
// }

#include "Weather.h"

String get_weatherStr(String url)
{
  String APIKEY = myAPIKEY;
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
  return response;
}

Realtime_weather get_realtime_weather()
{
  String url = "https://devapi.qweather.com/v7/weather/now";
  String response = get_weatherStr(url);
  if (response.isEmpty())
    return {};
  JsonDocument doc;
  deserializeJson(doc, response);

  Realtime_weather res;
  res.updateTime = doc["updateTime"].as<String>().substring(11, 16);
  res.temp = doc["now"]["temp"].as<String>();
  res.text = doc["now"]["text"].as<String>();
  res.windDir = doc["now"]["windDir"].as<String>();
  res.windScale = doc["now"]["windScale"].as<String>();
  res.humidity = doc["now"]["humidity"].as<String>();

  return res;
}

Forecast_weather get_forecast_weather()
{
  String url = "https://devapi.qweather.com/v7/weather/3d";
  String response = get_weatherStr(url);
  if (response.isEmpty())
    return {};
  JsonDocument doc;
  deserializeJson(doc, response);

  Forecast_weather res;
  res.updateTime = doc["updateTime"].as<String>().substring(11, 16);
  for (int i = 0; i < 3; ++i)
  {
    res.fxDate[i] = doc["daily"][i]["fxDate"].as<String>().substring(5, 10);
    res.tempMax[i] = doc["daily"][i]["tempMax"].as<String>();
    res.tempMin[i] = doc["daily"][i]["tempMin"].as<String>();
    res.textDay[i] = doc["daily"][i]["textDay"].as<String>();
    res.textNight[i] = doc["daily"][i]["textNight"].as<String>();
  }

  return res;
}

Air_data get_air_data()
{
  String url = "https://devapi.qweather.com/v7/air/now";
  String response = get_weatherStr(url);
  if (response.isEmpty())
    return {};
  JsonDocument doc;
  deserializeJson(doc, response);

  Air_data res;
  res.updateTime = doc["updateTime"].as<String>().substring(11, 16);
  res.aqi = doc["now"]["aqi"].as<String>();
  res.category = doc["now"]["category"].as<String>();

  return res;
}

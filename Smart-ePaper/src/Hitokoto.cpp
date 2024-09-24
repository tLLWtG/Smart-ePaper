#include "Hitokoto.h"

String get_hitokotoStr(String url)
{
  HTTPClient http;
  http.begin(url);
  int httpCode = http.GET();
  Serial.printf("HTTP Code: %d\n", httpCode);
  if (httpCode != 200)
  {
    Serial.println("GET Failed.");
    return "";
  }
  String response = http.getString();
  Serial.println("response: ");
  Serial.println(response);
  http.end();

  return response;
}

Hitokoto get_hitokoto()
{
  String url = "https://v1.hitokoto.cn/?c=a&c=b&c=d&c=i&c=k&encode=json";
  String response = get_hitokotoStr(url);
  if (response.isEmpty())
    return {};
  JsonDocument doc;
  deserializeJson(doc, response);

  Hitokoto res;
  res.hitokoto = doc["hitokoto"].as<String>();
  res.from = doc["from"].as<String>();

  return res;
}

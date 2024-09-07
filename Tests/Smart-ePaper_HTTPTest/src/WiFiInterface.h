#ifndef __WIFIINTERFACE_H__
#define __WIFIINTERFACE_H__

#include <WiFi.h>
#include <DNSServer.h>
#include <WebServer.h>
#include <ESPmDNS.h>      // 用于设备域名 MDNS.begin("esp32")，"esp32.local"
#include <esp_wifi.h>     // 用于 esp_wifi_restore() 删除保存的wifi信息

extern const int connectTimeOut_s;

void connectToWiFi(int timeOut_s = connectTimeOut_s);    // 连接 WiFi
void restoreWiFi();                   // 删除保存的 WiFi 信息
void checkConnect();                  // 检测 WiFi 是否已经连接
void checkDNS_HTTP();                 // 检测客户端 DNS&HTTP 请求

#endif

#include "WiFiInterface.h"

const int connectTimeOut_s = 15;
const int DNS_PORT = 53;
const int webPort = 80;
const char* myAP_SSID  = "myESP32_AP";
const char* myHOST_NAME = "MY_ESP32";
IPAddress myAPIP(192, 168, 4, 1);

String scanNetworksID = "";
String wifi_ssid = "";                     // 暂时存储 WiFi 账号密码
String wifi_pass = "";                     // 暂时存储 WiFi 账号密码

DNSServer dnsServer;
WebServer server(webPort);

#define ROOT_HTML  "<!DOCTYPE html><html><head><title>WIFI</title><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"></head><style type=\"text/css\">.input{display: block; margin-top: 10px;}.input span{width: 100px; float: left; float: left; height: 36px; line-height: 36px;}.input input{height: 30px;width: 200px;}.btn{width: 120px; height: 35px; background-color: #000000; border:0px; color:#ffffff; margin-top:15px; margin-left:100px;}</style><body><form method=\"POST\" action=\"configwifi\"><label class=\"input\"><span>WiFi SSID</span><input type=\"text\" name=\"ssid\" value=\"\"></label><label class=\"input\"><span>WiFi PASS</span> <input type=\"text\"  name=\"pass\"></label><input class=\"btn\" type=\"submit\" name=\"submit\" value=\"Submie\"> <p><span> Nearby wifi:</P></form>"

static void handleRoot();                    // 处理网站根目录的访问请求
static void handleConfigWifi() ;             // 提交数据后的提示页面
static void handleNotFound();                // 处理 404
static void initSoftAP();                    // 进入 AP 模式
static void initDNS();                       // 开启 DNS 服务器
static void initWebServer();                 // 初始化 WebServer
static bool scanWiFi();                      // 扫描附近的 WiFi，为了显示在配网界面
static void wifiConfig();                    // 配置配网功能

static void handleRoot() 
{
  if (server.hasArg("selectSSID"))
    server.send(200, "text/html", ROOT_HTML + scanNetworksID + "</body></html>");
  else
    server.send(200, "text/html", ROOT_HTML + scanNetworksID + "</body></html>");   
}

static void handleConfigWifi()
{
  if (server.hasArg("ssid"))
  {
    wifi_ssid = server.arg("ssid"); // 获取 html 表单输入框 name 名为 "ssid" 的内容
    Serial.print("got ssid:");
    Serial.println(wifi_ssid);
  } 
  else
  { 
    server.send(200, "text/html", "<meta charset='UTF-8'>error, not found ssid");
    Serial.println("error, not found ssid");
    return;
  }
  if (server.hasArg("pass")) 
  {
    wifi_pass = server.arg("pass"); // 获取 html 表单输入框 name 名为 "pwd" 的内容
    Serial.print("got password:");
    Serial.println(wifi_pass);
  } 
  else 
  {
    server.send(200, "text/html", "<meta charset='UTF-8'>error, not found password");
    Serial.println("error, not found password");
    return;
  }
  server.send(200, "text/html", "<meta charset='UTF-8'>SSID：" + wifi_ssid + "<br />password:" + wifi_pass + "<br />已取得WiFi信息，正在尝试连接，请手动关闭此页面。");
  delay(2000);
  server.close();
  WiFi.softAPdisconnect();
  Serial.println("WiFi Connect SSID:" + wifi_ssid + "  PASS:" + wifi_pass);

  if (WiFi.status() != WL_CONNECTED)
  {
    Serial.println("connectToWiFi()");
    connectToWiFi(connectTimeOut_s);
  } 
  else
  {
    Serial.println("提交的配置信息自动连接成功。");
  }
}

static void handleNotFound()
{           
  handleRoot(); // 访问不存在目录则返回配置页面
}

static void initSoftAP() {
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(myAPIP, myAPIP, IPAddress(255, 255, 255, 0));
  if (WiFi.softAP(myAP_SSID)) // 开启 AP 热点，如需要密码则添加第二个参数
  {                           
    Serial.println("ESP-32S SoftAP is right.");
    Serial.print("Soft-AP IP address = ");
    Serial.println(WiFi.softAPIP());
    Serial.println(String("MAC address = ")  + WiFi.softAPmacAddress().c_str());
  } 
  else
  { 
    Serial.println("WiFiAP Failed");
    delay(1000);
    Serial.println("restart now...");
    ESP.restart();
  }
}

static void initDNS() 
{
  if (dnsServer.start(DNS_PORT, "*", myAPIP)) // 判断将所有地址映射到 esp32 的 ip 上是否成功
  {
    Serial.println("start dnsserver success.");
  } else {
    Serial.println("start dnsserver failed.");
  }
}

static void initWebServer() 
{
  if (MDNS.begin("esp32"))
  {
    Serial.println("MDNS responder started");
  }
  server.on("/", HTTP_GET, handleRoot);                      // 当浏览器请求服务器根目录(网站首页)时调用自定义函数 handleRoot 处理，设置主页回调函数，必须添加第二个参数 HTTP_GET，否则无法强制门户
  server.on("/configwifi", HTTP_POST, handleConfigWifi);     // 当浏览器请求服务器 /configwifi (表单字段)目录时调用自定义函数 handleConfigWifi 处理
  server.onNotFound(handleNotFound);                         // 当浏览器请求的网络资源无法在服务器找到时调用自定义函数 handleNotFound 处理
  server.begin();                                            // 启动 TCP SERVER
 
  Serial.println("WebServer started!");
}

static bool scanWiFi()
{
  Serial.println("scan start");
  Serial.println("--------->");
  // 扫描附近 WiFi
  int n = WiFi.scanNetworks();
  Serial.println("scan done");
  if (n == 0)
  {
    Serial.println("no networks found");
    scanNetworksID = "no networks found";
    return false;
  }
  else {
    Serial.print(n);
    Serial.println(" networks found");
    for (int i = 0; i < n; ++i)
    {
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(WiFi.SSID(i));
      Serial.print(" (");
      Serial.print(WiFi.RSSI(i));
      Serial.print(")");
      Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN) ? " " : "*");
      scanNetworksID += "<P>" + WiFi.SSID(i) + "</P>";
      delay(10);
    }
    return true;
  }
}

static void wifiConfig() 
{
  initSoftAP();   
  initDNS();        
  initWebServer();  
  scanWiFi();       
}

void connectToWiFi(int timeOut_s)
{
  WiFi.hostname(myHOST_NAME);
  Serial.println("connectToWiFi()");
  WiFi.mode(WIFI_STA);
  WiFi.setAutoReconnect(true);
  
  if (wifi_ssid != "")
  {
    Serial.println("用 web 配置信息连接。");
    WiFi.begin(wifi_ssid.c_str(), wifi_pass.c_str());
    wifi_ssid = "";
    wifi_pass = "";
  } 
  else
  {
    Serial.println("用 nvs 保存的信息连接。");
    WiFi.begin(); // begin() 不传入参数，默认连接上一次连接成功的 WiFi
  }

  int Connect_time = 0;
  while (WiFi.status() != WL_CONNECTED)
  {  
    Serial.print(".");
    delay(500);
    Connect_time ++;

    if (Connect_time > 2 * timeOut_s) // 长时间连接不上，重新进入配网页面
    { 
      Serial.println("");
      Serial.println("WIFI autoconnect fail, start AP for webconfig now...");
      wifiConfig(); // 开始配网
      return;
    }
  }

  if (WiFi.status() == WL_CONNECTED)
  {
    Serial.println("WIFI connect Success");
    Serial.printf("SSID:%s", WiFi.SSID().c_str());
    Serial.printf(", PSW:%s\r\n", WiFi.psk().c_str());
    Serial.print("LocalIP:");
    Serial.print(WiFi.localIP());
    Serial.print(" ,GateIP:");
    Serial.println(WiFi.gatewayIP());
    Serial.print("WIFI status is:");
    Serial.println(WiFi.status());
    server.stop();
  }
}

void restoreWiFi()
{
  delay(500);
  esp_wifi_restore(); // 删除保存的 WiFi 信息
  Serial.println("WiFi 配置信息已清空，准备重启设备...");
  delay(10);
}

void checkConnect() 
{
  if (WiFi.status() != WL_CONNECTED)
  {
    if (WiFi.getMode() != WIFI_AP && WiFi.getMode() != WIFI_AP_STA ) 
    {
      Serial.println("WIFI未连接。");
      Serial.println("WiFi Mode:");
      Serial.println(WiFi.getMode());
      Serial.println("正在连接WiFi...");
      connectToWiFi(connectTimeOut_s);
    }
  } 
}

void checkDNS_HTTP()
{
  dnsServer.processNextRequest();   // 检查客户端 DNS 请求
  server.handleClient();            // 检查客户端(浏览器) http 请求
}

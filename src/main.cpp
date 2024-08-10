#include <Arduino.h>
#include "M5Dial.h"
#include <HWCDC.h>
#include "USB.h"
#include "USBMSC.h"
#include "screen.h"
#include "Ticker.h"
#include "task.h"
#include "Wire.h"
#include <WiFi.h>
// #include "AdafruitConnect.h"
// put function declarations here:
M5GFX display;
M5Canvas img(&M5Dial.Display);

Ticker updatescreen;
Ticker updateAC;
Ticker tickercontrolRelay;
Ticker tickerMQTTpublish;

void setup() {
  // put your setup code here, to run once:
  auto cfg = M5.config();
  M5Dial.begin(cfg, true, false);
  Serial.begin(115200);
  Wire.begin();
  M5Dial.Encoder.write(-1000);
  setupPahub();
  switchChanel_2();
   setupACsensor();
  switchChanel_3();
   setupRelay();
   ALLrelayState=OFF_ALL;
   controlALL();
  //  setupMQTT1();
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  setupMQTT();
  init_screen();
  while (WiFi.status() != WL_CONNECTED){
  
    M5Dial.Lcd.setCursor(158, 106);
    M5Dial.Lcd.setTextSize(1);
    M5Dial.Lcd.printf("Connecting...");
  }
  while(WiFiConnectFlag!=true && MQTTConnectFlag!=true){
    checkWiFiStatus();
    checkConnectMQTT(); 
  }
  updateAC.attach_ms(211,taskUpdateACinfor);
  updatescreen.attach_ms(1023,taskUpdateScreen);
  tickercontrolRelay.attach_ms(53,taskControlRelay);
  tickerMQTTpublish.attach_ms(1013, taskClientPublish);
  clientPublish("kienpham/feeds/topic0","0");
  clientPublish("kienpham/feeds/topic1","0");
  clientPublish("kienpham/feeds/topic2","0");
  clientPublish("kienpham/feeds/topic3","0");
  clientPublish("kienpham/feeds/topic4","0");

}

void loop() {
  // M5.update();
  // if(M5.BtnA.wasClicked()==true){
  //   relayState=ON_RELAY_1;
  //   switchChanel_3();
  //   controlALL();
  // }
  // put your main code here, to run repeatedly:
    if (WiFi.status() == WL_CONNECTED)
  {
    checkWiFiStatus();
    checkConnectMQTT();
    clientLoop(); 
  }
  // delay (100);
  // io.run(); // gọi hàm Run.
  // delay(1000);
}

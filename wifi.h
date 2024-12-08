//==============================================
/*

  'wifi.h'

  Sets up wireless accesspoint, configuration pages, and OTA handling
  Recieves and formats user inputs, indicates that configuration is ready for updating 

*/
//==============================================

#pragma once
#include <Preferences.h>

#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <Update.h>
#include <WiFiAP.h>

#include "DataFunctions.h"
#include "display.h"
#include "pinMap.h"

#include "SensorData.h"
#include "config.h"
#include "led.h"
#include "nvs.h"

// HTML pages
#include "pages/jquery.h"
#include "pages/start.h"
#include "pages/update.h"
#include "pages/config2.h"
#include "pages/wifi.h"
#include "pages/boot.h"
#include "pages/sensorConfig.h"
#include "pages/displayConfig.h"
#include "pages/ledConfig.h"
#include "pages/test.h"


//#define WIFI_STA_MODE
char ssid_sta[16] = "ssid";
char password_sta[16] = "pass";

// WiFi OTA
WebServer server(80);

int wifiEnabled = false;
bool readyToUpdate = false;

int red;
int green;
int blue;

int otaUpdateStatus = 0;

bool opened = false;
// bool updateWifiConfig = false;


/*
    Service any client connections to the gauge
*/

void disableWifi() {

  WiFi.mode(WIFI_OFF);
  wifiEnabled = false;
}

void ota(void) {
  server.handleClient();
}

//===============================================================
// Functions used to send information to browser
// Configure to webpages in WiFi setup
//===============================================================

/*
    When JS is required send the GZ JQuery 3.2.1
*/
void onJavaScript(void) {

  //Serial.println("onJavaScript(void)");

  server.setContentLength(jquery_min_js_v3_2_1_gz_len);
  server.sendHeader(F("Content-Encoding"), F("gzip"));
  server.send_P(200, "text/javascript", jquery_min_js_v3_2_1_gz, jquery_min_js_v3_2_1_gz_len);
}

void handleRoot() {
  server.send(200, "text/html", startPage);
}

void handleVersion() {
  server.send(200, "text/plane", softwareVersion);
}

void handleNote() {
  server.send(200, "text/plane", buildNote);
}

void handleHardware() {
  server.send(200, "text/plane", hardwareConfig);
}

void handleOTA() {
  server.send(200, "text/html", updatePage);
}

void handleDataTest(){
  server.send(200, "text/plane", "TEST" );
}

void handleData_currentConfig() {
  // Convert value to a string
  char currentGaugeConfig[10];
  sprintf(currentGaugeConfig, "%d", (config_selectedConfig[0] + 1));
  server.send(200, "text/plane", currentGaugeConfig);
}

void handleData_currentType() {
  String currentGaugeType = gaugeStyleNames[config_gaugeStyle[config_selectedConfig[0]]];
  server.send(200, "text/plane", currentGaugeType);
}


// =========================================================
// Send Current Sensor Selections
// =========================================================

void handleData_currentSensor1() {

  server.send(200, "text/plane", ptrData[0]->dataNameFull);
}
void handleData_currentSensor2() {
  server.send(200, "text/plane", ptrData[1]->dataNameFull);
}
void handleData_currentSensor3() {
  server.send(200, "text/plane", ptrData[2]->dataNameFull);
}
void handleData_currentSensor4() {
  server.send(200, "text/plane", ptrData[3]->dataNameFull);
}
void handleData_currentSensor5() {
  server.send(200, "text/plane", ptrData[4]->dataNameFull);
}
void handleData_currentSensor6() {
  server.send(200, "text/plane", ptrData[5]->dataNameFull);
}
void handleData_currentSensor7() {
  server.send(200, "text/plane", ptrData[6]->dataNameFull);
}
void handleData_currentSensor8() {
  server.send(200, "text/plane", ptrData[7]->dataNameFull);
}
void handleData_currentSensor9() {
  server.send(200, "text/plane", ptrData[8]->dataNameFull);
}
void handleData_currentSensor10() {
  server.send(200, "text/plane", ptrData[9]->dataNameFull);
}

// =========================================================
// Send Current Mins
// =========================================================

void handleData_currentSensor1min() {
  char sensor1min[10];
  dtostrf(ptrData[0]->minimum, 4, 2, sensor1min);
  server.send(200, "text/plane", sensor1min);
}
void handleData_currentSensor2min() {
  char sensor2min[10];
  dtostrf(ptrData[1]->minimum, 5, 2, sensor2min);
  server.send(200, "text/plane", sensor2min);
}
void handleData_currentSensor3min() {
  char sensor3min[10];
  dtostrf(ptrData[2]->minimum, 5, 2, sensor3min);
  server.send(200, "text/plane", sensor3min);
}
void handleData_currentSensor4min() {
  char sensor4min[10];
  dtostrf(ptrData[3]->minimum, 5, 2, sensor4min);
  server.send(200, "text/plane", sensor4min);
}
void handleData_currentSensor5min() {
  char sensor5min[10];
  dtostrf(ptrData[4]->minimum, 5, 2, sensor5min);
  server.send(200, "text/plane", sensor5min);
}

void handleData_currentSensor6min() {
  char sensor6min[10];
  dtostrf(ptrData[5]->minimum, 5, 2, sensor6min);
  server.send(200, "text/plane", sensor6min);
}

void handleData_currentSensor7min() {
  char sensor7min[10];
  dtostrf(ptrData[6]->minimum, 5, 2, sensor7min);
  server.send(200, "text/plane", sensor7min);
}

void handleData_currentSensor8min() {
  char sensor8min[10];
  dtostrf(ptrData[7]->minimum, 5, 2, sensor8min);
  server.send(200, "text/plane", sensor8min);
}
void handleData_currentSensor9min() {
  char sensor9min[10];
  dtostrf(ptrData[8]->minimum, 5, 2, sensor9min);
  server.send(200, "text/plane", sensor9min);
}
void handleData_currentSensor10min() {
  char sensor10min[10];
  dtostrf(ptrData[9]->minimum, 5, 2, sensor10min);
  server.send(200, "text/plane", sensor10min);
}

// =========================================================
// Send Current Maxs
// =========================================================

void handleData_currentSensor1max() {
  char sensor1max[10];
  dtostrf(ptrData[0]->maximum, 5, 2, sensor1max);
  server.send(200, "text/plane", sensor1max);
}
void handleData_currentSensor2max() {
  char sensor2max[10];
  dtostrf(ptrData[1]->maximum, 5, 2, sensor2max);
  server.send(200, "text/plane", sensor2max);
}
void handleData_currentSensor3max() {
  char sensor3max[10];
  dtostrf(ptrData[2]->maximum, 5, 2, sensor3max);
  server.send(200, "text/plane", sensor3max);
}
void handleData_currentSensor4max() {
  char sensor4max[10];
  dtostrf(ptrData[3]->maximum, 5, 2, sensor4max);
  server.send(200, "text/plane", sensor4max);
}
void handleData_currentSensor5max() {
  char sensor5max[10];
  dtostrf(ptrData[4]->maximum, 5, 2, sensor5max);
  server.send(200, "text/plane", sensor5max);
}

void handleData_currentSensor6max() {
  char sensor6max[10];
  dtostrf(ptrData[5]->maximum, 5, 2, sensor6max);
  server.send(200, "text/plane", sensor6max);
}

void handleData_currentSensor7max() {
  char sensor7max[10];
  dtostrf(ptrData[6]->maximum, 5, 2, sensor7max);
  server.send(200, "text/plane", sensor7max);
}

void handleData_currentSensor8max() {
  char sensor8max[10];
  dtostrf(ptrData[7]->maximum, 5, 2, sensor8max);
  server.send(200, "text/plane", sensor8max);
}
void handleData_currentSensor9max() {
  char sensor9max[10];
  dtostrf(ptrData[8]->maximum, 5, 2, sensor9max);
  server.send(200, "text/plane", sensor9max);
}
void handleData_currentSensor10max() {
  char sensor10max[10];
  dtostrf(ptrData[9]->maximum, 5, 2, sensor10max);
  server.send(200, "text/plane", sensor10max);
}


// =========================================================
// Send Current Alert Low
// =========================================================

void handleData_currentSensor1low() {
  char sensor1low[10];
  dtostrf(ptrData[0]->alertLow, 5, 2, sensor1low);
  server.send(200, "text/plane", sensor1low);
}
void handleData_currentSensor2low() {
  char sensor2low[10];
  dtostrf(ptrData[1]->alertLow, 5, 2, sensor2low);
  server.send(200, "text/plane", sensor2low);
}
void handleData_currentSensor3low() {
  char sensor3low[10];
  dtostrf(ptrData[2]->alertLow, 5, 2, sensor3low);
  server.send(200, "text/plane", sensor3low);
}
void handleData_currentSensor4low() {
  char sensor4low[10];
  dtostrf(ptrData[3]->alertLow, 5, 2, sensor4low);
  server.send(200, "text/plane", sensor4low);
}
void handleData_currentSensor5low() {
  char sensor5low[10];
  dtostrf(ptrData[4]->alertLow, 5, 2, sensor5low);
  server.send(200, "text/plane", sensor5low);
}

void handleData_currentSensor6low() {
  char sensor6low[10];
  dtostrf(ptrData[5]->alertLow, 5, 2, sensor6low);
  server.send(200, "text/plane", sensor6low);
}

void handleData_currentSensor7low() {
  char sensor7low[10];
  dtostrf(ptrData[6]->alertLow, 5, 2, sensor7low);
  server.send(200, "text/plane", sensor7low);
}

void handleData_currentSensor8low() {
  char sensor8low[10];
  dtostrf(ptrData[7]->alertLow, 5, 2, sensor8low);
  server.send(200, "text/plane", sensor8low);
}
void handleData_currentSensor9low() {
  char sensor9low[10];
  dtostrf(ptrData[8]->alertLow, 5, 2, sensor9low);
  server.send(200, "text/plane", sensor9low);
}
void handleData_currentSensor10low() {
  char sensor10low[10];
  dtostrf(ptrData[9]->alertLow, 5, 2, sensor10low);
  server.send(200, "text/plane", sensor10low);
}

// =========================================================
// Send Current Alert High
// =========================================================

void handleData_currentSensor1high() {
  char sensor1high[10];
  dtostrf(ptrData[0]->alertHigh, 5, 2, sensor1high);
  server.send(200, "text/plane", sensor1high);
}
void handleData_currentSensor2high() {
  char sensor2high[10];
  dtostrf(ptrData[1]->alertHigh, 5, 2, sensor2high);
  server.send(200, "text/plane", sensor2high);
}
void handleData_currentSensor3high() {
  char sensor3high[10];
  dtostrf(ptrData[2]->alertHigh, 5, 2, sensor3high);
  server.send(200, "text/plane", sensor3high);
}
void handleData_currentSensor4high() {
  char sensor4high[10];
  dtostrf(ptrData[3]->alertHigh, 5, 2, sensor4high);
  server.send(200, "text/plane", sensor4high);
}
void handleData_currentSensor5high() {
  char sensor5high[10];
  dtostrf(ptrData[4]->alertHigh, 5, 2, sensor5high);
  server.send(200, "text/plane", sensor5high);
}

void handleData_currentSensor6high() {
  char sensor6high[10];
  dtostrf(ptrData[5]->alertHigh, 5, 2, sensor6high);
  server.send(200, "text/plane", sensor6high);
}

void handleData_currentSensor7high() {
  char sensor7high[10];
  dtostrf(ptrData[6]->alertHigh, 5, 2, sensor7high);
  server.send(200, "text/plane", sensor7high);
}

void handleData_currentSensor8high() {
  char sensor8high[10];
  dtostrf(ptrData[7]->alertHigh, 5, 2, sensor8high);
  server.send(200, "text/plane", sensor8high);
}
void handleData_currentSensor9high() {
  char sensor9high[10];
  dtostrf(ptrData[8]->alertHigh, 5, 2, sensor9high);
  server.send(200, "text/plane", sensor9high);
}
void handleData_currentSensor10high() {
  char sensor10high[10];
  dtostrf(ptrData[9]->alertHigh, 5, 2, sensor10high);
  server.send(200, "text/plane", sensor10high);
}


// =========================================================
// Send Display related info
// =========================================================

void handleData_alertType() {
  server.send(200, "text/plane", alertTypeText[config_alertType]);
}

void handleData_displayUpdate() {
  char dispRate[10];
  sprintf(dispRate, "%d", selectedDisplayRate);
  server.send(200, "text/plane", dispRate);
}

void handleData_displayBrightnessHigh() {
  char dispHigh[10];
  sprintf(dispHigh, "%d", brightness[0]);
  server.send(200, "text/plane", dispHigh);
}

void handleData_displayBrightnessLow() {
  char dispLow[10];
  sprintf(dispLow, "%d", brightness[1]);
  server.send(200, "text/plane", dispLow);
}


// =========================================================
// Send Arc related info
// =========================================================

void handleData_inArcColor() {
  server.send(200, "text/plane", arcColors[arcColor1]);
}

void handleData_outArcColor() {
  server.send(200, "text/plane", arcColors[arcColor2]);
}

void handleData_inArcWidth() {
  char inarcSegW[10];
  sprintf(inarcSegW, "%d", arcSeg1);
  server.send(200, "text/plane", inarcSegW);
}

void handleData_inArcIncrement() {
  char inarcSegi[10];
  sprintf(inarcSegi, "%d", arcInc1);
  server.send(200, "text/plane", inarcSegi);
}


void handleData_outArcWidth() {
  char outarcSegW[10];
  sprintf(outarcSegW, "%d", arcSeg2);
  server.send(200, "text/plane", outarcSegW);
}

void handleData_outArcIncrement() {
  char outarcSegi[10];
  sprintf(outarcSegi, "%d", arcInc2);
  server.send(200, "text/plane", outarcSegi);
}



// =========================================================
// Send Text color related info
// =========================================================


// =========================================================
// Send LED related info
// =========================================================
void handleData_ledColor() {
  server.send(200, "text/plane", ledColorName[LEDcolor]);
}

void handleData_ledStyle() {
  server.send(200, "text/plane", ledStyleName[LEDstyle]);
}

void handleData_boot1(){
  server.send(200, "text/plane", bootLogoNames[bootLogo1]);
}

void handleData_boot2(){
  server.send(200, "text/plane", bootLogoNames[bootLogo2]);
}

void handleData_boot3(){
  server.send(200, "text/plane", bootLogoNames[bootLogo3]);
}

void handleData_bootLevel() {
  server.send(200, "text/plane", bootLogoLevel[quickstart]);
}

void handleData_bootTime() {
  char bootTime[10];
  sprintf(bootTime, "%d", logoTime_ms);
  server.send(200, "text/plane", bootTime);
}

void handleData_ledBrightnessHigh() {
  char ledHigh[10];
  sprintf(ledHigh, "%d", brightness[2]);
  server.send(200, "text/plane", ledHigh);
}

void handleData_ledBrightnessLow() {
  char ledLow[10];
  sprintf(ledLow, "%d", brightness[3]);
  server.send(200, "text/plane", ledLow);
}

void handleData_ledCustomColor1_R() {
  char ledR1[10];
  sprintf(ledR1, "%d", LEDred[3][0]);
  server.send(200, "text/plane", ledR1);
}

void handleData_ledCustomColor2_R() {
  char ledR2[10];
  sprintf(ledR2, "%d", LEDred[3][1]);
  server.send(200, "text/plane", ledR2);
}

void handleData_ledCustomColor3_R() {
  char ledR3[10];
  sprintf(ledR3, "%d", LEDred[3][2]);
  server.send(200, "text/plane", ledR3);
}

void handleData_ledCustomColor4_R() {
  char ledR4[10];
  sprintf(ledR4, "%d", LEDred[3][3]); 
  server.send(200, "text/plane", ledR4);
}

void handleData_ledCustomColor5_R() {
  char ledR5[10];
  sprintf(ledR5, "%d", LEDred[3][4]);
  server.send(200, "text/plane", ledR5);
}

void handleData_ledCustomColor6_R() {
  char ledR6[10];
  sprintf(ledR6, "%d", LEDred[3][5]);
  server.send(200, "text/plane", ledR6);
}

void handleData_ledCustomColor1_G() {
  char ledG1[10];
  sprintf(ledG1, "%d", LEDgreen[3][0]);
  server.send(200, "text/plane", ledG1);
}

void handleData_ledCustomColor2_G() {
  char ledG2[10];
  sprintf(ledG2, "%d", LEDgreen[3][1]);
  server.send(200, "text/plane", ledG2);
}

void handleData_ledCustomColor3_G() {
  char ledG3[10];
  sprintf(ledG3, "%d", LEDgreen[3][2]);
  server.send(200, "text/plane", ledG3);
}

void handleData_ledCustomColor4_G() {
  char ledG4[10];
  sprintf(ledG4, "%d", LEDgreen[3][3]);
  server.send(200, "text/plane", ledG4);
}

void handleData_ledCustomColor5_G() {
  char ledG5[10];
  sprintf(ledG5, "%d", LEDgreen[3][4]);
  server.send(200, "text/plane", ledG5);
}

void handleData_ledCustomColor6_G() {
  char ledG6[10];
  sprintf(ledG6, "%d", LEDgreen[3][5]);
  server.send(200, "text/plane", ledG6);
}

void handleData_ledCustomColor1_B() {
  char ledB1[10];
  sprintf(ledB1, "%d", LEDblue[3][0]);
  server.send(200, "text/plane", ledB1);
}

void handleData_ledCustomColor2_B() {
  char ledB2[10];
  sprintf(ledB2, "%d", LEDblue[3][1]);
  server.send(200, "text/plane", ledB2);
}

void handleData_ledCustomColor3_B() {
  char ledB3[10];
  sprintf(ledB3, "%d", LEDblue[3][2]);
  server.send(200, "text/plane", ledB3);
}

void handleData_ledCustomColor4_B() {
  char ledB4[10];
  sprintf(ledB4, "%d", LEDblue[3][3]);
  server.send(200, "text/plane", ledB4);
}

void handleData_ledCustomColor5_B() {
  char ledB5[10];
  sprintf(ledB5, "%d", LEDblue[3][4]);
  server.send(200, "text/plane", ledB5);
}

void handleData_ledCustomColor6_B() {
  char ledB6[10];
  sprintf(ledB6, "%d", LEDblue[3][5]);
  server.send(200, "text/plane", ledB6);
}


/*

    Setup the WiFi connection and prepare
*/

void otaSetup(void) {

#ifdef WIFI_STA_MODE

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid_sta, password_sta);

#else
  WiFi.mode(WIFI_AP);
  IPAddress ip(192, 168, 4, 1);
  IPAddress gateway(192, 168, 4, 1);
  IPAddress subnet(255, 255, 255, 0);

  WiFi.softAPConfig(ip, ip, subnet);
  WiFi.softAP(ssid, password);


  if (!MDNS.begin(host)) {
    //Serial.println("Error setting up MDNS responder!");
    while (1) {
      delay(100);
    }
  }
  //Serial.println("mDNS responder started");

  //Serial.println("TCP server started");

  // Add service to MDNS-SD
  MDNS.addService("http", "tcp", 80);

#endif

  server.on("/jquery.min.js", HTTP_GET, onJavaScript);

  server.on("/reset", HTTP_GET, [] {
    ESP.restart();
  });

  server.on("/resetDefaults", HTTP_GET, [] {
    setToDefaults = true;
    checkNvsVer();

    ESP.restart();
  });

  server.on("/version", handleVersion);
  server.on("/note", handleNote);
  server.on("/hardware", handleHardware);

  server.on("/gaugeConfig", handleData_currentConfig);
  server.on("/gaugeType", handleData_currentType);

  server.on("/sensor1", handleData_currentSensor1);
  server.on("/sensor2", handleData_currentSensor2);
  server.on("/sensor3", handleData_currentSensor3);
  server.on("/sensor4", handleData_currentSensor4);
  server.on("/sensor5", handleData_currentSensor5);
  server.on("/sensor6", handleData_currentSensor6);
  server.on("/sensor7", handleData_currentSensor7);
  server.on("/sensor8", handleData_currentSensor8);
  server.on("/sensor9", handleData_currentSensor9);
  server.on("/sensor10", handleData_currentSensor10);

  server.on("/sensor1min", handleData_currentSensor1min);
  server.on("/sensor2min", handleData_currentSensor2min);
  server.on("/sensor3min", handleData_currentSensor3min);
  server.on("/sensor4min", handleData_currentSensor4min);
  server.on("/sensor5min", handleData_currentSensor5min);
  server.on("/sensor6min", handleData_currentSensor6min);
  server.on("/sensor7min", handleData_currentSensor7min);
  server.on("/sensor8min", handleData_currentSensor8min);
  server.on("/sensor9min", handleData_currentSensor9min);
  server.on("/sensor10min", handleData_currentSensor10min);

  server.on("/sensor1max", handleData_currentSensor1max);
  server.on("/sensor2max", handleData_currentSensor2max);
  server.on("/sensor3max", handleData_currentSensor3max);
  server.on("/sensor4max", handleData_currentSensor4max);
  server.on("/sensor5max", handleData_currentSensor5max);
  server.on("/sensor6max", handleData_currentSensor6max);
  server.on("/sensor7max", handleData_currentSensor7max);
  server.on("/sensor8max", handleData_currentSensor8max);
  server.on("/sensor9max", handleData_currentSensor9max);
  server.on("/sensor10max", handleData_currentSensor10max);

  server.on("/sensor1low", handleData_currentSensor1low);
  server.on("/sensor2low", handleData_currentSensor2low);
  server.on("/sensor3low", handleData_currentSensor3low);
  server.on("/sensor4low", handleData_currentSensor4low);
  server.on("/sensor5low", handleData_currentSensor5low);
  server.on("/sensor6low", handleData_currentSensor6low);
  server.on("/sensor7low", handleData_currentSensor7low);
  server.on("/sensor8low", handleData_currentSensor8low);
  server.on("/sensor9low", handleData_currentSensor9low);
  server.on("/sensor10low", handleData_currentSensor10low);

  server.on("/sensor1high", handleData_currentSensor1high);
  server.on("/sensor2high", handleData_currentSensor2high);
  server.on("/sensor3high", handleData_currentSensor3high);
  server.on("/sensor4high", handleData_currentSensor4high);
  server.on("/sensor5high", handleData_currentSensor5high);
  server.on("/sensor6high", handleData_currentSensor6high);
  server.on("/sensor7high", handleData_currentSensor7high);
  server.on("/sensor8high", handleData_currentSensor8high);
  server.on("/sensor9high", handleData_currentSensor9high);
  server.on("/sensor10high", handleData_currentSensor10high);

  server.on("/alertType", handleData_alertType);
  server.on("/displayRate", handleData_displayUpdate);
  server.on("/displayHigh", handleData_displayBrightnessHigh);
  server.on("/displayLow", handleData_displayBrightnessLow);

  server.on("/innerArcColor", handleData_inArcColor);
  server.on("/innerArcWidth", handleData_inArcWidth);
  server.on("/innerArcIncrement", handleData_inArcIncrement);

  server.on("/outerArcColor", handleData_outArcColor);
  server.on("/outerArcWidth", handleData_outArcWidth);
  server.on("/outerArcIncrement", handleData_outArcIncrement);

  server.on("/ledColor", handleData_ledColor);
  server.on("/ledStyle", handleData_ledStyle);
  server.on("/ledHigh", handleData_ledBrightnessHigh);
  server.on("/ledLow", handleData_ledBrightnessLow);


  server.on("/led1", handleData_ledCustomColor1_R);
  server.on("/led2", handleData_ledCustomColor1_G);
  server.on("/led3", handleData_ledCustomColor1_B);
  server.on("/led4", handleData_ledCustomColor2_R);
  server.on("/led5", handleData_ledCustomColor2_G);
  server.on("/led6", handleData_ledCustomColor2_B);
  server.on("/led7", handleData_ledCustomColor3_R);
  server.on("/led8", handleData_ledCustomColor3_G);
  server.on("/led9", handleData_ledCustomColor3_B);
  server.on("/led10", handleData_ledCustomColor4_R);
  server.on("/led11", handleData_ledCustomColor4_G);
  server.on("/led12", handleData_ledCustomColor4_B);
  server.on("/led13", handleData_ledCustomColor5_R);
  server.on("/led14", handleData_ledCustomColor5_G);
  server.on("/led15", handleData_ledCustomColor5_B);
  server.on("/led16", handleData_ledCustomColor6_R);
  server.on("/led17", handleData_ledCustomColor6_G);
  server.on("/led18", handleData_ledCustomColor6_B);

  server.on("/boot1", handleData_boot1);
  server.on("/boot2", handleData_boot2);
  server.on("/boot3", handleData_boot3);
  server.on("/bootTime", handleData_bootTime);
  server.on("/bootLevel", handleData_bootLevel);
  server.on("/testValue", handleDataTest);


  server.on("/test", HTTP_GET, [] {
    server.send(200, "text/html", testPage);
  });

  server.on("/", HTTP_GET, [] {
    server.send(200, "text/html", startPage);
  });

  server.on("/updateStart", HTTP_GET, [] {
    server.send(200, "text/html", updatePage);
  });

  server.on("/wifiConfig", HTTP_GET, [] {
    server.send(200, "text/html", wifiConfigPage);
  });

  server.on("/gaugeConfiguration", HTTP_GET, [] {
    server.send(200, "text/html", gaugeConfigPage2);
  });

  server.on("/displayConfiguration", HTTP_GET, [] {
    server.send(200, "text/html", displayConfigPage);
  });

  server.on("/ledConfiguration", HTTP_GET, [] {
    server.send(200, "text/html", ledConfigPage);
  });

  server.on("/sensorConfiguration", HTTP_GET, [] {
    server.send(200, "text/html", sensorConfigPage);
  });

    server.on("/boot", HTTP_GET, [] {
    server.send(200, "text/html", bootConfigPage);
  });

  server.on("/setLimitConfig", HTTP_GET, [] {
    String a, b, c, d, e;
    a = server.arg(0);
    b = server.arg(1);
    c = server.arg(2);
    d = server.arg(3);
    e = server.arg(4);

    selectedSensor = (int)(a.toFloat());
    newMin = b;
    newMax = c;
    newLow = d;
    newHigh = e;

    readyToUpdateLimits = true;

    server.send(200, "text/html", gaugeConfigPage2);
  });

  server.on("/setConfig", HTTP_GET, [] {
    String a;
    a = server.arg(0);

    config_selectedConfig[0] = (int)(a.toFloat());
    updateUserConfig = true;
    readyToUpdateGaugeConfig = true;


    server.send(200, "text/html", gaugeConfigPage2);
  });

  server.on("/setGaugeType", HTTP_GET, [] {
    String a;
    a = server.arg(0);

    //gaugeDisplayType = (int)(a.toFloat());
    config_gaugeStyle[config_selectedConfig[0]] = (int)(a.toFloat());
    updateUserConfig = true;
    readyToUpdateGaugeConfig = true;
    server.send(200, "text/html", gaugeConfigPage2);
  });


  server.on("/setAlertType", HTTP_GET, [] {
    String a;
    a = server.arg(0);

    config_alertType = (int)(a.toFloat());
    updateUserConfig = true;
    readyToUpdateGaugeConfig = true;
    server.send(200, "text/html", displayConfigPage);
  });




  server.on("/setDisplayRate", HTTP_GET, [] {
    String a, b, c;
    a = server.arg(0);

    displayRefresh_ms = (int)(a.toFloat());
    readyToUpdateGaugeConfig = true;
    selectedDisplayRate = displayRefresh_ms;
    server.send(200, "text/html", displayConfigPage);
  });



  server.on("/setGaugeConfig", HTTP_GET, [] {
    String a, b, c;
    a = server.arg(0);
    b = server.arg(1);
    c = server.arg(2);

    selectedGauge = (int)(a.toFloat());
    selectedSensor = (int)(b.toFloat());

    config_sensorData[config_selectedConfig[0]][selectedGauge] = selectedSensor;
    //setupUserConfig();
    //resetDisplay = true;

    updateUserConfig = true;
    readyToUpdateGaugeConfig = true;

    server.send(200, "text/html", gaugeConfigPage2);
  });

  server.on("/setWifiConfig", HTTP_GET, [] {
    String a, b, c;
    a = server.arg(0);
    b = server.arg(1);
    c = server.arg(2);

    strncpy(newSSID, a.c_str(), 16);
    strncpy(newPW, b.c_str(), 16);
    strncpy(newHOST, c.c_str(), 16);

    // newSSID = server.arg(0);
    // newPW = server.arg(1);
    updateWifiConfig = true;

    server.send(200, "text/html", wifiConfigPage);
  });

  server.on("/setLedColor", HTTP_GET, [] {
    String a, b;
    a = server.arg(0);
    b = server.arg(1);

    LEDcolor = (int)(a.toInt());
    LEDstyle = (int)(b.toInt());

    config_ledStyle[config_selectedConfig[0]] = LEDstyle;
    config_ledColors[config_selectedConfig[0]] = LEDcolor;

    updateUserConfig = true;
    readyToUpdateGaugeConfig = true;

    //saveLedConfig();

    server.send(200, "text/html", ledConfigPage);
  });

  server.on("/setLEDCustom", HTTP_GET, [] {
    // Setup LED values taken from user input if value is present. If not then keep the current value
    // Convert input value to 255 from 100

    for (int ledInd = 0; ledInd < 6; ledInd++) {
      int indexInc = ledInd * 3;

      if (server.arg(indexInc) != "") {
        LEDred[3][ledInd] = ((int)(server.arg(indexInc).toInt()));
      }

      if (server.arg(indexInc + 1) != "") {
        LEDgreen[3][ledInd] = ((int)(server.arg(indexInc + 1).toInt()));
      }

      if (server.arg(indexInc + 2) != "") {
        LEDblue[3][ledInd] = ((int)(server.arg(indexInc + 2).toInt()));
      }
    }

    saveNewLedColor();
    server.send(200, "text/html", ledConfigPage);
  });


  server.on("/setTextColor", HTTP_GET, [] {
    String a, b;
    a = server.arg(0);
    b = server.arg(1);

    //selectedColor[(int)(a.toInt())] = (int)(b.toInt());
    config_uiColors[config_selectedConfig[0]][(int)(a.toInt())] = (int)(b.toInt());

    updateUserConfig = true;
    readyToUpdateGaugeConfig = true;

    //saveTextConfig();

    server.send(200, "text/html", displayConfigPage);
  });

  server.on("/bootConfig", HTTP_GET, [] {
    String a, b, c, d, e;
    a = server.arg(0);
    b = server.arg(1);
    c = server.arg(2);
    d = server.arg(3);
    e = server.arg(4);

    bootLogo1 = (int)(a.toInt());
    bootLogo2 = (int)(b.toInt());
    bootLogo3 = (int)(c.toInt());

    quickstart = (int)(d.toInt());
    logoTime_ms = (int)(e.toInt());

    saveBootConfig();
    server.send(200, "text/html", bootConfigPage);
  });



  server.on("/setBrightness", HTTP_GET, [] {
    String a, b, c;
    a = server.arg(0);
    b = server.arg(1);
    c = server.arg(2);

    selectedBrightness = (int)(a.toFloat());
    brightnessInput = (int)(b.toFloat());
    brightnessInput2 = (int)(b.toFloat());

    if (brightnessInput > 100) {
      brightnessInput = 100;
    }

    if (brightnessInput < 0) {
      brightnessInput = 0;
    }

    if (brightnessInput2 > 100) {
      brightnessInput2 = 100;
    }

    if (brightnessInput2 < 0) {
      brightnessInput2 = 0;
    }

    if (b != "") {
      brightness[selectedBrightness] = brightnessInput;
    }

    if (c != "") {
      brightness[selectedBrightness + 1] = brightnessInput2;
    }

    readyToUpdateGaugeConfig = true;
    server.send(200, "text/html", gaugeConfigPage2);
  });

  server.on("/setBrightnessDisplay", HTTP_GET, [] {
    String a, b;
    a = server.arg(0);
    b = server.arg(1);

    selectedBrightness = 0;
    brightnessInput = (int)(a.toFloat());
    brightnessInput2 = (int)(b.toFloat());

    if (brightnessInput > 100) {
      brightnessInput = 100;
    }

    if (brightnessInput < 0) {
      brightnessInput = 0;
    }

    if (brightnessInput2 > 100) {
      brightnessInput2 = 100;
    }

    if (brightnessInput2 < 0) {
      brightnessInput2 = 0;
    }

    if (a != "") {
      brightness[selectedBrightness] = brightnessInput;
    }

    if (b != "") {
      brightness[selectedBrightness + 1] = brightnessInput2;
    }

    readyToUpdateGaugeConfig = true;
    server.send(200, "text/html", displayConfigPage);
  });

  server.on("/setBrightnessLeds", HTTP_GET, [] {
    String a, b;
    a = server.arg(0);
    b = server.arg(1);

    selectedBrightness = 2;
    brightnessInput = (int)(a.toFloat());
    brightnessInput2 = (int)(b.toFloat());

    if (brightnessInput > 100) {
      brightnessInput = 100;
    }

    if (brightnessInput < 0) {
      brightnessInput = 0;
    }

    if (brightnessInput2 > 100) {
      brightnessInput2 = 100;
    }

    if (brightnessInput2 < 0) {
      brightnessInput2 = 0;
    }

    if (a != "") {
      brightness[selectedBrightness + 1] = brightnessInput;
    }

    if (b != "") {
      brightness[selectedBrightness] = brightnessInput2;
    }

    readyToUpdateGaugeConfig = true;
    server.send(200, "text/html", ledConfigPage);
  });

  server.on("/setArc1", HTTP_GET, [] {
    String a, b, c;
    a = server.arg(0);
    b = server.arg(1);
    c = server.arg(2);

    arcColor1 = (int)(a.toFloat());

    arcSeg1 = (int)(b.toFloat());
    if (arcSeg1 == 0) {
      arcSeg1 = 3;
    }

    arcInc1 = (int)(c.toFloat());
    if (arcInc1 == 0) {
      arcInc1 = 6;
    }

    updateArcConfig = true;
    updatedArc = true;

    server.send(200, "text/html", displayConfigPage);
  });

  server.on("/setArc2", HTTP_GET, [] {
    String a, b, c;
    a = server.arg(0);
    b = server.arg(1);
    c = server.arg(2);

    arcColor2 = (int)(a.toFloat());

    arcSeg2 = (int)(b.toFloat());
    if (arcSeg2 == 0) {
      arcSeg2 = 3;
    }

    arcInc2 = (int)(c.toFloat());
    if (arcInc2 == 0) {
      arcInc2 = 3;
    }

    updatedArc = true;
    updateArcConfig = true;
    server.send(200, "text/html", displayConfigPage);
  });

  server.on(
    "/update", HTTP_POST, []() {
      server.sendHeader("Connection", "close");
      server.send(200, "text/plain", (Update.hasError()) ? "FAIL" : "OK");
      ESP.restart();
    },

    []() {
      HTTPUpload &upload = server.upload();

      // Uploading File
      if (upload.status == UPLOAD_FILE_START) {

        // Serial.printf("Update: %s\n", upload.filename.c_str());
        if (!Update.begin(UPDATE_SIZE_UNKNOWN)) {  // start with max available size
          Update.printError(Serial);
        }
      }
      // File Uploaded, flash
      else if (upload.status == UPLOAD_FILE_WRITE) {

        /* flashing firmware to ESP*/
        if (Update.write(upload.buf, upload.currentSize) != upload.currentSize) {
          Update.printError(Serial);
        }
      }

      // Update finished
      else if (upload.status == UPLOAD_FILE_END) {
        //  If update is a success
        if (Update.end(true)) {
        }
        // If update fails
        else {
          // Update.printError(Serial);
        }
      }
    });
  // Start TCP (HTTP) server
  server.begin();
  wifiEnabled = true;
}

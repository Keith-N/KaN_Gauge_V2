/*

  'wifi.h'

  Sets up wireless accesspoint, configuration pages, and OTA handling
  Recieves and formats user inputs, indicates that configuration is ready for updating 

*/

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
#include "pages.h"

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

void disableWifi()
{

  WiFi.mode(WIFI_OFF);
  wifiEnabled = false;
}

void ota(void)
{
  server.handleClient();
}

/*
    When JS is required send the GZ JQuery 3.2.1
*/
void onJavaScript(void)
{

  //Serial.println("onJavaScript(void)");

  server.setContentLength(jquery_min_js_v3_2_1_gz_len);
  server.sendHeader(F("Content-Encoding"), F("gzip"));
  server.send_P(200, "text/javascript", jquery_min_js_v3_2_1_gz, jquery_min_js_v3_2_1_gz_len);
}

/*
    Setup the WiFi connection and prepare
*/

void otaSetup(void)
{

  WiFi.mode(WIFI_AP);
  IPAddress ip(192,168,4,1);
  IPAddress gateway(192,168,4,1);
  IPAddress subnet(255,255,255,0);

  WiFi.softAPConfig(ip, ip, subnet);
  WiFi.softAP(ssid, password);


  if (!MDNS.begin(host))
  {
    //Serial.println("Error setting up MDNS responder!");
    while (1)
    {
      delay(100);
    }
  }
  //Serial.println("mDNS responder started");

  // Start TCP (HTTP) server
  server.begin();
  
  //Serial.println("TCP server started");

  // Add service to MDNS-SD
  MDNS.addService("http", "tcp", 80);

  server.on("/jquery.min.js", HTTP_GET, onJavaScript);

  server.on("/reset", HTTP_GET, []
            { ESP.restart(); });

  server.on("/resetDefaults", HTTP_GET, []
            { 
              setToDefaults = true;
              checkNvsVer();
              
              ESP.restart(); });


  server.on("/", HTTP_GET, []
            { server.send(200, "text/html", startPage); });

  server.on("/updateStart", HTTP_GET, []
            { server.send(200, "text/html", update1); });

  server.on("/wifiConfig", HTTP_GET, []
            { server.send(200, "text/html", wifiConfigPage); });

  server.on("/gaugeConfig", HTTP_GET, []
            { server.send(200, "text/html", gaugeConfigPage); });

  server.on("/setLimitConfig", HTTP_GET, []
            {
    String a, b, c;
    a = server.arg(0);
    b = server.arg(1);
    c = server.arg(2);

    selectedSensor = (int) (a.toFloat());
    selectedLimit = (int) (b.toFloat());
    inputNewValue = c.toFloat();

    readyToUpdateLimits = true;
    server.send(200, "text/html", gaugeConfigPage); 
    });

server.on("/setGaugeType", HTTP_GET, []
            {
    String a;
    a = server.arg(0);

    gaugeDisplayType = (int) (a.toFloat());
    resetDisplay= true;
    updateGaugeType = true;
    server.send(200, "text/html", gaugeConfigPage); 
    });


  server.on("/setDisplayRate", HTTP_GET, []
            {
    String a, b, c;
    a = server.arg(0);

    displayRefresh_ms = (int) (a.toFloat());
    readyToUpdateGaugeConfig = true;
    server.send(200, "text/html", gaugeConfigPage); 
    });



  server.on("/setGaugeConfig", HTTP_GET, []
            {
    String a, b, c;
    a = server.arg(0);
    b = server.arg(1);
    c = server.arg(2);

    selectedGauge = (int) (a.toFloat());
    selectedSensor = (int) (b.toFloat());

    readyToUpdateGaugeConfig = true;
    server.send(200, "text/html", gaugeConfigPage); 
    });

  server.on("/setWifiConfig", HTTP_GET, []
            {
 
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

  server.on("/setLedColor", HTTP_GET, []
            {
      String a, b;
      a = server.arg(0);
      b = server.arg(1);

      LEDcolor = (int) (a.toInt());
      LEDstyle = (int) (b.toInt());

      saveLedConfig();

      server.send(200, "text/html", gaugeConfigPage); 
      });

  server.on("/setLEDCustom", HTTP_GET, []
            {
      String a, r, g, b;
      a = server.arg(0);
      r = server.arg(1);
      g = server.arg(2);
      b = server.arg(3);

      int LEDindex = (int) (a.toInt());
      int LEDcolorRed = (int) (r.toInt());
      int LEDcolorGreen = (int) (g.toInt());
      int LEDcolorBlue = (int) (b.toInt());

      saveNewLedColor(LEDindex, LEDcolorRed, LEDcolorGreen, LEDcolorBlue);


      saveLedConfig();
      server.send(200, "text/html", gaugeConfigPage); 
      });


  server.on("/setTextColor", HTTP_GET, []
            {
      String a, b;
      a = server.arg(0);
      b = server.arg(1);

      selectedColor[(int) (a.toInt())] = (int) (b.toInt());
      saveTextConfig();

      server.send(200, "text/html", gaugeConfigPage); 
      });

  server.on("/boot", HTTP_GET, []
            {
 
    String a, b, c, d, e ,f;
    a = server.arg(0);
    b = server.arg(1);
    c = server.arg(2);
    d = server.arg(3);
    e = server.arg(4);
    f = server.arg(5);

    bootLogo1 = (int) (a.toInt());
    bootLogo2 = (int) (b.toInt());
    bootLogo3 = (int) (c.toInt());

    // Make sure we keep the correct PCB rev
    int revbuf = pcbRev;
    pcbRev = (int) (d.toFloat());
    if (pcbRev == 0){
      pcbRev = revbuf;
    }

    quickstart = (int) (e.toInt());
    logoTime_ms = (int) (f.toInt());

    saveBootConfig();
    server.send(200, "text/html", bootConfigPage); 
    });

  server.on("/setBrightness", HTTP_GET, []
            {
    String a, b, c;
    a = server.arg(0);
    b = server.arg(1);

    selectedBrightness = (int) (a.toFloat());
    brightnessInput = (int) (b.toFloat());

    if (brightnessInput > 100){
      brightnessInput = 100;
    }

    if (brightnessInput < 0){
      brightnessInput = 0;
    }

    brightness[selectedBrightness] = brightnessInput;

    readyToUpdateGaugeConfig = true;
    server.send(200, "text/html", gaugeConfigPage); 
    });

  server.on("/setArc1", HTTP_GET, []
            {
    String a, b, c;
    a = server.arg(0);
    b = server.arg(1);
    c = server.arg(2);

    arcColor1 = (int) (a.toFloat());

    arcSeg1 = (int) (b.toFloat());
        if (arcSeg1 == 0){
      arcSeg1 = 3;
    }

    arcInc1 = (int) (c.toFloat());
    if (arcInc1 == 0){
      arcInc1 = 6;
    }

    updateArcConfig = true;
    updatedArc = true;
    server.send(200, "text/html", gaugeConfigPage); 
    });

  server.on("/setArc2", HTTP_GET, []
            {
    String a, b, c;
    a = server.arg(0);
    b = server.arg(1);
    c = server.arg(2);

    arcColor2 = (int) (a.toFloat());

    arcSeg2 = (int) (b.toFloat());
    if (arcSeg2 == 0){
      arcSeg2 = 3;
    }

    arcInc2 = (int) (c.toFloat());
    if (arcInc2 == 0){
      arcInc2 = 3;
    }
    
    updatedArc = true;
    updateArcConfig = true;
    server.send(200, "text/html", gaugeConfigPage); 
    });

  server.on(
      "/update", HTTP_POST, []()
      {
    server.sendHeader("Connection", "close");
    server.send(200, "text/plain", (Update.hasError()) ? "FAIL" : "OK");
    ESP.restart(); },

      []()
      {
        HTTPUpload &upload = server.upload();

        // Uploading File
        if (upload.status == UPLOAD_FILE_START)
        {

          // Serial.printf("Update: %s\n", upload.filename.c_str());
          if (!Update.begin(UPDATE_SIZE_UNKNOWN))
          { // start with max available size
            Update.printError(Serial);
          }
        }
        // File Uploaded, flash
        else if (upload.status == UPLOAD_FILE_WRITE)
        {

          /* flashing firmware to ESP*/
          if (Update.write(upload.buf, upload.currentSize) != upload.currentSize)
          {
            Update.printError(Serial);
          }
        }

        // Update finished
        else if (upload.status == UPLOAD_FILE_END)
        {
          //  If update is a success
          if (Update.end(true))
          {
          }
          // If update fails
          else
          {
            // Update.printError(Serial);
          }
        }
      });

      wifiEnabled = true;
}

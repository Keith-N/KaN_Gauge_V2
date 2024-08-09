/*
  KaN Gauge V2
  08-08-2024
  v0.40

  Build target ESP32 S3

  Extract libraries included in /libraries to your libraries directory 
    Typically ".../Arduino/liberaries/" in User/Documents directory
  Includes:
    Adafruit_NeoPixel 1.12.0
    PNGdec            1.0.1
    SimpleCLI         1.1.4
    TFT_eSPI          2.5.34  (modified, to properly configure user setup)
    TFT_eWidget       0.0.5   (modified, to adjust meter)

  Using libraries from library manager / github should be okay, but will require modifications to the TFT_eSPI libraries.
  
*/


//==============================================
//  Libraries
//==============================================

#include "driver/twai.h"
#include <Arduino.h>
#include <Wire.h>

#include "wifi.h"
#include "display.h"
#include "pinMap.h"
#include "DataFunctions.h"
#include "SensorData.h"
#include "config.h"
#include "led.h"
#include "nvs.h"
#include "cli.h"
#include "gauge.h"
#include "can.h"


int loopTimer_ms = 0;
int loopStart_ms = 0;
int st = 0;

int sInput;

#define DEBUG_SERIAL
#define NVS
#define WIFI_OTA
#define CLI
#define DEMO

int lastInput_D1 = 0;
int debounceTimerD1 = 600;
bool buttonPressD1 = false;

// Button Input ISR

void inputButtonD1_ISR() {

  if ((millis() - lastInput_D1) > debounceTimerD1) {
    buttonPressD1 = true;
    lastInput_D1 = millis();
#ifdef DEBUG_SERIAL
    Serial.println("button pressed");
#endif
  }
}


//==============================================
// Tasks
//==============================================


/*
Task to handle CAN processing
Runs on core 0
*/

void setupCanTask() {

#ifdef DEBUG_SERIAL
  Serial.println("Setting up CAN task");
#endif

  // Use core 0 for processing CAN messages
  xTaskCreatePinnedToCore(
    canReceiveTask,   /* Function to implement the task */
    "CAN_RX",         /* Name of the task */
    4096,             /* Stack size in words */
    NULL,             /* Task input parameter */
    tskIDLE_PRIORITY, /* Priority of the task */
    NULL,             /* Task handle. */
    0);               /* Core where the task should run */
  st++;
}


/*
Setup the display task
Runs on core 1
*/
void setupDisplayTask() {

#ifdef DEBUG_SERIAL
  Serial.println("Setting up display task");
#endif

  xTaskCreatePinnedToCore(
    updateDisplayTask, /* Function to implement the task */
    "UPDATE_DISPLAY",  /* Name of the task */
    4096,              /* Stack size in words */
    NULL,              /* Task input parameter */
    1,                 /* Priority of the task */
    NULL,              /* Task handle. */
    1);                /* Core where the task should run */
  st++;
}


/*
Task to respond to user inputs
Includes wifi, CLI, and incrementing test data
*/

void inputTask(void *pvParameters) {
  for (;;) {
    if (wifiEnabled == true) {
      ota();
    }

#ifdef CLI
    CLItask();
#endif

    checkNewConfig();

#ifdef DEMO
    incrementTestData();
#endif

    buttonPressD1 = nextConfigCheck(buttonPressD1);
  }
}


/*
Setup the input task
Runs on core 1
*/
void setupInputTask() {

#ifdef DEBUG_SERIAL
  Serial.println("Setting up input task");
#endif

  xTaskCreatePinnedToCore(
    inputTask,     /* Function to implement the task */
    "INPUT_CHECK", /* Name of the task */
    4096,          /* Stack size in words */
    NULL,          /* Task input parameter */
    1,             /* Priority of the task */
    NULL,          /* Task handle. */
    1);            /* Core where the task should run */
  st++;
}


//=========================================
// Configuration Restore
//=========================================

void startupConfig() {

  // Check the NVS version
  // Reset if old
  nvs_flash_init();
  checkNvsVer();

  // Restore user configurations
  restoreUserConfig();
  setupUserConfig();

  for (int p = 0; (p < numDataPtr); p++) {
    ptrData[p] = selectSensor(gaugeSensor[p]);
  }

  restoreSensorMinMax();
  restoreSensorAlerts();
  restoreWifi();
  restoreBootConfig();
  restoreLedColor();
  restoreArcConfig();
  restoreBrightnessSettings();
}

void checkWifiConfig() {

  // Check that Wifi credentials have something, if not default them so gauge can be accessed
  // Password must be 8 characters or more, password can be 0 for no password
  if (strlen(password) != 0 && strlen(password) < 8) {

    strncpy(password, default_password, 16);
    saveWifi();
    Serial.println("Short password, resetting to default!");

    Serial.print("PW : ");
    Serial.println(password);
  }

  if (strlen(ssid) == 0) {
    strncpy(ssid, default_ssid, 16);
    saveWifi();
    Serial.println("No SSID, resetting to default!");
    Serial.print("SSID : ");
    Serial.println(ssid);
  }

  if (strlen(host) == 0) {
    strncpy(host, default_host, 16);
    saveWifi();
    Serial.println("No host, resetting to default!");
    Serial.print("host : ");
    Serial.println(host);
  }
}

//==============================================
//  Setup
//==============================================

void setup() {
  //delay(3000);
  analogReadResolution(12);

  Serial.begin(115200);
  setupPinMode();
  attachInterrupt(USER_INPUT_D2, inputButtonD1_ISR, FALLING);

#ifdef DEBUG_SERIAL
  Serial.println("Setup ...");
  Serial.print("Build : ");
  Serial.println(build);
  Serial.print("Build Type : ");
  Serial.println(buildType);
  Serial.print("NVS : ");
  Serial.println(nvs);
#endif

#ifdef DEBUG_SERIAL
  Serial.println("Initializing Display ...");
#endif

  displayInit();
  setDisplayBrightness(dispBrightness);

#ifdef DEBUG_SERIAL
  Serial.println("Restoring saved configuration ...");
#endif

  startupConfig();

#ifdef DEBUG_SERIAL
  Serial.print("PCB Rev : ");
  Serial.println(pcbRev);
#endif

#ifdef DEBUG_SERIAL
  Serial.println("Initializing LEDs ...");
#endif

  ledInit();
  ledOff();

#ifdef DEBUG_SERIAL
  Serial.println("Showing boot ...");
  Serial.print("Boot 1 : ");
  Serial.println(bootLogo1);
  Serial.print("Boot 2 : ");
  Serial.println(bootLogo3);

#endif

  // Show boot logos
  showBootLogos(quickstart);

  if (startWifi == true) {

    checkWifiConfig();

#ifdef DEBUG_SERIAL
    Serial.println("Initializing WiFi...");
    Serial.print("SSID : ");
    Serial.println(ssid);
    Serial.print("PW : ");
    Serial.println(password);
    Serial.print("Name : ");
    Serial.println(host);
#endif

    otaSetup();

#ifdef DEBUG_SERIAL
    Serial.print("IP : ");
    Serial.println(WiFi.softAPIP());
#endif
  }

  if (startCan == true) {
    Serial.println("Initializing CAN...");
    canSetup();

#ifdef DEBUG_SERIAL
    Serial.println("Setting up Tasks...");
#endif

    setupCanTask();
  }

  setupDisplayTask();

#ifdef CLI
  setupCLI();
#endif

  setupInputTask();


#ifdef DEBUG_SERIAL
  Serial.println("Starting!");
#endif
}

//==============================================
//  Main Loop
//==============================================

/*
Nothing is done here, all functions are defined in tasks
*/

void loop() {
}

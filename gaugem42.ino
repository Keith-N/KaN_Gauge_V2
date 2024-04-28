/*
  KaN Gauge
  v0.x

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

twai_message_t CANMessage;
TaskHandle_t TASK_CAN;

int loopTimer_ms = 0;
int loopStart_ms = 0;
int lastAlert_ms = 0;
int alertTime_ms = 250;
int alertTime2_ms = 250;
int st = 0;

int sInput;

bool alertActive = false;
bool showAlert;
bool analogMeterSetup = false;
bool screenSet = false;

#define DEBUG_SERIAL
#define NVS
#define WIFI_OTA
#define CLI


//==============================================
//  CAN
//==============================================

/*
Setup CAN in Normal mode using GPIO defined in pinMap
Speed: 500k
No Filters
*/

void canSetup()
{

  twai_general_config_t g_config = TWAI_GENERAL_CONFIG_DEFAULT((gpio_num_t)CAN_TX, (gpio_num_t)CAN_RX, TWAI_MODE_NORMAL);
  // twai_general_config_t g_config = TWAI_GENERAL_CONFIG_DEFAULT((gpio_num_t)CAN_TX, (gpio_num_t)CAN_RX, TWAI_MODE_LISTEN_ONLY);
  twai_timing_config_t t_config = TWAI_TIMING_CONFIG_500KBITS();
  twai_filter_config_t f_config = TWAI_FILTER_CONFIG_ACCEPT_ALL();

  // Install TWAI driver
  if (twai_driver_install(&g_config, &t_config, &f_config) == ESP_OK)
  {
#ifdef DEBUG_SERIAL
    Serial.println("Driver installed");
#endif
  }
  else
  {
#ifdef DEBUG_SERIAL
    Serial.println("Failed to install driver");
#endif

    return;
  }

  // Start TWAI driver
  if (twai_start() == ESP_OK)
  {
    canEnabled = true;
#ifdef DEBUG_SERIAL
    Serial.println("Driver started");
#endif
  }
  else
  {
#ifdef DEBUG_SERIAL
    Serial.println("Failed to start driver");
#endif

    return;
  }
}

/*
When a CAN message is recieved, pass it to be processed and values saved
*/

void canReceive()
{

  if (twai_receive(&CANMessage, 0) == ESP_OK)
  {

    if (printCan == true)
    {
      Serial.print("0x");
      // id = CANMessage.identifier;
      Serial.print(CANMessage.identifier, HEX);
      Serial.print("\t");
      Serial.print(CANMessage.extd);
      Serial.print("\t");
      Serial.print(CANMessage.rtr);
      Serial.print("\t");
      Serial.print(CANMessage.data_length_code);
      for (int i = 0; i < CANMessage.data_length_code; i++)
      {
        Serial.print("\t0x");
        if (CANMessage.data[i] <= 0x0F)
        {
          Serial.print(0);
        }
        Serial.print(CANMessage.data[i], HEX);
      }
      Serial.println();
    }

    SAVE_CAN_DATA(CANMessage);
  }
}

void canReceiveTask(void *pvParameters)
{

#ifdef DEBUG_SERIAL
  Serial.print("CAN Task on core: ");
  Serial.println(xPortGetCoreID());
#endif

  for (;;)
  {
    canReceive();
  }
}

/*
Task to handle CAN processing
Runs on core 0
*/

void setupCanTask()
{

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

//==============================================
//  Gauges
//==============================================

/*
Updates the display based on the selected configurations
This includes two arcs across the top as well as 4 sets of digits
*/

void updateDisplay()
{
  int radius1 = 116;
  int radius2 = 80;
  int x_1 = 15;
  int y_1 = 17;

  int x_2 = x_1 + (radius1 - radius2) / 2;
  int y_2 = y_1 + (radius1 - radius2) / 2;

  // Inner
  if (ptrData[0]->dataName != "None")
  {
    gaugeArc(ptrData[0]->scaledValue, ptrData[0]->minimum, ptrData[0]->maximum, (gaugeposition_x + x_2 + 18), (gaugeposition_y + y_2 + 15), radius2,
             4, 240, arcColor1, arcSeg1, arcInc1);
    if (ptrData[0]->alert == true)
    {
      showAlert = true;
    }
  }

  // Outer
  if (ptrData[1]->dataName != "None")
  {
    gaugeArc(ptrData[1]->scaledValue, ptrData[1]->minimum, ptrData[1]->maximum, (gaugeposition_x + x_1), (gaugeposition_y + y_1), radius1,
             8, 240, arcColor2, arcSeg2, arcInc2);
    if (ptrData[1]->alert == true)
    {
      showAlert = true;
    }
  }

  // Center Top Text
  if (ptrData[2]->dataName != "None")
  {

    gaugeText(ptrData[2]->scaledValue, ptrData[2]->minimum, ptrData[2]->maximum, (120), (95), 1,
              ptrData[2]->units, ptrData[2]->dataName, selectedColor[0], selectedColor[1], TRUE, TRUE, 15, ptrData[2]->alert, selectedColor[2]);
    if (ptrData[2]->alert == true)
    {
      showAlert = true;
    }
  }

  // Lower Left
  if (ptrData[3]->dataName != "None")
  {

    gaugeText(ptrData[3]->scaledValue, ptrData[3]->minimum, ptrData[3]->maximum, (60), (190), 1,
              ptrData[3]->units, ptrData[3]->dataName, selectedColor[0], selectedColor[1], TRUE, TRUE, 15, ptrData[3]->alert, selectedColor[2]);
    if (ptrData[3]->alert == true)
    {
      showAlert = true;
    }
  }

  // Lower Text
  if (ptrData[4]->dataName != "None")
  {
    gaugeText(ptrData[4]->scaledValue, ptrData[4]->minimum, ptrData[4]->maximum, (120), (160), 1,
              ptrData[4]->units, ptrData[4]->dataName, selectedColor[0], selectedColor[1], TRUE, TRUE, 15, ptrData[4]->alert, selectedColor[2]);
    if (ptrData[4]->alert == true)
    {
      showAlert = true;
    }
  }

  // Right
  if (ptrData[5]->dataName != "None")
  {
    gaugeText(ptrData[5]->scaledValue, ptrData[5]->minimum, ptrData[5]->maximum, (180), (190), 1,
              ptrData[5]->units, ptrData[5]->dataName, selectedColor[0], selectedColor[1], TRUE, TRUE, 15, ptrData[5]->alert, selectedColor[2]);
    if (ptrData[5]->alert == true)
    {
      showAlert = true;
    }
  }

  if (showAlert == true)
  {

    if (millis() > (lastAlert_ms + alertTime_ms))
    {
      alertActive = !alertActive;
      lastAlert_ms = millis();
    }
    if (alertActive == true)
    {
      drawAlert(120, 210, 50, 1);
    }
    else if (alertActive == false)
    {
      drawAlert(120, 210, 50, 0);
    }
  }

  else
  {
    drawAlert(120, 210, 50, 0);
  }
}

/*
Updates the display based on the selected configurations
This is similar to the updateDisplay function with an increased size for the center digits
Includes one Arc and three sets of digits
*/

void updateDisplay_LargeText()
{

  int radius1 = 116;
  int radius2 = 80;
  int x_1 = 15;
  int y_1 = 17;

  int x_2 = x_1 + (radius1 - radius2) / 2;
  int y_2 = y_1 + (radius1 - radius2) / 2;

  // Outer
  if (ptrData[1]->dataName != "None")
  {
    gaugeArc(ptrData[1]->scaledValue, ptrData[1]->minimum, ptrData[1]->maximum, (gaugeposition_x + x_1), (gaugeposition_y + y_1), radius1,
             8, 240, arcColor2, arcSeg2, arcInc2);
    if (ptrData[1]->alert == true)
    {
      showAlert = true;
    }
  }

  // Center Top Text
  if (ptrData[2]->dataName != "None")
  {

    gaugeText(ptrData[2]->scaledValue, ptrData[2]->minimum, ptrData[2]->maximum, (120), (120), 4,
              ptrData[2]->units, ptrData[2]->dataName, selectedColor[0], selectedColor[1], TRUE, TRUE, 15, ptrData[2]->alert, selectedColor[2]);
    if (ptrData[2]->alert == true)
    {
      showAlert = true;
    }
  }

  // Lower Left
  if (ptrData[3]->dataName != "None")
  {
    gaugeText(ptrData[3]->scaledValue, ptrData[3]->minimum, ptrData[3]->maximum, (60), (190), 1,
              ptrData[3]->units, ptrData[3]->dataName, selectedColor[0], selectedColor[1], TRUE, TRUE, 15, ptrData[3]->alert, selectedColor[2]);
    if (ptrData[3]->alert == true)
    {
      showAlert = true;
    }
  }

  // Right
  if (ptrData[5]->dataName != "None")
  {
    gaugeText(ptrData[5]->scaledValue, ptrData[5]->minimum, ptrData[5]->maximum, (180), (190), 1,
              ptrData[5]->units, ptrData[5]->dataName, selectedColor[0], selectedColor[1], TRUE, TRUE, 15, ptrData[5]->alert, selectedColor[2]);
    if (ptrData[5]->alert == true)
    {
      showAlert = true;
    }
  }

  if (showAlert == true)
  {

    if (millis() > (lastAlert_ms + alertTime_ms))
    {
      alertActive = !alertActive;
      lastAlert_ms = millis();
    }
    if (alertActive == true)
    {
      drawAlert(120, 210, 50, 1);
    }
    else if (alertActive == false)
    {
      drawAlert(120, 210, 50, 0);
    }
  }

  else
  {
    drawAlert(120, 210, 50, 0);
  }
}


/*
Updates the display based on the selected configurations
Includes one large set of digits
*/

void updateDisplay_Large()
{

  int radius1 = 116;
  int radius2 = 80;
  int x_1 = 15;
  int y_1 = 17;

  int x_2 = x_1 + (radius1 - radius2) / 2;
  int y_2 = y_1 + (radius1 - radius2) / 2;

  // Center Top Text
  if (ptrData[2]->dataName != "None")
  {

    gaugeText(ptrData[2]->scaledValue, ptrData[2]->minimum, ptrData[2]->maximum, (120), (140), 5,
              ptrData[2]->units, ptrData[2]->dataName, selectedColor[0], selectedColor[1], TRUE, TRUE, 15, ptrData[2]->alert, selectedColor[2]);
    if (ptrData[2]->alert == true)
    {
      showAlert = true;
    }
  }

  if (showAlert == true)
  {

    if (millis() > (lastAlert_ms + alertTime_ms))
    {
      alertActive = !alertActive;
      lastAlert_ms = millis();
    }
    if (alertActive == true)
    {
      drawAlert(120, 210, 50, 1);
    }
    else if (alertActive == false)
    {
      drawAlert(120, 210, 50, 0);
    }
  }

  else
  {
    drawAlert(120, 210, 50, 0);
  }
}

/*
Updates the display based on the selected configurations
This creates an analog style needle on top with up to 5 sets of digits
*/

void updateDisplay_Analog()
{
  int radius1 = 116;
  int radius2 = 80;
  int x_1 = 15;
  int y_1 = 17;

  int x_2 = x_1 + (radius1 - radius2) / 2;
  int y_2 = y_1 + (radius1 - radius2) / 2;

  if (analogMeterSetup == false)
  {
    tft.fillScreen(TFT_BLACK);
    setupAnalogMeter(0, 10, ptrData[9]->dataName, ptrData[9]->units, ptrData[9]->minimum, ptrData[9]->maximum);
    tft.setTextColor(selectedColor[1], TFT_BLACK);
    tft.drawString(ptrData[9]->dataName, 20, 95, 2);
    tft.drawString(ptrData[9]->units, 200, 95, 2);
    analogMeterSetup = true;
  }

  // Meter Needle

  AnMeter.updateNeedle(ptrData[9]->scaledValue, 0, selectedColor[3], TFT_BLACK, selectedColor[0]);
  if (ptrData[9]->alert == true && ptrData[9]->dataName != "None")
  {
    showAlert = true;
  }

  // Left Top
  if (ptrData[7]->dataName != "None")
  {
    gaugeText(ptrData[7]->scaledValue, ptrData[7]->minimum, ptrData[7]->maximum, (40), (140), 1,
              ptrData[7]->units, ptrData[7]->dataName, selectedColor[0], selectedColor[1], TRUE, TRUE, 15, ptrData[7]->alert, selectedColor[2]);
    if (ptrData[7]->alert == true)
    {
      showAlert = true;
    }
  }

  // Right Top
  if (ptrData[8]->dataName != "None")
  {
    gaugeText(ptrData[8]->scaledValue, ptrData[8]->minimum, ptrData[8]->maximum, (200), (140), 1,
              ptrData[8]->units, ptrData[8]->dataName, selectedColor[0], selectedColor[1], TRUE, TRUE, 15, ptrData[8]->alert, selectedColor[2]);
    if (ptrData[8]->alert == true)
    {
      showAlert = true;
    }
  }

  // Center
  if (ptrData[4]->dataName != "None")
  {

    gaugeText(ptrData[4]->scaledValue, ptrData[4]->minimum, ptrData[4]->maximum, (120), (160), 1,
              ptrData[4]->units, ptrData[4]->dataName, selectedColor[0], selectedColor[1], TRUE, TRUE, 15, ptrData[4]->alert, selectedColor[2]);

    if (ptrData[4]->alert == true)
    {
      showAlert = true;
    }
  }

  // Bottom Left
  if (ptrData[3]->dataName != "None")
  {
    gaugeText(ptrData[3]->scaledValue, ptrData[3]->minimum, ptrData[3]->maximum, (60), (190), 1,
              ptrData[3]->units, ptrData[3]->dataName, selectedColor[0], selectedColor[1], TRUE, TRUE, 15, ptrData[3]->alert, selectedColor[2]);

    if (ptrData[3]->alert == true)
    {
      showAlert = true;
    }
  }

  // Bottom Right
  if (ptrData[5]->dataName != "None")
  {
    gaugeText(ptrData[5]->scaledValue, ptrData[5]->minimum, ptrData[5]->maximum, (180), (190), 1,
              ptrData[5]->units, ptrData[5]->dataName, selectedColor[0], selectedColor[1], TRUE, TRUE, 15, ptrData[5]->alert, selectedColor[2]);
    if (ptrData[5]->alert == true)
    {
      showAlert = true;
    }
  }

  if (showAlert == true)
  {

    if (millis() > (lastAlert_ms + alertTime_ms))
    {
      alertActive = !alertActive;
      lastAlert_ms = millis();
    }
    if (alertActive == true)
    {
      drawAlert(120, 210, 50, 1);
    }
    else if (alertActive == false)
    {
      drawAlert(120, 210, 50, 0);
    }
  }

  else
  {
    drawAlert(120, 210, 50, 0);
  }
}

/*
Updates the display based on the selected configurations
This creates an analog style needle on top with larger center digits
*/


void updateDisplay_Analog_LargeText()
{
  int radius1 = 116;
  int radius2 = 80;
  int x_1 = 15;
  int y_1 = 17;

  int x_2 = x_1 + (radius1 - radius2) / 2;
  int y_2 = y_1 + (radius1 - radius2) / 2;

  if (analogMeterSetup == false)
  {
    tft.fillScreen(TFT_BLACK);
    setupAnalogMeter(0, 10, ptrData[9]->dataName, ptrData[9]->units, ptrData[9]->minimum, ptrData[9]->maximum);
    tft.setTextColor(selectedColor[1], TFT_BLACK);
    tft.drawString(ptrData[9]->dataName, 20, 95, 2);
    tft.drawString(ptrData[9]->units, 200, 95, 2);
    analogMeterSetup = true;
  }

  // Meter Needle
  AnMeter.updateNeedle(ptrData[9]->scaledValue, 0, selectedColor[3], TFT_BLACK, selectedColor[0]);
  if (ptrData[9]->alert == true && ptrData[9]->dataName != "None")
  {
    showAlert = true;
  }

  // Center
  if (ptrData[4]->dataName != "None")
  {

    gaugeText(ptrData[4]->scaledValue, ptrData[4]->minimum, ptrData[4]->maximum, (130), (150), 3,
              ptrData[4]->units, ptrData[4]->dataName, selectedColor[0], selectedColor[1], TRUE, TRUE, 15, ptrData[4]->alert, selectedColor[2]);

    if (ptrData[4]->alert == true)
    {
      showAlert = true;
    }
  }

  if (showAlert == true)
  {

    if (millis() > (lastAlert_ms + alertTime_ms))
    {
      alertActive = !alertActive;
      lastAlert_ms = millis();
    }
    if (alertActive == true)
    {
      drawAlert(120, 210, 50, 1);
    }
    else if (alertActive == false)
    {
      drawAlert(120, 210, 50, 0);
    }
  }

  else
  {
    drawAlert(120, 210, 50, 0);
  }
}

//==============================================
//  Gauge Task
//==============================================

/*
Task to update the UI
Inludes display and LEDs
Update rate defined by displayRefresh_ms
*/

void updateDisplayTask(void *pvParameters)
{

#ifdef DEBUG_SERIAL
  Serial.print("Display Task on core: ");
  Serial.println(xPortGetCoreID());
#endif

  tft.fillScreen(TFT_BLACK);
  int lastDisplayUpdate_ms = 0;

  for (;;)
  {

    // When updating config reset the display to remove old text
    if (resetDisplay == true || updatedArc == true)
    {
      tft.fillScreen(TFT_BLACK);
      resetDisplay = false;
      updatedArc = false;
      analogMeterSetup = false;
    }

    showAlert = false;

    if ((millis() - lastDisplayUpdate_ms) > displayRefresh_ms)
    {
      getBrightness();
      setDisplayBrightness(dispBrightness);
      lastDisplayUpdate_ms = millis();

      switch (gaugeDisplayType)
      {

      case 0:
        updateDisplay();
        break;

      case 1:
        updateDisplay_Analog();
        break;

      case 2:
        updateDisplay_LargeText();
        break;

      case 3:
        updateDisplay_Analog_LargeText();
        break;

      case 4:
        updateDisplay_Large();
        break;

      default:
        updateDisplay();
        break;
      }

      if (ledEnabled == true)
      {

        int ledsON = 6 * (ptrData[6]->scaledValue - ptrData[6]->minimum) / (ptrData[6]->maximum - ptrData[6]->minimum);

        int ledCLR = ledsON - 1;

        if (ledCLR < 0)
        {
          ledCLR = 0;
        }

        if (ledCLR > 5)
        {
          ledCLR = 5;
        }

        switch (LEDstyle)
        {

        case 0:
          ledSeries(ledsON, LEDred[LEDcolor][ledCLR], LEDgreen[LEDcolor][ledCLR], LEDblue[LEDcolor][ledCLR], ledBrightness);
          break;

        case 1:
          ledSeriesMulticolor(ledsON, LEDred[LEDcolor][ledCLR], LEDgreen[LEDcolor][ledCLR], LEDblue[LEDcolor][ledCLR], ledBrightness);
          break;

        case 2:
          ledSingle(ledsON, LEDred[LEDcolor][ledCLR], LEDgreen[LEDcolor][ledCLR], LEDblue[LEDcolor][ledCLR], ledBrightness);
          break;

        default:
          ledSeries(ledsON, LEDred[LEDcolor][ledCLR], LEDgreen[LEDcolor][ledCLR], LEDblue[LEDcolor][ledCLR], ledBrightness);
          break;
        }
      }
    }
  }
}

/*
Setup the display task
Runs on core 1
*/
void setupDisplayTask()
{

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

//==============================================
//  Input Task
//==============================================

/*
Task to respond to user inputs
Includes wifi, CLI, and incrementing test data
*/

void inputTask(void *pvParameters){
for (;;)
  {
if (wifiEnabled == true)
  {
    ota();
  }

#ifdef CLI
  CLItask();
#endif

  checkNewConfig();
  incrementTestData();
  }
}


/*
Setup the input task
Runs on core 1
*/
void setupInputTask()
{

#ifdef DEBUG_SERIAL
  Serial.println("Setting up input task");
#endif

  xTaskCreatePinnedToCore(
      inputTask, /* Function to implement the task */
      "INPUT_CHECK",  /* Name of the task */
      4096,              /* Stack size in words */
      NULL,              /* Task input parameter */
      1,                 /* Priority of the task */
      NULL,              /* Task handle. */
      1);                /* Core where the task should run */
  st++;
}


//=========================================
// Configuration Restore
//=========================================

void startupConfig()
{

  // Check the NVS version
  // Reset if old
  nvs_flash_init();
  checkNvsVer();

  // Restore user configurations
  restoreSensorSetting();

  for (int p = 0; (p < numDataPtr); p++)
  {
    ptrData[p] = selectSensor(gaugeSensor[p]);
  }

  restoreSensorMinMax();
  restoreSensorAlerts();
  restoreSensorPrecsision();

  restoreWifi();
  restoreBootConfig();

  restoreLedConfig();
  restoreLedColor();

  restoreArcConfig();
  restoreGaugeType();

  restoreTextConfig();
  restoreBrightnessSettings();
}

void checkWifiConfig()
{

  // Check that Wifi credentials have something, if not default them so gauge can be accessed
  // Password must be 8 characters or more, password can be 0 for no password
  if (strlen(password) != 0 && strlen(password) < 8)
  {

    strncpy(password, default_password, 16);
    saveWifi();
    Serial.println("Short password, resetting to default!");

    Serial.print("PW : ");
    Serial.println(password);
  }

  if (strlen(ssid) == 0)
  {
    strncpy(ssid, default_ssid, 16);
    saveWifi();
    Serial.println("No SSID, resetting to default!");
    Serial.print("SSID : ");
    Serial.println(ssid);
  }

  if (strlen(host) == 0)
  {
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

void setup()
{

  analogReadResolution(12);

  Serial.begin(115200);

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

  if (startWifi == true)
  {

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

  if (startCan == true)
  {
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

void loop()
{
}

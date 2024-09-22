/*

  'nvs.h'

  Handles configuration checks and restoring previously saved configurations

*/
#pragma once
#include "config.h"
#include "DataFunctions.h"
#include "wifi.h"
#include "display.h"
#include "pinMap.h"

#include "SensorData.h"
#include "led.h"
#include "display.h"

#include <Preferences.h>
#include <nvs_flash.h>

Preferences preferences;


// Boot logos
#define KAN 0
#define BMM 1
#define FOME 2
#define MAZDA 3
#define REV 102

// Meter color schemes
#define RED2RED 0
#define GREEN2GREEN 1
#define BLUE2BLUE 2
#define BLUE2RED 3
#define GREEN2RED 4
#define RED2GREEN 5

// Arc Color schemes
#define ARC_RED 0
#define ARC_GREEN 1
#define ARC_BLUE 2
#define ARC_BLUE2RED 3
#define ARC_GREEN2RED 4
#define ARC_RED2GREEN 5
#define ARC_WHITE 6
#define ARC_BLACK 7
#define ARC_CUSTOM1 8
#define ARC_CUSTOM2 9

// LED Style
#define LED_STYLE_SINGLECOLOR 0
#define LED_STYLE_MULTICOLOR 1
#define LED_STYLE_SINGLE 2

// LED Colors
#define LED_COLOR_NONE 0
#define LED_COLOR_BLUE2GREEN2RED 1
#define LED_COLOR_GREEN2RED 2
#define LED_COLOR_CUSTOM 3

// Data Locations
#define DATALOC_INSIDEARC 0
#define DATALOC_OUTSIDEARC 1
#define DATALOC_CENTER 2
#define DATALOC_BOTTOMLEFT 3
#define DATALOC_BOTTOMCENTER 4
#define DATALOC_BOTTOMRIGHT 5
#define DATALOC_LED 6
#define DATALOC_TOPLEFT 7
#define DATALOC_TOPRIGHT 8
#define DATALOC_METER 9
#define DATALOC_E 10


sensorData *selectSensor(int dataSelection) {

  switch (dataSelection) {
    case AFR:
      return &afr;
      break;

    case RPM:
      return &rpm;
      break;

    case SPEED_KPH:
      return &vss;
      break;

    case SPEED_MPH:
      return &vss_mph;
      break;

    case MANIFOLD_PRESS_KPA:
      return &manifoldPressure;
      break;

    case MANIFOLD_PRESS_PSI:
      return &manifoldPressure_psi;
      break;

    case COOLANT_TEMP_C:
      return &coolantTemperature;
      break;

    case COOLANT_TEMP_F:
      return &coolantTemperature_f;
      break;

    case INTAKE_TEMP_C:
      return &intakeTemperature;
      break;

    case INTAKE_TEMP_F:
      return &intakeTemperature_f;
      break;

    case ACCELERATOR:
      return &accelerator;
      break;

    case IGNITION_TIMING:
      return &ignitionTiming;
      break;

    case INJECTOR_DUTY:
      return &injectorDuty;
      break;

    case INJECTOR_PULSE:
      return &injectorPulse;
      break;

    case THROTTLE_POSITION_1:
      return &throttle1;
      break;

    case THROTTLE_POSITION_2:
      return &throttle2;
      break;

    case VALVE_TIMING:
      return &vvtPosition;
      break;

    case AIR_MASS:
      return &airMass;
      break;

    case ESTIMATED_AIRFLOW:
      return &estimatedAirflow;
      break;

    case FUEL:
      return &fuel;
      break;

    case MCU_C:
      return &mcuTemp;
      break;

    case AUX_TEMP_1_C:
      return &auxTemp1;
      break;

    case AUX_TEMP_1_F:
      return &auxTemp1_f;
      break;

    case AUX_TEMP_2_C:
      return &auxTemp2;
      break;

    case AUX_TEMP_2_F:
      return &auxTemp2_f;
      break;

    case BATTERY_VOLTAGE:
      return &batteryVoltage;
      break;

    case ETHANOL:
      return &ethanol;
      break;

    case LAMBDA_1:
      return &lambda1;
      break;

    case LAMBDA_2:
      return &lambda2;
      break;

    case FUEL_PRESS_LO:
      return &fuelPressureLow;
      break;

    case FUEL_PRESS_HI:
      return &fuelPressureHigh;
      break;

    case FUEL_CONSUMED:
      return &fuelConsumed;
      break;

    case FUEL_RATE:
      return &fuelConsumption;
      break;

    case FUEL_TRIM:
      return &fuelTrim;
      break;

    case INTAKE_VALVE_1:
      return &vvtIntake1;
      break;

    case INTAKE_VALVE_2:
      return &vvtIntake2;
      break;

    case EXHAUST_VALVE_1:
      return &vvtExhaust1;
      break;

    case EXHAUST_VALVE_2:
      return &vvtExhaust2;
      break;

    case OIL_PRESS_KPA:
      return &oilPressure;
      break;

    case OIL_PRESS_PSI:
      return &oilPressure_psi;
      break;

    case GEAR:
      return &gear;
      break;

    case NO_DATA:
      return &noData;
      break;

    case TEST_DATA:
      return &testData;
      break;

    case BOOST_KPA:
      return &boost_kpa;
      break;

    case BOOST_PSI:
      return &boost_psi;
      break;

    case WASTEGATE_DUTY:
      return &wastegate;
      break;

    case FUEL_PRESS_DELTA:
      return &fuelPressDelta_kpa;
      break;

    case OIL_TEMP:
      return &oilTemperature;
      break;

    case OIL_TEMP_F:
      return &oilTemperature_f;
      break;

    case FUEL_TEMP:
      return &fuelTemperature;
      break;

    case FUEL_TEMP_F:
      return &fuelTemperature_f;
      break;


    default:
      return &afr;
  }
}


// Pointer for current data
int numDataPtr = 10;
sensorData *ptrData[10];
sensorData *newSensorConfig;


char ssid[16] = "KaN Gauge";
char password[16] = "update1234";
char host[16] = "kan";

char default_ssid[16] = "KaN Gauge";
char default_password[16] = "update1234";
char default_host[16] = "kan";

char newSSID[16] = "KaN Gauge";
char newPW[16] = "update1234";
char newHOST[16] = "kan";

int gaugeSensor[] = { LAMBDA_1, OIL_PRESS_PSI, LAMBDA_1, COOLANT_TEMP_F, LAMBDA_1, OIL_PRESS_PSI, LAMBDA_1, LAMBDA_1, LAMBDA_1, LAMBDA_1, NO_DATA };
int brightness[] = { 80, 10, 80, 10 };
int logoTime_ms = 600;

int selectedSensor;
int selectedLimit;
int selectedType;
int selectedGauge;
int selectedLedMode;
int selectedDisplayRate;
int brightnessInput;
int brightnessInput2;
int selectedBrightness = 3;

float newMin, newMax, newHigh, newLow;

int gaugeDisplayType = 0;

#define NONE 0
#define EXCLAMATION 1
#define FF 2
#define LED 3

int config_alertType = NONE;


String arcColors[] = { "Red", "Green", "Blue", "Blue to Red", "Green to Red", "Red to Green", "White", "Black", "Custom 1", "Custom 2" };
int customArcColor[] = { 0, 0 };

// Default Arc Color Scheme
int arcColor1 = 4;  // Green to Red
int arcColor2 = 3;  // Blue to Red
int arcSeg1 = 3;
int arcSeg2 = 3;
int arcInc1 = 6;
int arcInc2 = 3;

int selectedColor[] = { 65535, 63488, 63488, 63488, 0 };
String colorName[] = { "Value", "Units", "Alert", "Needle", "Background" };

int bootLogo1 = 1;  // BMM
int bootLogo2 = 2;  // FOME
int bootLogo3 = 0;  // KaN with version

int LEDcolor = 1;  // LED config blue to green to red

int LEDstyle = 4;
String ledStyleName[] = { "Series Single Color", "Series Multi-Color", "Single LED" };
String ledColorName[] = { "None", "Blue -> Green -> Red", "Green -> Red", "Custom", "Alert 1", "Alert 2"};

int LEDred[6][6] = { { 0, 0, 0, 0, 0, 0 }, { 0, 100, 150, 255, 255, 255 }, { 100, 100, 100, 100, 100, 255 }, { 255, 255, 255, 255, 255, 255 }, { 255, 255, 255, 255, 255, 255 }, { 255, 255, 255, 255, 255, 255 } };
int LEDgreen[6][6] = { { 0, 0, 0, 0, 0, 0 }, { 100, 200, 255, 150, 50, 0 }, { 200, 200, 200, 200, 200, 0 }, { 255, 255, 255, 255, 255, 255 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 } };
int LEDblue[6][6] = { { 0, 0, 0, 0, 0, 0 }, { 150, 40, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 255, 255, 255, 255, 255, 255 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 } };

float inputNewValue;

bool nvsReset = false;
bool readyToUpdateGaugeConfig = false;
bool readyToUpdateLimits = false;
bool readyToUpdateDisplayRate = false;
bool readyToUpdateLedMode = false;
bool updateWifiConfig = false;
bool resetDisplay = false;
bool updateArcConfig = false;
bool updatedArc = false;
bool fullscreenAlert = true;
int quickstart = 0;
bool setToDefaults = false;
bool updateGaugeType = false;
bool updateUserConfig = false;

bool startWifi = true;
bool startCan = true;

int displayRefresh_ms = 100;


String gaugeStyleNames[] = { "2 Arc", "Meter", "1 Arc, large digits", "Meter, large digits", "Large Digits" };
String dataLocation[] = { "Inside Arc", "Outer Arc", "Center", "Bottom Left", "Center Bottom", "Bottom Right", "LEDs", "Top Left", "Top Right", "Meter", "" };


// USER CONFIGURATION
const int config_max = 3;
int config_selectedConfig[1];
int config_gaugeStyle[3] = { 4, 3, 2 };
int config_sensorData[3][10] = { { LAMBDA_1, OIL_PRESS_PSI, LAMBDA_1, COOLANT_TEMP_F, LAMBDA_1, OIL_PRESS_PSI, LAMBDA_1, LAMBDA_1, LAMBDA_1, LAMBDA_1}, { OIL_PRESS_PSI, OIL_PRESS_PSI, OIL_PRESS_PSI, LAMBDA_1, OIL_PRESS_PSI, MANIFOLD_PRESS_PSI, OIL_PRESS_PSI, OIL_PRESS_PSI, OIL_PRESS_PSI, OIL_PRESS_PSI}, { MANIFOLD_PRESS_PSI, MANIFOLD_PRESS_PSI, MANIFOLD_PRESS_PSI, COOLANT_TEMP_F, MANIFOLD_PRESS_PSI, INTAKE_TEMP_F, MANIFOLD_PRESS_PSI, MANIFOLD_PRESS_PSI, MANIFOLD_PRESS_PSI, MANIFOLD_PRESS_PSI}};

int config_ledStyle[3] = { 0, 0, 0 };
int config_ledColors[3] = { 1, 0, 0 };
int config_uiColors[3][6] = { {65535, 63488, 63488, 63488, 0 }, { 65535, 63488, 63488, 63488, 0 }, { 65535, 63488, 63488, 63488, 0 } };

//config_gaugeStyle[config_selectedConfig[0]] =

void setupUserConfig() {

  if (config_selectedConfig[0] >= config_max) {

    config_selectedConfig[0] = 0;
  }

  //Use selected config to setup gauge
  int cfg = config_selectedConfig[0];

  // Gauge Type
  gaugeDisplayType = config_gaugeStyle[cfg];

  // Gauge Data
  for (int iconf = 0; iconf < 10; iconf++) {
    gaugeSensor[iconf] = config_sensorData[cfg][iconf];
  }

  for (int p = 0; (p < numDataPtr); p++) {
    ptrData[p] = selectSensor(gaugeSensor[p]);
  }

  // Gauge LED Style
  LEDstyle = config_ledStyle[cfg];

  // Gauge LED Colors
  LEDcolor = config_ledColors[cfg];

  // Gauge UI Colors

  for (int iconf = 0; iconf < 5; iconf++) {
    selectedColor[iconf] = config_uiColors[cfg][iconf];
  }
}

void saveUserConfig() {
  preferences.begin("userConfig");
  preferences.putBytes("cf_sel", (byte *)(&config_selectedConfig), sizeof(config_selectedConfig));
  preferences.putBytes("cf_gauge", (byte *)(&config_gaugeStyle), sizeof(config_gaugeStyle));
  preferences.putBytes("cf_data", (byte *)(&config_sensorData), sizeof(config_sensorData));
  preferences.putBytes("cf_ledStyle", (byte *)(&config_ledStyle), sizeof(config_ledStyle));
  preferences.putBytes("cf_ledColors", (byte *)(&config_ledColors), sizeof(config_ledColors));
  preferences.putBytes("cf_uiColors", (byte *)(&config_uiColors), sizeof(config_uiColors));
  preferences.putBytes("cf_alertType", (byte *)(&config_alertType), sizeof(config_alertType));
  preferences.end();
}

void restoreUserConfig() {
  preferences.begin("userConfig");
  preferences.getBytes("cf_sel", (&config_selectedConfig), sizeof(config_selectedConfig));
  preferences.getBytes("cf_gauge", (&config_gaugeStyle), sizeof(config_gaugeStyle));
  preferences.getBytes("cf_data", (&config_sensorData), sizeof(config_sensorData));
  preferences.getBytes("cf_ledStyle", (&config_ledStyle), sizeof(config_ledStyle));
  preferences.getBytes("cf_ledColors", (&config_ledColors), sizeof(config_ledColors));
  preferences.getBytes("cf_uiColors", (&config_uiColors), sizeof(config_uiColors));
  preferences.getBytes("cf_alertType", (&config_alertType), sizeof(config_alertType));
  preferences.end();
}


bool nextConfigCheck(bool next) {

  if (next == true) {
    config_selectedConfig[0]++;
    if (config_selectedConfig[0] >= config_max) {
      config_selectedConfig[0] = 0;
    }

    setupUserConfig();
    saveUserConfig();
    resetDisplay = true;
  }

  return false;
}

//==============================================
//  Save and Restore Functions
//==============================================



void saveDisplayRefresh() {
  preferences.begin("dispRefresh", false);
  preferences.putUInt("dipRef", displayRefresh_ms);
  preferences.end();
}

void restoreDisplayRefresh() {
  preferences.begin("dispRefresh", false);
  displayRefresh_ms = preferences.getUInt("dipRef", displayRefresh_ms);
  preferences.end();
}


void saveBrightnessSettings() {
  // Open R/W
  preferences.begin("bright", false);
  preferences.putUInt("dispL", brightness[0]);
  preferences.putUInt("dispH", brightness[1]);
  preferences.putUInt("ledL", brightness[2]);
  preferences.putUInt("ledH", brightness[3]);
  preferences.end();
}

void restoreBrightnessSettings() {
  preferences.begin("bright", false);
  brightness[0] = preferences.getUInt("dispL", brightness[0]);
  brightness[1] = preferences.getUInt("dispH", brightness[1]);
  brightness[2] = preferences.getUInt("ledL", brightness[2]);
  brightness[3] = preferences.getUInt("ledH", brightness[3]);
  preferences.end();
}

void restoreSensorMinMax() {
  preferences.begin("MinMax", false);

  testData.minimum = preferences.getInt("testMIN", testData.minimum);
  testData.maximum = preferences.getInt("testMAX", testData.maximum);

  rpm.minimum = preferences.getInt("rpmMIN", rpm.minimum);
  rpm.maximum = preferences.getInt("rpmMAX", rpm.maximum);

  vss.minimum = preferences.getInt("vssMIN", vss.minimum);
  vss.maximum = preferences.getInt("vssMAX", vss.maximum);

  vss_mph.minimum = preferences.getInt("vssMPHMIN", vss_mph.minimum);
  vss_mph.maximum = preferences.getInt("vssMPHMAX", vss_mph.maximum);

  accelerator.minimum = preferences.getInt("acceleratorMIN", accelerator.minimum);
  accelerator.maximum = preferences.getInt("acceleratorMAX", accelerator.maximum);

  throttle1.minimum = preferences.getInt("throttle1MIN", throttle1.minimum);
  throttle1.maximum = preferences.getInt("throttle1MAX", throttle1.maximum);

  throttle2.minimum = preferences.getInt("throttle2MIN", throttle2.minimum);
  throttle2.maximum = preferences.getInt("throttle2MAX", throttle2.maximum);

  injectorDuty.minimum = preferences.getInt("injDutyMIN", injectorDuty.minimum);
  injectorDuty.maximum = preferences.getInt("injDutyMAX", injectorDuty.maximum);

  injectorPulse.minimum = preferences.getInt("injPulseMIN", injectorPulse.minimum);
  injectorPulse.maximum = preferences.getInt("injPulseMAX", injectorPulse.maximum);

  fuelPressureHigh.minimum = preferences.getInt("fuelPresHighMIN", fuelPressureHigh.minimum);
  fuelPressureHigh.maximum = preferences.getInt("fuelPresHighMAX", fuelPressureHigh.maximum);

  fuelPressureLow.minimum = preferences.getInt("fuelPresLowMIN", fuelPressureLow.minimum);
  fuelPressureLow.maximum = preferences.getInt("fuelPresLowMAX", fuelPressureLow.maximum);

  ethanol.minimum = preferences.getInt("ethanolMIN", ethanol.minimum);
  ethanol.maximum = preferences.getInt("ethanolMAX", ethanol.maximum);

  fuelTrim.minimum = preferences.getInt("fuelTrimMIN", fuelTrim.minimum);
  fuelTrim.maximum = preferences.getInt("fuelTrimMAX", fuelTrim.maximum);

  fuel.minimum = preferences.getInt("fuelMIN", fuel.minimum);
  fuel.maximum = preferences.getInt("fuelMAX", fuel.maximum);

  fuelConsumed.minimum = preferences.getInt("fuelUsedMIN", fuelConsumed.minimum);
  fuelConsumed.maximum = preferences.getInt("fuelUsedMAX", fuelConsumed.maximum);

  fuelConsumption.minimum = preferences.getInt("fuelFlowMIN", fuelConsumption.minimum);
  fuelConsumption.maximum = preferences.getInt("fuelFlowMAX", fuelConsumption.maximum);

  afr.minimum = preferences.getInt("afrMIN", afr.minimum);
  afr.maximum = preferences.getInt("afrMAX", afr.maximum);

  lambda1.minimum = preferences.getInt("lambda1MIN", lambda1.minimum);
  lambda1.maximum = preferences.getInt("lambda1MAX", lambda1.maximum);

  lambda2.minimum = preferences.getInt("lambda2MIN", lambda1.minimum);
  lambda2.maximum = preferences.getInt("lambda2MAX", lambda1.maximum);

  afr.minimum = afr.minimum / 100;
  afr.maximum = afr.maximum / 100;

  lambda1.minimum = lambda1.minimum / 100;
  lambda1.maximum = lambda1.maximum / 100;

  lambda2.minimum = lambda2.minimum / 100;
  lambda2.maximum = lambda2.maximum / 100;

  coolantTemperature.minimum = preferences.getInt("cltCMIN", coolantTemperature.minimum);
  coolantTemperature.maximum = preferences.getInt("cltCMAX", coolantTemperature.maximum);

  intakeTemperature.minimum = preferences.getInt("iatCMIN", intakeTemperature.minimum);
  intakeTemperature.maximum = preferences.getInt("iatCMAX", intakeTemperature.maximum);

  auxTemp1.minimum = preferences.getInt("aux1CMIN", auxTemp1.minimum);
  auxTemp1.maximum = preferences.getInt("aux1CMAX", auxTemp1.maximum);

  auxTemp2.minimum = preferences.getInt("aux2CMIN", auxTemp2.minimum);
  auxTemp2.maximum = preferences.getInt("aux2CMAX", auxTemp2.maximum);

  mcuTemp.minimum = preferences.getInt("mcuCMIN", mcuTemp.minimum);
  mcuTemp.maximum = preferences.getInt("mcuCMAX", mcuTemp.maximum);

  coolantTemperature_f.minimum = preferences.getInt("cltFMIN", coolantTemperature_f.minimum);
  coolantTemperature_f.maximum = preferences.getInt("cltFMAX", coolantTemperature_f.maximum);

  intakeTemperature_f.minimum = preferences.getInt("iatFMIN", intakeTemperature_f.minimum);
  intakeTemperature_f.maximum = preferences.getInt("iatFMAX", intakeTemperature_f.maximum);

  ignitionTiming.minimum = preferences.getInt("ignMIN", ignitionTiming.minimum);
  ignitionTiming.maximum = preferences.getInt("ignMAX", ignitionTiming.maximum);

  auxTemp1_f.minimum = preferences.getInt("aux1FMIN", auxTemp1_f.minimum);
  auxTemp1_f.maximum = preferences.getInt("aux1FMAX", auxTemp1_f.maximum);

  auxTemp2_f.minimum = preferences.getInt("aux2FMIN", auxTemp2_f.minimum);
  auxTemp2_f.maximum = preferences.getInt("aux2FMAX", auxTemp2_f.maximum);

  oilTemperature_f.minimum = preferences.getInt("oilTFMIN", oilTemperature_f.minimum);
  oilTemperature_f.maximum = preferences.getInt("oilTFMAX", oilTemperature_f.maximum);

  oilTemperature.minimum = preferences.getInt("oilTMIN", oilTemperature.minimum);
  oilTemperature.maximum = preferences.getInt("oilTMAX", oilTemperature.maximum);

  fuelTemperature_f.minimum = preferences.getInt("fuelTFMIN", fuelTemperature_f.minimum);
  fuelTemperature_f.maximum = preferences.getInt("fuelTFMAX", fuelTemperature_f.maximum);

  fuelTemperature.minimum = preferences.getInt("fuelTMIN", fuelTemperature.minimum);
  fuelTemperature.maximum = preferences.getInt("fuelTMAX", fuelTemperature.maximum);

  manifoldPressure.minimum = preferences.getInt("mapKPAMIN", manifoldPressure.minimum);
  manifoldPressure.maximum = preferences.getInt("mapKPAMAX", manifoldPressure.maximum);

  boost_kpa.minimum = preferences.getInt("boostKPAMIN", boost_kpa.minimum);
  boost_kpa.maximum = preferences.getInt("boostKPAMAX", boost_kpa.maximum);

  boost_psi.minimum = preferences.getInt("boostPSIMIN", boost_psi.minimum);
  boost_psi.maximum = preferences.getInt("boostPSIMAX", boost_psi.maximum);

  oilPressure.minimum = preferences.getInt("oilKPAMIN", oilPressure.minimum);
  oilPressure.maximum = preferences.getInt("oilKPAMAX", oilPressure.maximum);

  manifoldPressure_psi.minimum = preferences.getInt("mapPSIMIN", manifoldPressure_psi.minimum);
  manifoldPressure_psi.maximum = preferences.getInt("mapPSIMAX", manifoldPressure_psi.maximum);

  oilPressure_psi.minimum = preferences.getInt("oilKPAMIN", oilPressure_psi.minimum);
  oilPressure_psi.maximum = preferences.getInt("oilKPAMAX", oilPressure_psi.maximum);

  vvtPosition.minimum = preferences.getInt("vvtMIN", vvtPosition.minimum);
  vvtPosition.maximum = preferences.getInt("vvtMAX", vvtPosition.maximum);

  vvtExhaust1.minimum = preferences.getInt("vvtEx1MIN", vvtExhaust1.minimum);
  vvtExhaust1.maximum = preferences.getInt("vvtEx1MAX", vvtExhaust1.maximum);

  vvtExhaust2.minimum = preferences.getInt("vvtEx2MIN", vvtExhaust2.minimum);
  vvtExhaust2.maximum = preferences.getInt("vvtEx2MAX", vvtExhaust2.maximum);

  vvtIntake1.minimum = preferences.getInt("vvtIn1MIN", vvtIntake1.minimum);
  vvtIntake1.maximum = preferences.getInt("vvtIn1MAX", vvtIntake1.maximum);

  vvtIntake2.minimum = preferences.getInt("vvtIn2MIN", vvtIntake2.minimum);
  vvtIntake2.maximum = preferences.getInt("vvtIn2MAX", vvtIntake2.maximum);

  airMass.minimum = preferences.getInt("airMassMIN", airMass.minimum);
  airMass.maximum = preferences.getInt("airMassMAX", airMass.maximum);

  estimatedAirflow.minimum = preferences.getInt("estAirMIN", estimatedAirflow.minimum);
  estimatedAirflow.maximum = preferences.getInt("estAirMAX", estimatedAirflow.maximum);

  batteryVoltage.minimum = preferences.getInt("batVMIN", batteryVoltage.minimum);
  batteryVoltage.maximum = preferences.getInt("batVMAX", batteryVoltage.maximum);

  fuelPressDelta_kpa.minimum = preferences.getInt("fpDeltaMIN", fuelPressDelta_kpa.minimum);
  fuelPressDelta_kpa.maximum = preferences.getInt("fpDeltaMIN", fuelPressDelta_kpa.maximum);

  preferences.end();
}

void restoreSensorAlerts() {

  preferences.begin("alerts", false);

  testData.alertLow = preferences.getInt("testLOW", testData.alertLow);
  testData.alertHigh = preferences.getInt("testHI", testData.alertHigh);

  rpm.alertLow = preferences.getInt("rpmLOW", rpm.alertLow);
  rpm.alertHigh = preferences.getInt("rpmHI", rpm.alertHigh);

  vss.alertLow = preferences.getInt("vssLOW", vss.alertLow);
  vss.alertHigh = preferences.getInt("vssHI", vss.alertHigh);

  vss_mph.alertLow = preferences.getInt("vssMPHLOW", vss_mph.alertLow);
  vss_mph.alertHigh = preferences.getInt("vssMPHHI", vss_mph.alertHigh);

  accelerator.alertLow = preferences.getInt("acceleratorLOW", accelerator.alertLow);
  accelerator.alertHigh = preferences.getInt("acceleratorHI", accelerator.alertHigh);

  throttle1.alertLow = preferences.getInt("throttle1LOW", throttle1.alertLow);
  throttle1.alertHigh = preferences.getInt("throttle1HI", throttle1.alertHigh);

  throttle2.alertLow = preferences.getInt("throttle2LOW", throttle2.alertLow);
  throttle2.alertHigh = preferences.getInt("throttle2HI", throttle2.alertHigh);

  injectorDuty.alertLow = preferences.getInt("injDutyLOW", injectorDuty.alertLow);
  injectorDuty.alertHigh = preferences.getInt("injDutyHI", injectorDuty.alertHigh);

  injectorPulse.alertLow = preferences.getInt("injPulseLOW", injectorPulse.alertLow);
  injectorPulse.alertHigh = preferences.getInt("injPulseHI", injectorPulse.alertHigh);

  fuelPressureHigh.alertLow = preferences.getInt("fuelPresHighLOW", fuelPressureHigh.alertLow);
  fuelPressureHigh.alertHigh = preferences.getInt("fuelPresHighHI", fuelPressureHigh.alertHigh);

  fuelPressureLow.alertLow = preferences.getInt("fuelPresLowLOW", fuelPressureLow.alertLow);
  fuelPressureLow.alertHigh = preferences.getInt("fuelPresLowHI", fuelPressureLow.alertHigh);

  ethanol.alertLow = preferences.getInt("ethanolLOW", ethanol.alertLow);
  ethanol.alertHigh = preferences.getInt("ethanolHI", ethanol.alertHigh);

  fuelTrim.alertLow = preferences.getInt("fuelTrimLOW", fuelTrim.alertLow);
  fuelTrim.alertHigh = preferences.getInt("fuelTrimHI", fuelTrim.alertHigh);

  fuel.alertLow = preferences.getInt("fuelLOW", fuel.alertLow);
  fuel.alertHigh = preferences.getInt("fuelHI", fuel.alertHigh);

  fuelConsumed.alertLow = preferences.getInt("fuelUsedLOW", fuelConsumed.alertLow);
  fuelConsumed.alertHigh = preferences.getInt("fuelUsedHI", fuelConsumed.alertHigh);

  fuelConsumption.alertLow = preferences.getInt("fuelFlowLOW", fuelConsumption.alertLow);
  fuelConsumption.alertHigh = preferences.getInt("fuelFlowHI", fuelConsumption.alertHigh);

  afr.alertLow = preferences.getInt("afrLOW", afr.alertLow);
  afr.alertHigh = preferences.getInt("afrHI", afr.alertHigh);

  lambda1.alertLow = preferences.getInt("lambda1LOW", lambda1.alertLow);
  lambda1.alertHigh = preferences.getInt("lambda1HI", lambda1.alertHigh);

  lambda2.alertLow = preferences.getInt("lambda2LOW", lambda1.alertLow);
  lambda2.alertHigh = preferences.getInt("lambda2HI", lambda1.alertHigh);

  afr.alertLow = afr.alertLow / 100;
  afr.alertHigh = afr.alertHigh / 100;

  lambda1.alertLow = lambda1.alertLow / 100;
  lambda1.alertHigh = lambda1.alertHigh / 100;

  lambda2.alertLow = lambda2.alertLow / 100;
  lambda2.alertHigh = lambda2.alertHigh / 100;

  coolantTemperature.alertLow = preferences.getInt("cltCLOW", coolantTemperature.alertLow);
  coolantTemperature.alertHigh = preferences.getInt("cltCHI", coolantTemperature.alertHigh);

  intakeTemperature.alertLow = preferences.getInt("iatCLOW", intakeTemperature.alertLow);
  intakeTemperature.alertHigh = preferences.getInt("iatCHI", intakeTemperature.alertHigh);

  oilTemperature.alertLow = preferences.getInt("oilTLOW", oilTemperature.alertLow);
  oilTemperature.alertHigh = preferences.getInt("oilTHI", oilTemperature.alertHigh);

  oilTemperature_f.alertLow = preferences.getInt("oilTFLOW", oilTemperature_f.alertLow);
  oilTemperature_f.alertHigh = preferences.getInt("oilTFHI", oilTemperature_f.alertHigh);

  fuelTemperature.alertLow = preferences.getInt("fuelTLOW", fuelTemperature.alertLow);
  fuelTemperature.alertHigh = preferences.getInt("fuelTHI", fuelTemperature.alertHigh);

  fuelTemperature_f.alertLow = preferences.getInt("fuelTFLOW", fuelTemperature_f.alertLow);
  fuelTemperature_f.alertHigh = preferences.getInt("fuelTFHI", fuelTemperature_f.alertHigh);

  auxTemp1.alertLow = preferences.getInt("aux1CLOW", auxTemp1.alertLow);
  auxTemp1.alertHigh = preferences.getInt("aux1CHI", auxTemp1.alertHigh);

  auxTemp2.alertLow = preferences.getInt("aux2CLOW", auxTemp2.alertLow);
  auxTemp2.alertHigh = preferences.getInt("aux2CHI", auxTemp2.alertHigh);

  mcuTemp.alertLow = preferences.getInt("mcuCLOW", mcuTemp.alertLow);
  mcuTemp.alertHigh = preferences.getInt("mcuCHI", mcuTemp.alertHigh);

  coolantTemperature_f.alertLow = preferences.getInt("cltFLOW", coolantTemperature_f.alertLow);
  coolantTemperature_f.alertHigh = preferences.getInt("cltFHI", coolantTemperature_f.alertHigh);

  intakeTemperature_f.alertLow = preferences.getInt("iatFLOW", intakeTemperature_f.alertLow);
  intakeTemperature_f.alertHigh = preferences.getInt("iatFHI", intakeTemperature_f.alertHigh);

  ignitionTiming.alertLow = preferences.getInt("ignLOW", ignitionTiming.alertLow);
  ignitionTiming.alertHigh = preferences.getInt("ignHI", ignitionTiming.alertHigh);

  auxTemp1_f.alertLow = preferences.getInt("aux1FLOW", auxTemp1_f.alertLow);
  auxTemp1_f.alertHigh = preferences.getInt("aux1FHI", auxTemp1_f.alertHigh);

  auxTemp2_f.alertLow = preferences.getInt("aux2FLOW", auxTemp2_f.alertLow);
  auxTemp2_f.alertHigh = preferences.getInt("aux2FHI", auxTemp2_f.alertHigh);

  manifoldPressure.alertLow = preferences.getInt("mapKPALOW", manifoldPressure.alertLow);
  manifoldPressure.alertHigh = preferences.getInt("mapKPAHI", manifoldPressure.alertHigh);

  boost_kpa.alertLow = preferences.getInt("boostKPALOW", boost_kpa.alertLow);
  boost_kpa.alertHigh = preferences.getInt("boostKPAHI", boost_kpa.alertHigh);

  boost_psi.alertLow = preferences.getInt("boostPSILOW", boost_psi.alertLow);
  boost_psi.alertHigh = preferences.getInt("boostPSIHI", boost_psi.alertHigh);

  oilPressure.alertLow = preferences.getInt("oilKPALOW", oilPressure.alertLow);
  oilPressure.alertHigh = preferences.getInt("oilKPAHI", oilPressure.alertHigh);

  manifoldPressure_psi.alertLow = preferences.getInt("mapPSILOW", manifoldPressure_psi.alertLow);
  manifoldPressure_psi.alertHigh = preferences.getInt("mapPSIHI", manifoldPressure_psi.alertHigh);

  oilPressure_psi.alertLow = preferences.getInt("oilKPALOW", oilPressure_psi.alertLow);
  oilPressure_psi.alertHigh = preferences.getInt("oilKPAHI", oilPressure_psi.alertHigh);

  vvtPosition.alertLow = preferences.getInt("vvtLOW", vvtPosition.alertLow);
  vvtPosition.alertHigh = preferences.getInt("vvtHI", vvtPosition.alertHigh);

  vvtExhaust1.alertLow = preferences.getInt("vvtEx1LOW", vvtExhaust1.alertLow);
  vvtExhaust1.alertHigh = preferences.getInt("vvtEx1HI", vvtExhaust1.alertHigh);

  vvtExhaust2.alertLow = preferences.getInt("vvtEx2LOW", vvtExhaust2.alertLow);
  vvtExhaust2.alertHigh = preferences.getInt("vvtEx2HI", vvtExhaust2.alertHigh);

  vvtIntake1.alertLow = preferences.getInt("vvtIn1LOW", vvtIntake1.alertLow);
  vvtIntake1.alertHigh = preferences.getInt("vvtIn1HI", vvtIntake1.alertHigh);

  vvtIntake2.alertLow = preferences.getInt("vvtIn2LOW", vvtIntake2.alertLow);
  vvtIntake2.alertHigh = preferences.getInt("vvtIn2HI", vvtIntake2.alertHigh);

  airMass.alertLow = preferences.getInt("airMassLOW", airMass.alertLow);
  airMass.alertHigh = preferences.getInt("airMassHI", airMass.alertHigh);

  estimatedAirflow.alertLow = preferences.getInt("estAirLOW", estimatedAirflow.alertLow);
  estimatedAirflow.alertHigh = preferences.getInt("estAirHI", estimatedAirflow.alertHigh);

  batteryVoltage.alertLow = preferences.getInt("batVLOW", batteryVoltage.alertLow);
  batteryVoltage.alertHigh = preferences.getInt("batVHI", batteryVoltage.alertHigh);

  fuelPressDelta_kpa.alertLow = preferences.getInt("fpDeltaLOW", fuelPressDelta_kpa.alertLow);
  fuelPressDelta_kpa.alertHigh = preferences.getInt("fpDeltaHI", fuelPressDelta_kpa.alertHigh);

  preferences.end();
}


void saveSensorMinMax() {


  preferences.begin("MinMax", false);

  preferences.putInt("testMIN", testData.minimum);
  preferences.putInt("testMAX", testData.maximum);

  preferences.putInt("rpmMIN", rpm.minimum);
  preferences.putInt("rpmMAX", rpm.maximum);

  preferences.putInt("vssMIN", vss.minimum);
  preferences.putInt("vssMAX", vss.maximum);

  preferences.putInt("vssMPHMIN", vss_mph.minimum);
  preferences.putInt("vssMPHMAX", vss_mph.maximum);

  preferences.putInt("acceleratorMIN", accelerator.minimum);
  preferences.putInt("acceleratorMAX", accelerator.maximum);

  preferences.putInt("throttle1MIN", throttle1.minimum);
  preferences.putInt("throttle1MAX", throttle1.maximum);

  preferences.putInt("throttle2MIN", throttle2.minimum);
  preferences.putInt("throttle2MAX", throttle2.maximum);

  preferences.putInt("injDutyMIN", injectorDuty.minimum);
  preferences.putInt("injDutyMAX", injectorDuty.maximum);

  preferences.putInt("injPulseMIN", injectorPulse.minimum);
  preferences.putInt("injPulseMAX", injectorPulse.maximum);

  preferences.putInt("fuelPresHighMIN", fuelPressureHigh.minimum);
  preferences.putInt("fuelPresHighMAX", fuelPressureHigh.maximum);

  preferences.putInt("fuelPresLowMIN", fuelPressureLow.minimum);
  preferences.putInt("fuelPresLowMAX", fuelPressureLow.maximum);

  preferences.putInt("ethanolMIN", ethanol.minimum);
  preferences.putInt("ethanolMAX", ethanol.maximum);

  preferences.putInt("fuelTrimMIN", fuelTrim.minimum);
  preferences.putInt("fuelTrimMAX", fuelTrim.maximum);

  preferences.putInt("fuelMIN", fuel.minimum);
  preferences.putInt("fuelMAX", fuel.maximum);

  preferences.putInt("fuelUsedMIN", fuelConsumed.minimum);
  preferences.putInt("fuelUsedMAX", fuelConsumed.maximum);

  preferences.putInt("fuelFlowMIN", fuelConsumption.minimum);
  preferences.putInt("fuelFlowMAX", fuelConsumption.maximum);

  afr.minimum = afr.minimum * 100;
  afr.maximum = afr.maximum * 100;

  lambda1.minimum = lambda1.minimum * 100;
  lambda1.maximum = lambda1.maximum * 100;

  lambda2.minimum = lambda2.minimum * 100;
  lambda2.maximum = lambda2.maximum * 100;

  preferences.putInt("afrMIN", afr.minimum);
  preferences.putInt("afrMAX", afr.maximum);

  preferences.putInt("lambda1MIN", lambda1.minimum);
  preferences.putInt("lambda1MAX", lambda1.maximum);

  preferences.putInt("lambda2MIN", lambda2.minimum);
  preferences.putInt("lambda2MAX", lambda2.maximum);

  preferences.putInt("cltCMIN", coolantTemperature.minimum);
  preferences.putInt("cltCMAX", coolantTemperature.maximum);

  preferences.putInt("iatCMIN", intakeTemperature.minimum);
  preferences.putInt("iatCMAX", intakeTemperature.maximum);

  afr.minimum = afr.minimum / 100;
  afr.maximum = afr.maximum / 100;

  lambda1.minimum = lambda1.minimum / 100;
  lambda1.maximum = lambda1.maximum / 100;

  lambda2.minimum = lambda2.minimum / 100;
  lambda2.maximum = lambda2.maximum / 100;

  preferences.putInt("aux1CMIN", auxTemp1.minimum);
  preferences.putInt("aux1CMAX", auxTemp1.maximum);

  preferences.putInt("aux2CMIN", auxTemp2.minimum);
  preferences.putInt("aux2CMAX", auxTemp2.maximum);

  preferences.putInt("mcuCMIN", mcuTemp.minimum);
  preferences.putInt("mcuCMAX", mcuTemp.maximum);

  preferences.putInt("cltFMIN", coolantTemperature_f.minimum);
  preferences.putInt("cltFMAX", coolantTemperature_f.maximum);

  preferences.putInt("iatFMIN", intakeTemperature_f.minimum);
  preferences.putInt("iatFMAX", intakeTemperature_f.maximum);

  preferences.putInt("oilTFMIN", oilTemperature_f.minimum);
  preferences.putInt("oilTFMAX", oilTemperature_f.maximum);

  preferences.putInt("oilTMIN", oilTemperature.minimum);
  preferences.putInt("oilTMAX", oilTemperature.maximum);

  preferences.putInt("fuelTFMIN", fuelTemperature_f.minimum);
  preferences.putInt("fuelTFMAX", fuelTemperature_f.maximum);

  preferences.putInt("fuelTMIN", fuelTemperature.minimum);
  preferences.putInt("fuelTMAX", fuelTemperature.maximum);

  preferences.putInt("ignMIN", ignitionTiming.minimum);
  preferences.putInt("ignMAX", ignitionTiming.maximum);

  preferences.putInt("aux1FMIN", auxTemp1_f.minimum);
  preferences.putInt("aux1FMAX", auxTemp1_f.maximum);

  preferences.putInt("aux2FMIN", auxTemp2_f.minimum);
  preferences.putInt("aux2FMAX", auxTemp2_f.maximum);

  preferences.putInt("mapKPAMIN", manifoldPressure.minimum);
  preferences.putInt("mapKPAMAX", manifoldPressure.maximum);

  preferences.putInt("boostKPAMIN", boost_kpa.minimum);
  preferences.putInt("boostKPAMAX", boost_kpa.maximum);

  preferences.putInt("boostPSIMIN", boost_psi.minimum);
  preferences.putInt("boostPSIMAX", boost_psi.maximum);

  preferences.putInt("oilKPAMIN", oilPressure.minimum);
  preferences.putInt("oilKPAMAX", oilPressure.maximum);

  preferences.putInt("mapPSIMIN", manifoldPressure_psi.minimum);
  preferences.putInt("mapPSIMAX", manifoldPressure_psi.maximum);

  preferences.putInt("oilKPAMIN", oilPressure_psi.minimum);
  preferences.putInt("oilKPAMAX", oilPressure_psi.maximum);

  preferences.putInt("vvtMIN", vvtPosition.minimum);
  preferences.putInt("vvtMAX", vvtPosition.maximum);

  preferences.putInt("vvtEx1MIN", vvtExhaust1.minimum);
  preferences.putInt("vvtEx1MAX", vvtExhaust1.maximum);

  preferences.putInt("vvtEx2MIN", vvtExhaust2.minimum);
  preferences.putInt("vvtEx2MAX", vvtExhaust2.maximum);

  preferences.putInt("vvtIn1MIN", vvtIntake1.minimum);
  preferences.putInt("vvtIn1MAX", vvtIntake1.maximum);

  preferences.putInt("vvtIn2MIN", vvtIntake2.minimum);
  preferences.putInt("vvtIn2MAX", vvtIntake2.maximum);

  preferences.putInt("airMassMIN", airMass.minimum);
  preferences.putInt("airMassMAX", airMass.maximum);

  preferences.putInt("estAirMIN", estimatedAirflow.minimum);
  preferences.putInt("estAirMAX", estimatedAirflow.maximum);

  preferences.putInt("batVMIN", batteryVoltage.minimum);
  preferences.putInt("batVMAX", batteryVoltage.maximum);

  preferences.putInt("fpDeltaMIN", fuelPressDelta_kpa.minimum);
  preferences.putInt("fpDeltaMIN", fuelPressDelta_kpa.maximum);


  preferences.end();
}

void saveSensorAlerts() {

  preferences.begin("alerts", false);

  preferences.putInt("testLOW", testData.alertLow);
  preferences.putInt("testHI", testData.alertHigh);

  preferences.putInt("rpmLOW", rpm.alertLow);
  preferences.putInt("rpmHI", rpm.alertHigh);

  preferences.putInt("vssLOW", vss.alertLow);
  preferences.putInt("vssHI", vss.alertHigh);

  preferences.putInt("vssMPHLOW", vss_mph.alertLow);
  preferences.putInt("vssMPHHI", vss_mph.alertHigh);

  preferences.putInt("acceleratorLOW", accelerator.alertLow);
  preferences.putInt("acceleratorHI", accelerator.alertHigh);

  preferences.putInt("throttle1LOW", throttle1.alertLow);
  preferences.putInt("throttle1HI", throttle1.alertHigh);

  preferences.putInt("throttle2LOW", throttle2.alertLow);
  preferences.putInt("throttle2HI", throttle2.alertHigh);

  preferences.putInt("injDutyLOW", injectorDuty.alertLow);
  preferences.putInt("injDutyHI", injectorDuty.alertHigh);

  preferences.putInt("injPulseLOW", injectorPulse.alertLow);
  preferences.putInt("injPulseHI", injectorPulse.alertHigh);

  preferences.putInt("fuelPresHighLOW", fuelPressureHigh.alertLow);
  preferences.putInt("fuelPresHighHI", fuelPressureHigh.alertHigh);

  preferences.putInt("fuelPresLowLOW", fuelPressureLow.alertLow);
  preferences.putInt("fuelPresLowHI", fuelPressureLow.alertHigh);

  preferences.putInt("ethanolLOW", ethanol.alertLow);
  preferences.putInt("ethanolHI", ethanol.alertHigh);

  preferences.putInt("fuelTrimLOW", fuelTrim.alertLow);
  preferences.putInt("fuelTrimHI", fuelTrim.alertHigh);

  preferences.putInt("fuelLOW", fuel.alertLow);
  preferences.putInt("fuelHI", fuel.alertHigh);

  preferences.putInt("fuelUsedLOW", fuelConsumed.alertLow);
  preferences.putInt("fuelUsedHI", fuelConsumed.alertHigh);

  preferences.putInt("fuelFlowLOW", fuelConsumption.alertLow);
  preferences.putInt("fuelFlowHI", fuelConsumption.alertHigh);

  afr.alertLow = afr.alertLow * 100;
  afr.alertHigh = afr.alertHigh * 100;

  lambda1.alertLow = lambda1.alertLow * 100;
  lambda1.alertHigh = lambda1.alertHigh * 100;

  lambda2.alertLow = lambda2.alertLow * 100;
  lambda2.alertHigh = lambda2.alertHigh * 100;

  preferences.putInt("afrLOW", afr.alertLow);
  preferences.putInt("afrHI", afr.alertHigh);

  preferences.putInt("lambda1LOW", lambda1.alertLow);
  preferences.putInt("lambda1HI", lambda1.alertHigh);

  preferences.putInt("lambda2LOW", lambda2.alertLow);
  preferences.putInt("lambda2HI", lambda2.alertHigh);

  afr.alertLow = afr.alertLow / 100;
  afr.alertHigh = afr.alertHigh / 100;

  lambda1.alertLow = lambda1.alertLow / 100;
  lambda1.alertHigh = lambda1.alertHigh / 100;

  lambda2.alertLow = lambda2.alertLow / 100;
  lambda2.alertHigh = lambda2.alertHigh / 100;

  preferences.putInt("cltCLOW", coolantTemperature.alertLow);
  preferences.putInt("cltCHI", coolantTemperature.alertHigh);

  preferences.putInt("iatCLOW", intakeTemperature.alertLow);
  preferences.putInt("iatCHI", intakeTemperature.alertHigh);

  preferences.putInt("aux1CLOW", auxTemp1.alertLow);
  preferences.putInt("aux1CHI", auxTemp1.alertHigh);

  preferences.putInt("oilTFLOW", oilTemperature_f.alertLow);
  preferences.putInt("oilTFHI", oilTemperature_f.alertHigh);

  preferences.putInt("oilTLOW", oilTemperature.alertLow);
  preferences.putInt("oilTHI", oilTemperature.alertHigh);

  preferences.putInt("fuelTFLOW", fuelTemperature_f.alertLow);
  preferences.putInt("fuelTFHI", fuelTemperature_f.alertHigh);
  
  preferences.putInt("fuelTLOW", fuelTemperature.alertLow);
  preferences.putInt("fuelTHI", fuelTemperature.alertHigh);

  preferences.putInt("aux2CLOW", auxTemp2.alertLow);
  preferences.putInt("aux2CHI", auxTemp2.alertHigh);

  preferences.putInt("mcuCLOW", mcuTemp.alertLow);
  preferences.putInt("mcuCHI", mcuTemp.alertHigh);

  preferences.putInt("cltFLOW", coolantTemperature_f.alertLow);
  preferences.putInt("cltFHI", coolantTemperature_f.alertHigh);

  preferences.putInt("iatFLOW", intakeTemperature_f.alertLow);
  preferences.putInt("iatFHI", intakeTemperature_f.alertHigh);

  preferences.putInt("ignLOW", ignitionTiming.alertLow);
  preferences.putInt("ignHI", ignitionTiming.alertHigh);

  preferences.putInt("aux1FLOW", auxTemp1_f.alertLow);
  preferences.putInt("aux1FHI", auxTemp1_f.alertHigh);

  preferences.putInt("aux2FLOW", auxTemp2_f.alertLow);
  preferences.putInt("aux2FHI", auxTemp2_f.alertHigh);

  preferences.putInt("mapKPALOW", manifoldPressure.alertLow);
  preferences.putInt("mapKPAHI", manifoldPressure.alertHigh);

  preferences.putInt("boostKPALOW", boost_kpa.alertLow);
  preferences.putInt("boostKPAHI", boost_kpa.alertHigh);

  preferences.putInt("boostPSILOW", boost_psi.alertLow);
  preferences.putInt("boostPSIHI", boost_psi.alertHigh);

  preferences.putInt("oilKPALOW", oilPressure.alertLow);
  preferences.putInt("oilKPAHI", oilPressure.alertHigh);

  preferences.putInt("mapPSILOW", manifoldPressure_psi.alertLow);
  preferences.putInt("mapPSIHI", manifoldPressure_psi.alertHigh);

  preferences.putInt("oilKPALOW", oilPressure_psi.alertLow);
  preferences.putInt("oilKPAHI", oilPressure_psi.alertHigh);

  // preferences.putInt("vvtLOW", vvtPosition.alertLow);
  // preferences.putInt("vvtHI", vvtPosition.alertHigh);

  preferences.putInt("vvtEx1LOW", vvtExhaust1.alertLow);
  preferences.putInt("vvtEx1HI", vvtExhaust1.alertHigh);

  preferences.putInt("vvtEx2LOW", vvtExhaust2.alertLow);
  preferences.putInt("vvtEx2HI", vvtExhaust2.alertHigh);

  preferences.putInt("vvtIn1LOW", vvtIntake1.alertLow);
  preferences.putInt("vvtIn1HI", vvtIntake1.alertHigh);

  preferences.putInt("vvtIn2LOW", vvtIntake2.alertLow);
  preferences.putInt("vvtIn2HI", vvtIntake2.alertHigh);

  preferences.putInt("airMassLOW", airMass.alertLow);
  preferences.putInt("airMassHI", airMass.alertHigh);

  preferences.putInt("estAirLOW", estimatedAirflow.alertLow);
  preferences.putInt("estAirHI", estimatedAirflow.alertHigh);

  preferences.putInt("batVLOW", batteryVoltage.alertLow);
  preferences.putInt("batVHI", batteryVoltage.alertHigh);

  preferences.putInt("fpDeltaLOW", fuelPressDelta_kpa.alertLow);
  preferences.putInt("fpDeltaLOW", fuelPressDelta_kpa.alertHigh);


  preferences.end();
}

void eraseNVS() {

#ifdef DEBUG_SERIAL
  Serial.println("Erasing NVS!");
#endif

  nvs_flash_deinit();
  nvs_flash_erase();  // erase the NVS partition and...
  nvs_flash_init();   // initialize the NVS partition.
}

void setSensorMinMax(int sensor, float min, float max, float low, float high) {
//void setSensorMinMax(int sensor, float min, float newValue) {

  newSensorConfig = selectSensor(sensor);
  newSensorConfig->minimum = min;
  newSensorConfig->maximum = max;
  newSensorConfig->alertLow = low;
  newSensorConfig->alertHigh = high;

  // switch (limit) {
  //   case 1:
  //     newSensorConfig->minimum = newValue;
  //     break;

  //   case 2:
  //     newSensorConfig->maximum = newValue;
  //     break;

  //   case 3:
  //     newSensorConfig->alertLow = newValue;
  //     break;

  //   case 4:
  //     newSensorConfig->alertHigh = newValue;
  //     break;

  //   case 5:
  //     newSensorConfig->precision = newValue;
  //     break;

  //   default:
  //     break;
  // }
}

// void saveLedConfig()
// {

//   preferences.begin("led", false);
//   preferences.putUInt("LEDcolor", LEDcolor);
//   preferences.putUInt("LEDstyle", LEDstyle);
//   preferences.end();
// }

// void restoreLedConfig()
// {

//   preferences.begin("led", false);
//   LEDcolor = preferences.getUInt("LEDcolor", LEDcolor);
//   LEDstyle = preferences.getUInt("LEDstyle", LEDstyle);
//   preferences.end();
// }

void restoreWifi() {

  preferences.begin("wifi", false);

  size_t res = preferences.getString("ssid", ssid, 16);
  size_t res2 = preferences.getString("pw", password, 16);
  size_t res3 = preferences.getString("host", host, 16);

  preferences.end();

#ifdef DEBUG_SERIAL
  Serial.print("SSID ");
  Serial.println(ssid);
  Serial.print("pw ");
  Serial.println(password);
  Serial.print("host ");
  Serial.println(host);
#endif
}

void saveWifi() {

#ifdef DEBUG_SERIAL
  Serial.println("Saving new wifi config");
  Serial.print("SSID ");
  Serial.println(newSSID);
  Serial.print("pw ");
  Serial.println(newPW);
  Serial.print("host ");
  Serial.println(newHOST);

#endif
  preferences.begin("wifi", false);
  size_t save1 = preferences.putString("ssid", newSSID);
  size_t save2 = preferences.putString("pw", newPW);
  size_t save3 = preferences.putString("host", newHOST);
  preferences.end();
}

void saveBootConfig() {

  preferences.begin("boot", false);
  preferences.putUInt("bootLogo1", bootLogo1);
  preferences.putUInt("bootLogo2", bootLogo2);
  preferences.putUInt("bootLogo3", bootLogo3);
  preferences.putUInt("quickstart", quickstart);
  preferences.putUInt("logoTime_ms", logoTime_ms);
  preferences.putBool("startWifi", startWifi);
  preferences.putBool("startCan", startCan);
  preferences.end();
}

void restoreBootConfig() {

  preferences.begin("boot", false);
  bootLogo1 = preferences.getUInt("bootLogo1", BMM);
  bootLogo2 = preferences.getUInt("bootLogo2", FOME);
  bootLogo3 = preferences.getUInt("bootLogo3", KAN);
  quickstart = preferences.getUInt("quickstart", 0);
  logoTime_ms = preferences.getUInt("logoTime_ms", logoTime_ms);
  startWifi = preferences.getBool("startWifi", startWifi);
  startCan = preferences.getBool("startCan", startCan);
  preferences.end();
}


  //   Check NVS config version and wipe if it is not as expected
  //   Save startup config
  //   This will allow cleaning up stored configs if changes are made to the format

void checkNvsVer() {


  preferences.begin("startup", false);
  int nvsBuf = preferences.getUInt("nvs", 0);

  restoreBootConfig();
  restoreWifi();
  //restoreSensorMinMax();
  preferences.end();

  if (nvsBuf != nvs || nvsBuf == 99 || setToDefaults == true) {

    eraseNVS();

    preferences.begin("startup", false);
    preferences.putUInt("nvs", nvs);
    preferences.end();

    // Save default config
    saveBootConfig();
    saveWifi();
    //saveSensorMinMax();
    //saveSensorAlerts();

    nvsReset = true;
    setToDefaults = false;
  }
}

void saveArcConfig() {

  preferences.begin("arc", false);
  preferences.putUInt("arcColor1", arcColor1);
  preferences.putUInt("arcColor2", arcColor2);
  preferences.putUInt("arcSeg1", arcSeg1);
  preferences.putUInt("arcSeg2", arcSeg1);
  preferences.putUInt("arcInc1", arcInc1);
  preferences.putUInt("arcInc2", arcInc2);

  preferences.end();
}

void restoreArcConfig() {

  preferences.begin("arc", false);

  arcColor1 = preferences.getUInt("arcColor1", arcColor1);
  arcColor2 = preferences.getUInt("arcColor2", arcColor2);
  arcSeg1 = preferences.getUInt("arcSeg1", arcSeg1);
  arcSeg2 = preferences.getUInt("arcSeg2", arcSeg2);
  arcInc1 = preferences.getUInt("arcInc1", arcInc1);
  arcInc2 = preferences.getUInt("arcInc2", arcInc2);
  preferences.end();
}
void restoreLedColor() {

  preferences.begin("led", false);

  LEDred[3][0] = preferences.getUInt("red0", 255);
  LEDgreen[3][0] = preferences.getUInt("green0", 255);
  LEDblue[3][0] = preferences.getUInt("blue0", 255);
  LEDred[3][1] = preferences.getUInt("red1", 255);
  LEDgreen[3][1] = preferences.getUInt("green1", 255);
  LEDblue[3][1] = preferences.getUInt("blue1", 255);
  LEDred[3][2] = preferences.getUInt("red2", 255);
  LEDgreen[3][2] = preferences.getUInt("green2", 255);
  LEDblue[3][2] = preferences.getUInt("blue2", 255);
  LEDred[3][3] = preferences.getUInt("red3", 255);
  LEDgreen[3][3] = preferences.getUInt("green3", 255);
  LEDblue[3][3] = preferences.getUInt("blue3", 255);
  LEDred[3][4] = preferences.getUInt("red4", 255);
  LEDgreen[3][4] = preferences.getUInt("green4", 255);
  LEDblue[3][4] = preferences.getUInt("blue4", 255);
  LEDred[3][5] = preferences.getUInt("red5", 255);
  LEDgreen[3][5] = preferences.getUInt("green5", 255);
  LEDblue[3][5] = preferences.getUInt("blue5", 255);

  preferences.end();
}

void saveNewLedColor(const int index, int red, int green, int blue) {

  if (red > 255 || red < 0) {
    red = 255;
  }

  if (green > 255 || green < 0) {
    green = 255;
  }

  if (blue > 255 || blue < 0) {
    blue = 255;
  }

  preferences.begin("led", false);

  switch (index) {

    case 0:

      preferences.putUInt("red0", red);
      preferences.putUInt("green0", green);
      preferences.putUInt("blue0", blue);
      break;

    case 1:
      preferences.putUInt("red1", red);
      preferences.putUInt("green1", green);
      preferences.putUInt("blue1", blue);
      break;

    case 2:
      preferences.putUInt("red2", red);
      preferences.putUInt("green2", green);
      preferences.putUInt("blue2", blue);
      break;

    case 3:
      preferences.putUInt("red3", red);
      preferences.putUInt("green3", green);
      preferences.putUInt("blue3", blue);
      break;

    case 4:
      preferences.putUInt("red4", red);
      preferences.putUInt("green4", green);
      preferences.putUInt("blue4", blue);
      break;

    case 5:
      preferences.putUInt("red5", red);
      preferences.putUInt("green5", green);
      preferences.putUInt("blue5", blue);
      break;
  }
  preferences.end();

  restoreLedColor();
}

// ========================================================= Check Config =============================================

void checkNewConfig() {

  if (updateUserConfig == true) {
    setupUserConfig();
    resetDisplay = true;
    updateUserConfig = false;
  }

  if (readyToUpdateGaugeConfig == true) {

#ifdef DEBUG_SERIAL
    Serial.println("Updating Config");
#endif

    //gaugeSensor[selectedGauge] = selectedSensor;
    // wifiTimer_ms = wifiTimer_ms + wifiTimer_ms_increment;

#ifdef DEBUG_SERIAL
    Serial.print("Ptr 0 ");
    Serial.print(gaugeSensor[0]);

    Serial.print("Ptr 1 ");
    Serial.print(gaugeSensor[1]);

    Serial.print("Ptr 2 ");
    Serial.print(gaugeSensor[2]);

    Serial.print("Ptr 3 ");
    Serial.print(gaugeSensor[3]);

    Serial.print("Ptr 4 ");
    Serial.print(gaugeSensor[4]);

    Serial.print("Ptr 5 ");
    Serial.print(gaugeSensor[5]);

    Serial.print("Ptr 6 ");
    Serial.print(gaugeSensor[6]);
#endif

    for (int p = 0; (p < numDataPtr); p++) {
      ptrData[p] = selectSensor(gaugeSensor[p]);
    }

    //saveSensorSetting();
    //restoreSensorSetting();
    //saveGaugeType();

    saveDisplayRefresh();
    saveUserConfig();
    saveBrightnessSettings();

    readyToUpdateGaugeConfig = false;
    resetDisplay = true;
  }

  if (readyToUpdateLimits == true) {
    //setSensorMinMax(selectedSensor, selectedLimit, inputNewValue);
    setSensorMinMax(selectedSensor, newMin, newMax, newLow, newHigh);
    saveSensorMinMax();
    saveSensorAlerts();


    readyToUpdateLimits = false;
  }

  if (updateWifiConfig == true) {
    saveWifi();
    updateWifiConfig = false;
  }

  if (updateArcConfig == true) {
    saveArcConfig();
    updateArcConfig = false;
  }

  if (updateGaugeType == true) {
    //saveGaugeType();
    updateGaugeType = false;
  }
}
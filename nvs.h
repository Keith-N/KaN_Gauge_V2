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

String dataLocation[] = {"Inside Arc", "Outer Arc", "Center", "Bottom Left", "Center Bottom", "Bottom Right", "LEDs", "Top Left", "Top Right", "Meter", ""};
int gaugeSensor[] = {LAMBDA_1, OIL_PRESS_PSI, LAMBDA_1, COOLANT_TEMP_F, GEAR, OIL_PRESS_PSI, RPM, NO_DATA, NO_DATA, LAMBDA_1, NO_DATA};

int brightness[] = {80, 10, 80, 10};

int logoTime_ms = 600;

int selectedSensor;
int selectedLimit;
int selectedType;
int selectedGauge;
int selectedLedMode;
int selectedDisplayRate;
int brightnessInput;
int selectedBrightness = 3;

int gaugeDisplayType = 0;

String arcColors[] = {"Red", "Green", "Blue", "Blue to Red", "Green to Red", "Red to Green", "White", "Black", "Custom 1", "Custom 2"};
int customArcColor[] = {0, 0};

int arcColor1 = 4; // Green to Red
int arcColor2 = 3; // Blue to Red
int arcSeg1 = 3;
int arcSeg2 = 3;
int arcInc1 = 6;
int arcInc2 = 3;

int selectedColor[] = {65535, 63488, 63488, 63488, 0};
String colorName[] = {"Value", "Units", "Alert", "Needle", "Background"};

int bootLogo1 = 1; // BMM
int bootLogo2 = 2; // FOME
int bootLogo3 = 0; // KaN with version

int LEDcolor = 1; // LED config blue to red

int LEDstyle = 0;
String ledStyleName[] = {"Series Single Color", "Series Multi-Color", "Single LED"};
String ledColorName[] = {"None", "Blue -> Green -> Red", "Green -> Red", "Custom"};

int LEDred[4][6] = {{0, 0, 0, 0, 0, 0}, {0, 100, 150, 255, 255, 255}, {100, 100, 100, 100, 100, 255}, {255, 255, 255, 255, 255, 255}};
int LEDgreen[4][6] = {{0, 0, 0, 0, 0, 0}, {100, 200, 255, 150, 50, 0}, {200, 200, 200, 200, 200, 0}, {255, 255, 255, 255, 255, 255}};
int LEDblue[4][6] = {{0, 0, 0, 0, 0, 0}, {150, 40, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {255, 255, 255, 255, 255, 255}};

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
bool ffAlert = false;
int quickstart = 0;
bool setToDefaults = false;
bool updateGaugeType = false;

bool startWifi = true;
bool startCan = true;

int displayRefresh_ms = 100;

//==============================================
//  Save and Restore Functions
//==============================================

sensorData *selectSensor(int dataSelection)
{

  switch (dataSelection)
  {
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

  default:
    return &afr;
  }
}

void saveGaugeType()
{
  preferences.begin("gaugeType", false);
  preferences.putUInt("gaugeType", gaugeDisplayType);
  preferences.putUInt("displayRate", displayRefresh_ms);
  preferences.end();
}

void restoreGaugeType()
{
  preferences.begin("gaugeType", false);
  gaugeDisplayType = preferences.getUInt("gaugeType", gaugeDisplayType);
  displayRefresh_ms = preferences.getUInt("displayRate", displayRefresh_ms);
  preferences.end();
}

void saveSensorSetting()
{
  // Open R/W
  preferences.begin("config", false);
  preferences.putUInt("sensor0", gaugeSensor[0]);
  preferences.putUInt("sensor1", gaugeSensor[1]);
  preferences.putUInt("sensor2", gaugeSensor[2]);
  preferences.putUInt("sensor3", gaugeSensor[3]);
  preferences.putUInt("sensor4", gaugeSensor[4]);
  preferences.putUInt("sensor5", gaugeSensor[5]);
  preferences.putUInt("sensor6", gaugeSensor[6]);
  preferences.putUInt("sensor7", gaugeSensor[7]);
  preferences.putUInt("sensor8", gaugeSensor[8]);
  preferences.putUInt("sensor9", gaugeSensor[9]);
  preferences.end();
}

void saveBrightnessSettings()
{
  // Open R/W
  preferences.begin("bright", false);
  preferences.putUInt("dispL", brightness[0]);
  preferences.putUInt("dispH", brightness[1]);
  preferences.putUInt("ledL", brightness[2]);
  preferences.putUInt("ledH", brightness[3]);
  preferences.end();
}

void restoreBrightnessSettings()
{
  preferences.begin("bright", false);
  brightness[0] = preferences.getUInt("dispL", brightness[0]);
  brightness[1] = preferences.getUInt("dispH", brightness[1]);
  brightness[2] = preferences.getUInt("ledL", brightness[2]);
  brightness[3] = preferences.getUInt("ledH", brightness[3]);
  preferences.end();
}

void restoreSensorSetting()
{
  // Open RO
  preferences.begin("config", false);
  gaugeSensor[0] = preferences.getUInt("sensor0", gaugeSensor[0]);
  gaugeSensor[1] = preferences.getUInt("sensor1", gaugeSensor[1]);
  gaugeSensor[2] = preferences.getUInt("sensor2", gaugeSensor[2]);
  gaugeSensor[3] = preferences.getUInt("sensor3", gaugeSensor[3]);
  gaugeSensor[4] = preferences.getUInt("sensor4", gaugeSensor[4]);
  gaugeSensor[5] = preferences.getUInt("sensor5", gaugeSensor[5]);
  gaugeSensor[6] = preferences.getUInt("sensor6", gaugeSensor[6]);
  gaugeSensor[7] = preferences.getUInt("sensor7", gaugeSensor[7]);
  gaugeSensor[8] = preferences.getUInt("sensor8", gaugeSensor[8]);
  gaugeSensor[9] = preferences.getUInt("sensor9", gaugeSensor[9]);

#ifdef DEBUG_SERIAL
  Serial.print("Ptr 0 ");
  Serial.println(gaugeSensor[0]);

  Serial.print("Ptr 1 ");
  Serial.println(gaugeSensor[1]);

  Serial.print("Ptr 2 ");
  Serial.println(gaugeSensor[2]);

  Serial.print("Ptr 3 ");
  Serial.println(gaugeSensor[3]);

  Serial.print("Ptr 4 ");
  Serial.println(gaugeSensor[4]);

  Serial.print("Ptr 5 ");
  Serial.println(gaugeSensor[5]);

  Serial.print("Ptr 6 ");
  Serial.println(gaugeSensor[6]);
#endif

  preferences.end();
}

void restoreSensorMinMax()
{
  preferences.begin("MinMax", false);

  testData.minimum = preferences.getFloat("testMIN", testData.minimum);
  testData.maximum = preferences.getFloat("testMAX", testData.maximum);

  rpm.minimum = preferences.getFloat("rpmMIN", rpm.minimum);
  rpm.maximum = preferences.getFloat("rpmMAX", rpm.maximum);

  vss.minimum = preferences.getFloat("vssMIN", vss.minimum);
  vss.maximum = preferences.getFloat("vssMAX", vss.maximum);

  vss_mph.minimum = preferences.getFloat("vssMPHMIN", vss_mph.minimum);
  vss_mph.maximum = preferences.getFloat("vssMPHMAX", vss_mph.maximum);

  accelerator.minimum = preferences.getFloat("acceleratorMIN", accelerator.minimum);
  accelerator.maximum = preferences.getFloat("acceleratorMAX", accelerator.maximum);

  throttle1.minimum = preferences.getFloat("throttle1MIN", throttle1.minimum);
  throttle1.maximum = preferences.getFloat("throttle1MAX", throttle1.maximum);

  throttle2.minimum = preferences.getFloat("throttle2MIN", throttle2.minimum);
  throttle2.maximum = preferences.getFloat("throttle2MAX", throttle2.maximum);

  injectorDuty.minimum = preferences.getFloat("injDutyMIN", injectorDuty.minimum);
  injectorDuty.maximum = preferences.getFloat("injDutyMAX", injectorDuty.maximum);

  injectorPulse.minimum = preferences.getFloat("injPulseMIN", injectorPulse.minimum);
  injectorPulse.maximum = preferences.getFloat("injPulseMAX", injectorPulse.maximum);

  fuelPressureHigh.minimum = preferences.getFloat("fuelPresHighMIN", fuelPressureHigh.minimum);
  fuelPressureHigh.maximum = preferences.getFloat("fuelPresHighMAX", fuelPressureHigh.maximum);

  fuelPressureLow.minimum = preferences.getFloat("fuelPresLowMIN", fuelPressureLow.minimum);
  fuelPressureLow.maximum = preferences.getFloat("fuelPresLowMAX", fuelPressureLow.maximum);

  ethanol.minimum = preferences.getFloat("ethanolMIN", ethanol.minimum);
  ethanol.maximum = preferences.getFloat("ethanolMAX", ethanol.maximum);

  fuelTrim.minimum = preferences.getFloat("fuelTrimMIN", fuelTrim.minimum);
  fuelTrim.maximum = preferences.getFloat("fuelTrimMAX", fuelTrim.maximum);

  fuel.minimum = preferences.getFloat("fuelMIN", fuel.minimum);
  fuel.maximum = preferences.getFloat("fuelMAX", fuel.maximum);

  fuelConsumed.minimum = preferences.getFloat("fuelUsedMIN", fuelConsumed.minimum);
  fuelConsumed.maximum = preferences.getFloat("fuelUsedMAX", fuelConsumed.maximum);

  fuelConsumption.minimum = preferences.getFloat("fuelFlowMIN", fuelConsumption.minimum);
  fuelConsumption.maximum = preferences.getFloat("fuelFlowMAX", fuelConsumption.maximum);

  afr.minimum = preferences.getFloat("afrMIN", afr.minimum);
  afr.maximum = preferences.getFloat("afrMAX", afr.maximum);

  lambda1.minimum = preferences.getFloat("lambda1MIN", lambda1.minimum);
  lambda1.maximum = preferences.getFloat("lambda1MAX", lambda1.maximum);

  lambda2.minimum = preferences.getFloat("lambda2MIN", lambda1.minimum);
  lambda2.maximum = preferences.getFloat("lambda2MAX", lambda1.maximum);

  coolantTemperature.minimum = preferences.getFloat("cltCMIN", coolantTemperature.minimum);
  coolantTemperature.maximum = preferences.getFloat("cltCMAX", coolantTemperature.maximum);

  intakeTemperature.minimum = preferences.getFloat("iatCMIN", intakeTemperature.minimum);
  intakeTemperature.maximum = preferences.getFloat("iatCMAX", intakeTemperature.maximum);

  auxTemp1.minimum = preferences.getFloat("aux1CMIN", auxTemp1.minimum);
  auxTemp1.maximum = preferences.getFloat("aux1CMAX", auxTemp1.maximum);

  auxTemp2.minimum = preferences.getFloat("aux2CMIN", auxTemp2.minimum);
  auxTemp2.maximum = preferences.getFloat("aux2CMAX", auxTemp2.maximum);

  mcuTemp.minimum = preferences.getFloat("mcuCMIN", mcuTemp.minimum);
  mcuTemp.maximum = preferences.getFloat("mcuCMAX", mcuTemp.maximum);

  coolantTemperature_f.minimum = preferences.getFloat("cltFMIN", coolantTemperature_f.minimum);
  coolantTemperature_f.maximum = preferences.getFloat("cltFMAX", coolantTemperature_f.maximum);

  intakeTemperature_f.minimum = preferences.getFloat("iatFMIN", intakeTemperature_f.minimum);
  intakeTemperature_f.maximum = preferences.getFloat("iatFMAX", intakeTemperature_f.maximum);

  ignitionTiming.minimum = preferences.getFloat("ignMIN", ignitionTiming.minimum);
  ignitionTiming.maximum = preferences.getFloat("ignMAX", ignitionTiming.maximum);

  auxTemp1_f.minimum = preferences.getFloat("aux1FMIN", auxTemp1_f.minimum);
  auxTemp1_f.maximum = preferences.getFloat("aux1FMAX", auxTemp1_f.maximum);
  auxTemp2_f.minimum = preferences.getFloat("aux2FMIN", auxTemp2_f.minimum);
  auxTemp2_f.maximum = preferences.getFloat("aux2FMAX", auxTemp2_f.maximum);

  manifoldPressure.minimum = preferences.getFloat("mapKPAMIN", manifoldPressure.minimum);
  manifoldPressure.maximum = preferences.getFloat("mapKPAMAX", manifoldPressure.maximum);

  boost_kpa.minimum = preferences.getFloat("boostKPAMIN", boost_kpa.minimum);
  boost_kpa.maximum = preferences.getFloat("boostKPAMAX", boost_kpa.maximum);

  boost_psi.minimum = preferences.getFloat("boostPSIMIN", boost_psi.minimum);
  boost_psi.maximum = preferences.getFloat("boostPSIMAX", boost_psi.maximum);

  oilPressure.minimum = preferences.getFloat("oilKPAMIN", oilPressure.minimum);
  oilPressure.maximum = preferences.getFloat("oilKPAMAX", oilPressure.maximum);

  manifoldPressure_psi.minimum = preferences.getFloat("mapPSIMIN", manifoldPressure_psi.minimum);
  manifoldPressure_psi.maximum = preferences.getFloat("mapPSIMAX", manifoldPressure_psi.maximum);

  oilPressure_psi.minimum = preferences.getFloat("oilKPAMIN", oilPressure_psi.minimum);
  oilPressure_psi.maximum = preferences.getFloat("oilKPAMAX", oilPressure_psi.maximum);

  vvtPosition.minimum = preferences.getFloat("vvtMIN", vvtPosition.minimum);
  vvtPosition.maximum = preferences.getFloat("vvtMAX", vvtPosition.maximum);

  vvtExhaust1.minimum = preferences.getFloat("vvtEx1MIN", vvtExhaust1.minimum);
  vvtExhaust1.maximum = preferences.getFloat("vvtEx1MAX", vvtExhaust1.maximum);

  vvtExhaust2.minimum = preferences.getFloat("vvtEx2MIN", vvtExhaust2.minimum);
  vvtExhaust2.maximum = preferences.getFloat("vvtEx2MAX", vvtExhaust2.maximum);

  vvtIntake1.minimum = preferences.getFloat("vvtIn1MIN", vvtIntake1.minimum);
  vvtIntake1.maximum = preferences.getFloat("vvtIn1MAX", vvtIntake1.maximum);

  vvtIntake2.minimum = preferences.getFloat("vvtIn2MIN", vvtIntake2.minimum);
  vvtIntake2.maximum = preferences.getFloat("vvtIn2MAX", vvtIntake2.maximum);

  airMass.minimum = preferences.getFloat("airMassMIN", airMass.minimum);
  airMass.maximum = preferences.getFloat("airMassMAX", airMass.maximum);

  estimatedAirflow.minimum = preferences.getFloat("estAirMIN", estimatedAirflow.minimum);
  estimatedAirflow.maximum = preferences.getFloat("estAirMAX", estimatedAirflow.maximum);

  batteryVoltage.minimum = preferences.getFloat("batVMIN", batteryVoltage.minimum);
  batteryVoltage.maximum = preferences.getFloat("batVMAX", batteryVoltage.maximum);

  fuelPressDelta_kpa.minimum = preferences.getFloat("fpDeltaMIN", fuelPressDelta_kpa.minimum);
  fuelPressDelta_kpa.maximum = preferences.getFloat("fpDeltaMIN", fuelPressDelta_kpa.maximum);

  preferences.end();

}

void restoreSensorAlerts()
{
  preferences.begin("alerts", false);

  testData.alertLow = preferences.getFloat("testLOW", testData.alertLow);
  testData.alertHigh = preferences.getFloat("testHI", testData.alertHigh);

  rpm.alertLow = preferences.getFloat("rpmLOW", rpm.alertLow);
  rpm.alertHigh = preferences.getFloat("rpmHI", rpm.alertHigh);

  vss.alertLow = preferences.getFloat("vssLOW", vss.alertLow);
  vss.alertHigh = preferences.getFloat("vssHI", vss.alertHigh);

  vss_mph.alertLow = preferences.getFloat("vssMPHLOW", vss_mph.alertLow);
  vss_mph.alertHigh = preferences.getFloat("vssMPHHI", vss_mph.alertHigh);

  accelerator.alertLow = preferences.getFloat("acceleratorLOW", accelerator.alertLow);
  accelerator.alertHigh = preferences.getFloat("acceleratorHI", accelerator.alertHigh);

  throttle1.alertLow = preferences.getFloat("throttle1LOW", throttle1.alertLow);
  throttle1.alertHigh = preferences.getFloat("throttle1HI", throttle1.alertHigh);

  throttle2.alertLow = preferences.getFloat("throttle2LOW", throttle2.alertLow);
  throttle2.alertHigh = preferences.getFloat("throttle2HI", throttle2.alertHigh);

  injectorDuty.alertLow = preferences.getFloat("injDutyLOW", injectorDuty.alertLow);
  injectorDuty.alertHigh = preferences.getFloat("injDutyHI", injectorDuty.alertHigh);

  injectorPulse.alertLow = preferences.getFloat("injPulseLOW", injectorPulse.alertLow);
  injectorPulse.alertHigh = preferences.getFloat("injPulseHI", injectorPulse.alertHigh);

  fuelPressureHigh.alertLow = preferences.getFloat("fuelPresHighLOW", fuelPressureHigh.alertLow);
  fuelPressureHigh.alertHigh = preferences.getFloat("fuelPresHighHI", fuelPressureHigh.alertHigh);

  fuelPressureLow.alertLow = preferences.getFloat("fuelPresLowLOW", fuelPressureLow.alertLow);
  fuelPressureLow.alertHigh = preferences.getFloat("fuelPresLowHI", fuelPressureLow.alertHigh);

  ethanol.alertLow = preferences.getFloat("ethanolLOW", ethanol.alertLow);
  ethanol.alertHigh = preferences.getFloat("ethanolHI", ethanol.alertHigh);

  fuelTrim.alertLow = preferences.getFloat("fuelTrimLOW", fuelTrim.alertLow);
  fuelTrim.alertHigh = preferences.getFloat("fuelTrimHI", fuelTrim.alertHigh);

  fuel.alertLow = preferences.getFloat("fuelLOW", fuel.alertLow);
  fuel.alertHigh = preferences.getFloat("fuelHI", fuel.alertHigh);

  fuelConsumed.alertLow = preferences.getFloat("fuelUsedLOW", fuelConsumed.alertLow);
  fuelConsumed.alertHigh = preferences.getFloat("fuelUsedHI", fuelConsumed.alertHigh);

  fuelConsumption.alertLow = preferences.getFloat("fuelFlowLOW", fuelConsumption.alertLow);
  fuelConsumption.alertHigh = preferences.getFloat("fuelFlowHI", fuelConsumption.alertHigh);

  afr.alertLow = preferences.getFloat("afrLOW", afr.alertLow);
  afr.alertHigh = preferences.getFloat("afrHI", afr.alertHigh);

  lambda1.alertLow = preferences.getFloat("lambda1LOW", lambda1.alertLow);
  lambda1.alertHigh = preferences.getFloat("lambda1HI", lambda1.alertHigh);

  lambda2.alertLow = preferences.getFloat("lambda2LOW", lambda1.alertLow);
  lambda2.alertHigh = preferences.getFloat("lambda2HI", lambda1.alertHigh);

  coolantTemperature.alertLow = preferences.getFloat("cltCLOW", coolantTemperature.alertLow);
  coolantTemperature.alertHigh = preferences.getFloat("cltCHI", coolantTemperature.alertHigh);

  intakeTemperature.alertLow = preferences.getFloat("iatCLOW", intakeTemperature.alertLow);
  intakeTemperature.alertHigh = preferences.getFloat("iatCHI", intakeTemperature.alertHigh);

  auxTemp1.alertLow = preferences.getFloat("aux1CLOW", auxTemp1.alertLow);
  auxTemp1.alertHigh = preferences.getFloat("aux1CHI", auxTemp1.alertHigh);

  auxTemp2.alertLow = preferences.getFloat("aux2CLOW", auxTemp2.alertLow);
  auxTemp2.alertHigh = preferences.getFloat("aux2CHI", auxTemp2.alertHigh);

  mcuTemp.alertLow = preferences.getFloat("mcuCLOW", mcuTemp.alertLow);
  mcuTemp.alertHigh = preferences.getFloat("mcuCHI", mcuTemp.alertHigh);

  coolantTemperature_f.alertLow = preferences.getFloat("cltFLOW", coolantTemperature_f.alertLow);
  coolantTemperature_f.alertHigh = preferences.getFloat("cltFHI", coolantTemperature_f.alertHigh);

  intakeTemperature_f.alertLow = preferences.getFloat("iatFLOW", intakeTemperature_f.alertLow);
  intakeTemperature_f.alertHigh = preferences.getFloat("iatFHI", intakeTemperature_f.alertHigh);

  ignitionTiming.alertLow = preferences.getFloat("ignLOW", ignitionTiming.alertLow);
  ignitionTiming.alertHigh = preferences.getFloat("ignHI", ignitionTiming.alertHigh);

  auxTemp1_f.alertLow = preferences.getFloat("aux1FLOW", auxTemp1_f.alertLow);
  auxTemp1_f.alertHigh = preferences.getFloat("aux1FHI", auxTemp1_f.alertHigh);

  auxTemp2_f.alertLow = preferences.getFloat("aux2FLOW", auxTemp2_f.alertLow);
  auxTemp2_f.alertHigh = preferences.getFloat("aux2FHI", auxTemp2_f.alertHigh);

  manifoldPressure.alertLow = preferences.getFloat("mapKPALOW", manifoldPressure.alertLow);
  manifoldPressure.alertHigh = preferences.getFloat("mapKPAHI", manifoldPressure.alertHigh);

  boost_kpa.alertLow = preferences.getFloat("boostKPALOW", boost_kpa.alertLow);
  boost_kpa.alertHigh = preferences.getFloat("boostKPAHI", boost_kpa.alertHigh);

  boost_psi.alertLow = preferences.getFloat("boostPSILOW", boost_psi.alertLow);
  boost_psi.alertHigh = preferences.getFloat("boostPSIHI", boost_psi.alertHigh);

  oilPressure.alertLow = preferences.getFloat("oilKPALOW", oilPressure.alertLow);
  oilPressure.alertHigh = preferences.getFloat("oilKPAHI", oilPressure.alertHigh);

  manifoldPressure_psi.alertLow = preferences.getFloat("mapPSILOW", manifoldPressure_psi.alertLow);
  manifoldPressure_psi.alertHigh = preferences.getFloat("mapPSIHI", manifoldPressure_psi.alertHigh);

  oilPressure_psi.alertLow = preferences.getFloat("oilKPALOW", oilPressure_psi.alertLow);
  oilPressure_psi.alertHigh = preferences.getFloat("oilKPAHI", oilPressure_psi.alertHigh);

  vvtPosition.alertLow = preferences.getFloat("vvtLOW", vvtPosition.alertLow);
  vvtPosition.alertHigh = preferences.getFloat("vvtHI", vvtPosition.alertHigh);

  vvtExhaust1.alertLow = preferences.getFloat("vvtEx1LOW", vvtExhaust1.alertLow);
  vvtExhaust1.alertHigh = preferences.getFloat("vvtEx1HI", vvtExhaust1.alertHigh);

  vvtExhaust2.alertLow = preferences.getFloat("vvtEx2LOW", vvtExhaust2.alertLow);
  vvtExhaust2.alertHigh = preferences.getFloat("vvtEx2HI", vvtExhaust2.alertHigh);

  vvtIntake1.alertLow = preferences.getFloat("vvtIn1LOW", vvtIntake1.alertLow);
  vvtIntake1.alertHigh = preferences.getFloat("vvtIn1HI", vvtIntake1.alertHigh);

  vvtIntake2.alertLow = preferences.getFloat("vvtIn2LOW", vvtIntake2.alertLow);
  vvtIntake2.alertHigh = preferences.getFloat("vvtIn2HI", vvtIntake2.alertHigh);

  airMass.alertLow = preferences.getFloat("airMassLOW", airMass.alertLow);
  airMass.alertHigh = preferences.getFloat("airMassHI", airMass.alertHigh);

  estimatedAirflow.alertLow = preferences.getFloat("estAirLOW", estimatedAirflow.alertLow);
  estimatedAirflow.alertHigh = preferences.getFloat("estAirHI", estimatedAirflow.alertHigh);

  batteryVoltage.alertLow = preferences.getFloat("batVLOW", batteryVoltage.alertLow);
  batteryVoltage.alertHigh = preferences.getFloat("batVHI", batteryVoltage.alertHigh);

  fuelPressDelta_kpa.alertLow = preferences.getFloat("fpDeltaLOW", fuelPressDelta_kpa.alertLow);
  fuelPressDelta_kpa.alertHigh = preferences.getFloat("fpDeltaHI", fuelPressDelta_kpa.alertHigh);

  preferences.end();


}

void restoreSensorPrecsision()
{
  preferences.begin("precision", false);

  testData.precision = preferences.getFloat("testprecision", testData.precision);
  rpm.precision = preferences.getFloat("rpmprecision", rpm.precision);
  vss.precision = preferences.getFloat("vssprecision", vss.precision);
  vss_mph.precision = preferences.getFloat("vssMPHprecision", vss_mph.precision);
  accelerator.precision = preferences.getFloat("acceleratorprecision", accelerator.precision);
  throttle1.precision = preferences.getFloat("throttle1precision", throttle1.precision);
  throttle2.precision = preferences.getFloat("throttle2precision", throttle2.precision);
  injectorDuty.precision = preferences.getFloat("injDutyprecision", injectorDuty.precision);
  injectorPulse.precision = preferences.getFloat("injPulseprecision", injectorPulse.precision);
  fuelPressureHigh.precision = preferences.getFloat("fuelPresHighprecision", fuelPressureHigh.precision);
  fuelPressureLow.precision = preferences.getFloat("fuelPresLowprecision", fuelPressureLow.precision);
  ethanol.precision = preferences.getFloat("ethanolprecision", ethanol.precision);
  fuelTrim.precision = preferences.getFloat("fuelTrimprecision", fuelTrim.precision);
  fuel.precision = preferences.getFloat("fuelprecision", fuel.precision);
  fuelConsumed.precision = preferences.getFloat("fuelUsedprecision", fuelConsumed.precision);
  fuelConsumption.precision = preferences.getFloat("fuelFlowprecision", fuelConsumption.precision);
  afr.precision = preferences.getFloat("afrprecision", afr.precision);
  lambda1.precision = preferences.getFloat("lambda1precision", lambda1.precision);
  lambda2.precision = preferences.getFloat("lambda2precision", lambda2.precision);
  coolantTemperature.precision = preferences.getFloat("cltCprecision", coolantTemperature.precision);
  intakeTemperature.precision = preferences.getFloat("iatCprecision", intakeTemperature.precision);
  auxTemp1.precision = preferences.getFloat("aux1precision", auxTemp1.precision);
  auxTemp2.precision = preferences.getFloat("aux2Cprecision", auxTemp2.precision);
  mcuTemp.precision = preferences.getFloat("mcuCprecision", mcuTemp.precision);
  coolantTemperature_f.precision = preferences.getFloat("cltFprecision", coolantTemperature_f.precision);
  intakeTemperature_f.precision = preferences.getFloat("iatprecision", intakeTemperature_f.precision);
  ignitionTiming.precision = preferences.getFloat("ignprecision", ignitionTiming.precision);
  auxTemp1_f.precision = preferences.getFloat("aux1precision", auxTemp1_f.precision);
  auxTemp2_f.precision = preferences.getFloat("aux2precision", auxTemp2_f.precision);
  manifoldPressure.precision = preferences.getFloat("mapKprecision", manifoldPressure.precision);
  boost_kpa.precision = preferences.getFloat("boostKprecision", boost_kpa.precision);
  boost_psi.precision = preferences.getFloat("boostPprecision", boost_psi.precision);
  oilPressure.precision = preferences.getFloat("oilKPAprecision", oilPressure.precision);
  manifoldPressure_psi.precision = preferences.getFloat("mapKPAprecision", manifoldPressure_psi.precision);
  oilPressure_psi.precision = preferences.getFloat("oilKPAprecision", oilPressure_psi.precision);
  vvtPosition.precision = preferences.getFloat("vvtprecision", vvtPosition.precision);
  vvtExhaust1.precision = preferences.getFloat("vvtEx1precision", vvtExhaust1.precision);
  vvtExhaust2.precision = preferences.getFloat("vvtEx2precision", vvtExhaust2.precision);
  vvtIntake1.precision = preferences.getFloat("vvtIn1precision", vvtIntake1.precision);
  vvtIntake2.precision = preferences.getFloat("vvtIn1precision", vvtIntake2.precision);
  airMass.precision = preferences.getFloat("airMassprecision", airMass.precision);
  estimatedAirflow.precision = preferences.getFloat("estAirprecision", estimatedAirflow.precision);
  batteryVoltage.precision = preferences.getFloat("batVprecision", batteryVoltage.precision);
  fuelPressDelta_kpa.precision = preferences.getFloat("fpDeltaprecision", fuelPressDelta_kpa.precision);


  preferences.end();
}

void saveSensorMinMax()
{


  preferences.begin("MinMax", false);

  preferences.putFloat("testMIN", testData.minimum);
  preferences.putFloat("testMAX", testData.maximum);

  preferences.putFloat("rpmMIN", rpm.minimum);
  preferences.putFloat("rpmMAX", rpm.maximum);

  preferences.putFloat("vssMIN", vss.minimum);
  preferences.putFloat("vssMAX", vss.maximum);

  preferences.putFloat("vssMPHMIN", vss_mph.minimum);
  preferences.putFloat("vssMPHMAX", vss_mph.maximum);

  preferences.putFloat("acceleratorMIN", accelerator.minimum);
  preferences.putFloat("acceleratorMAX", accelerator.maximum);

  preferences.putFloat("throttle1MIN", throttle1.minimum);
  preferences.putFloat("throttle1MAX", throttle1.maximum);

  preferences.putFloat("throttle2MIN", throttle2.minimum);
  preferences.putFloat("throttle2MAX", throttle2.maximum);

  preferences.putFloat("injDutyMIN", injectorDuty.minimum);
  preferences.putFloat("injDutyMAX", injectorDuty.maximum);

  preferences.putFloat("injPulseMIN", injectorPulse.minimum);
  preferences.putFloat("injPulseMAX", injectorPulse.maximum);

  preferences.putFloat("fuelPresHighMIN", fuelPressureHigh.minimum);
  preferences.putFloat("fuelPresHighMAX", fuelPressureHigh.maximum);

  preferences.putFloat("fuelPresLowMIN", fuelPressureLow.minimum);
  preferences.putFloat("fuelPresLowMAX", fuelPressureLow.maximum);

  preferences.putFloat("ethanolMIN", ethanol.minimum);
  preferences.putFloat("ethanolMAX", ethanol.maximum);

  preferences.putFloat("fuelTrimMIN", fuelTrim.minimum);
  preferences.putFloat("fuelTrimMAX", fuelTrim.maximum);

  preferences.putFloat("fuelMIN", fuel.minimum);
  preferences.putFloat("fuelMAX", fuel.maximum);

  preferences.putFloat("fuelUsedMIN", fuelConsumed.minimum);
  preferences.putFloat("fuelUsedMAX", fuelConsumed.maximum);

  preferences.putFloat("fuelFlowMIN", fuelConsumption.minimum);
  preferences.putFloat("fuelFlowMAX", fuelConsumption.maximum);

  preferences.putFloat("afrMIN", afr.minimum);
  preferences.putFloat("afrMAX", afr.maximum);

  preferences.putFloat("lambda1MIN", lambda1.minimum);
  preferences.putFloat("lambda1MAX", lambda1.maximum);

  preferences.putFloat("lambda2MIN", lambda2.minimum);
  preferences.putFloat("lambda2MAX", lambda2.maximum);

  preferences.putFloat("cltCMIN", coolantTemperature.minimum);
  preferences.putFloat("cltCMAX", coolantTemperature.maximum);

  preferences.putFloat("iatCMIN", intakeTemperature.minimum);
  preferences.putFloat("iatCMAX", intakeTemperature.maximum);

  preferences.putFloat("aux1CMIN", auxTemp1.minimum);
  preferences.putFloat("aux1CMAX", auxTemp1.maximum);

  preferences.putFloat("aux2CMIN", auxTemp2.minimum);
  preferences.putFloat("aux2CMAX", auxTemp2.maximum);

  preferences.putFloat("mcuCMIN", mcuTemp.minimum);
  preferences.putFloat("mcuCMAX", mcuTemp.maximum);

  preferences.putFloat("cltFMIN", coolantTemperature_f.minimum);
  preferences.putFloat("cltFMAX", coolantTemperature_f.maximum);

  preferences.putFloat("iatFMIN", intakeTemperature_f.minimum);
  preferences.putFloat("iatFMAX", intakeTemperature_f.maximum);

  preferences.putFloat("ignMIN", ignitionTiming.minimum);
  preferences.putFloat("ignMAX", ignitionTiming.maximum);

  preferences.putFloat("aux1FMIN", auxTemp1_f.minimum);
  preferences.putFloat("aux1FMAX", auxTemp1_f.maximum);

  preferences.putFloat("aux2FMIN", auxTemp2_f.minimum);
  preferences.putFloat("aux2FMAX", auxTemp2_f.maximum);

  preferences.putFloat("mapKPAMIN", manifoldPressure.minimum);
  preferences.putFloat("mapKPAMAX", manifoldPressure.maximum);

  preferences.putFloat("boostKPAMIN", boost_kpa.minimum);
  preferences.putFloat("boostKPAMAX", boost_kpa.maximum);

  preferences.putFloat("boostPSIMIN", boost_psi.minimum);
  preferences.putFloat("boostPSIMAX", boost_psi.maximum);

  preferences.putFloat("oilKPAMIN", oilPressure.minimum);
  preferences.putFloat("oilKPAMAX", oilPressure.maximum);

  preferences.putFloat("mapPSIMIN", manifoldPressure_psi.minimum);
  preferences.putFloat("mapPSIMAX", manifoldPressure_psi.maximum);

  preferences.putFloat("oilKPAMIN", oilPressure_psi.minimum);
  preferences.putFloat("oilKPAMAX", oilPressure_psi.maximum);

  preferences.putFloat("vvtMIN", vvtPosition.minimum);
  preferences.putFloat("vvtMAX", vvtPosition.maximum);

  preferences.putFloat("vvtEx1MIN", vvtExhaust1.minimum);
  preferences.putFloat("vvtEx1MAX", vvtExhaust1.maximum);

  preferences.putFloat("vvtEx2MIN", vvtExhaust2.minimum);
  preferences.putFloat("vvtEx2MAX", vvtExhaust2.maximum);

  preferences.putFloat("vvtIn1MIN", vvtIntake1.minimum);
  preferences.putFloat("vvtIn1MAX", vvtIntake1.maximum);

  preferences.putFloat("vvtIn2MIN", vvtIntake2.minimum);
  preferences.putFloat("vvtIn2MAX", vvtIntake2.maximum);

  preferences.putFloat("airMassMIN", airMass.minimum);
  preferences.putFloat("airMassMAX", airMass.maximum);

  preferences.putFloat("estAirMIN", estimatedAirflow.minimum);
  preferences.putFloat("estAirMAX", estimatedAirflow.maximum);

  preferences.putFloat("batVMIN", batteryVoltage.minimum);
  preferences.putFloat("batVMAX", batteryVoltage.maximum);

  preferences.putFloat("fpDeltaMIN", fuelPressDelta_kpa.minimum);
  preferences.putFloat("fpDeltaMIN", fuelPressDelta_kpa.maximum);


  preferences.end();
}

void saveSensorAlerts()
{

  preferences.begin("alerts", false);

  preferences.putFloat("testLOW", testData.alertLow);
  preferences.putFloat("testHI", testData.alertHigh);

  preferences.putFloat("rpmLOW", rpm.alertLow);
  preferences.putFloat("rpmHI", rpm.alertHigh);

  preferences.putFloat("vssLOW", vss.alertLow);
  preferences.putFloat("vssHI", vss.alertHigh);

  preferences.putFloat("vssMPHLOW", vss_mph.alertLow);
  preferences.putFloat("vssMPHHI", vss_mph.alertHigh);

  preferences.putFloat("acceleratorLOW", accelerator.alertLow);
  preferences.putFloat("acceleratorHI", accelerator.alertHigh);

  preferences.putFloat("throttle1LOW", throttle1.alertLow);
  preferences.putFloat("throttle1HI", throttle1.alertHigh);

  preferences.putFloat("throttle2LOW", throttle2.alertLow);
  preferences.putFloat("throttle2HI", throttle2.alertHigh);

  preferences.putFloat("injDutyLOW", injectorDuty.alertLow);
  preferences.putFloat("injDutyHI", injectorDuty.alertHigh);

  preferences.putFloat("injPulseLOW", injectorPulse.alertLow);
  preferences.putFloat("injPulseHI", injectorPulse.alertHigh);

  preferences.putFloat("fuelPresHighLOW", fuelPressureHigh.alertLow);
  preferences.putFloat("fuelPresHighHI", fuelPressureHigh.alertHigh);

  preferences.putFloat("fuelPresLowLOW", fuelPressureLow.alertLow);
  preferences.putFloat("fuelPresLowHI", fuelPressureLow.alertHigh);

  preferences.putFloat("ethanolLOW", ethanol.alertLow);
  preferences.putFloat("ethanolHI", ethanol.alertHigh);

  preferences.putFloat("fuelTrimLOW", fuelTrim.alertLow);
  preferences.putFloat("fuelTrimHI", fuelTrim.alertHigh);

  preferences.putFloat("fuelLOW", fuel.alertLow);
  preferences.putFloat("fuelHI", fuel.alertHigh);

  preferences.putFloat("fuelUsedLOW", fuelConsumed.alertLow);
  preferences.putFloat("fuelUsedHI", fuelConsumed.alertHigh);

  preferences.putFloat("fuelFlowLOW", fuelConsumption.alertLow);
  preferences.putFloat("fuelFlowHI", fuelConsumption.alertHigh);

  preferences.putFloat("afrLOW", afr.alertLow);
  preferences.putFloat("afrHI", afr.alertHigh);

  preferences.putFloat("lambda1LOW", lambda1.alertLow);
  preferences.putFloat("lambda1HI", lambda1.alertHigh);

  preferences.putFloat("lambda2LOW", lambda2.alertLow);
  preferences.putFloat("lambda2HI", lambda2.alertHigh);

  preferences.putFloat("cltCLOW", coolantTemperature.alertLow);
  preferences.putFloat("cltCHI", coolantTemperature.alertHigh);

  preferences.putFloat("iatCLOW", intakeTemperature.alertLow);
  preferences.putFloat("iatCHI", intakeTemperature.alertHigh);

  preferences.putFloat("aux1CLOW", auxTemp1.alertLow);
  preferences.putFloat("aux1CHI", auxTemp1.alertHigh);

  preferences.putFloat("aux2CLOW", auxTemp2.alertLow);
  preferences.putFloat("aux2CHI", auxTemp2.alertHigh);

  preferences.putFloat("mcuCLOW", mcuTemp.alertLow);
  preferences.putFloat("mcuCHI", mcuTemp.alertHigh);

  preferences.putFloat("cltFLOW", coolantTemperature_f.alertLow);
  preferences.putFloat("cltFHI", coolantTemperature_f.alertHigh);

  preferences.putFloat("iatFLOW", intakeTemperature_f.alertLow);
  preferences.putFloat("iatFHI", intakeTemperature_f.alertHigh);

  preferences.putFloat("ignLOW", ignitionTiming.alertLow);
  preferences.putFloat("ignHI", ignitionTiming.alertHigh);

  preferences.putFloat("aux1FLOW", auxTemp1_f.alertLow);
  preferences.putFloat("aux1FHI", auxTemp1_f.alertHigh);

  preferences.putFloat("aux2FLOW", auxTemp2_f.alertLow);
  preferences.putFloat("aux2FHI", auxTemp2_f.alertHigh);

  preferences.putFloat("mapKPALOW", manifoldPressure.alertLow);
  preferences.putFloat("mapKPAHI", manifoldPressure.alertHigh);

  preferences.putFloat("boostKPALOW", boost_kpa.alertLow);
  preferences.putFloat("boostKPAHI", boost_kpa.alertHigh);

  preferences.putFloat("boostPSILOW", boost_psi.alertLow);
  preferences.putFloat("boostPSIHI", boost_psi.alertHigh);

  preferences.putFloat("oilKPALOW", oilPressure.alertLow);
  preferences.putFloat("oilKPAHI", oilPressure.alertHigh);

  preferences.putFloat("mapPSILOW", manifoldPressure_psi.alertLow);
  preferences.putFloat("mapPSIHI", manifoldPressure_psi.alertHigh);

  preferences.putFloat("oilKPALOW", oilPressure_psi.alertLow);
  preferences.putFloat("oilKPAHI", oilPressure_psi.alertHigh);

  preferences.putFloat("vvtLOW", vvtPosition.alertLow);
  preferences.putFloat("vvtHI", vvtPosition.alertHigh);

  preferences.putFloat("vvtEx1LOW", vvtExhaust1.alertLow);
  preferences.putFloat("vvtEx1HI", vvtExhaust1.alertHigh);

  preferences.putFloat("vvtEx2LOW", vvtExhaust2.alertLow);
  preferences.putFloat("vvtEx2HI", vvtExhaust2.alertHigh);

  preferences.putFloat("vvtIn1LOW", vvtIntake1.alertLow);
  preferences.putFloat("vvtIn1HI", vvtIntake1.alertHigh);

  preferences.putFloat("vvtIn2LOW", vvtIntake2.alertLow);
  preferences.putFloat("vvtIn2HI", vvtIntake2.alertHigh);

  preferences.putFloat("airMassLOW", airMass.alertLow);
  preferences.putFloat("airMassHI", airMass.alertHigh);

  preferences.putFloat("estAirLOW", estimatedAirflow.alertLow);
  preferences.putFloat("estAirHI", estimatedAirflow.alertHigh);

  preferences.putFloat("batVLOW", batteryVoltage.alertLow);
  preferences.putFloat("batVHI", batteryVoltage.alertHigh);

  preferences.putFloat("fpDeltaLOW", fuelPressDelta_kpa.alertLow);
  preferences.putFloat("fpDeltaLOW", fuelPressDelta_kpa.alertHigh);


  preferences.end();
}

void eraseNVS()
{

#ifdef DEBUG_SERIAL
  Serial.println("Erasing NVS!");
#endif

  nvs_flash_deinit();
  nvs_flash_erase(); // erase the NVS partition and...
  nvs_flash_init();  // initialize the NVS partition.
}

void setSensorMinMax(int sensor, int limit, float newValue)
{

  newSensorConfig = selectSensor(sensor);

  switch (limit)
  {
  case 1:
    newSensorConfig->minimum = newValue;
    break;

  case 2:
    newSensorConfig->maximum = newValue;
    break;

  case 3:
    newSensorConfig->alertLow = newValue;
    break;

  case 4:
    newSensorConfig->alertHigh = newValue;
    break;

  case 5:
    newSensorConfig->precision = newValue;
    break;

  default:
    break;
  }
}

void saveLedConfig()
{

  preferences.begin("led", false);
  preferences.putUInt("LEDcolor", LEDcolor);
  preferences.putUInt("LEDstyle", LEDstyle);
  preferences.end();
}

void restoreLedConfig()
{

  preferences.begin("led", false);
  LEDcolor = preferences.getUInt("LEDcolor", LEDcolor);
  LEDstyle = preferences.getUInt("LEDstyle", LEDstyle);
  preferences.end();
}

void restoreWifi()
{

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

void saveWifi()
{

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

void saveBootConfig()
{

  preferences.begin("boot", false);
  preferences.putUInt("bootLogo1", bootLogo1);
  preferences.putUInt("bootLogo2", bootLogo2);
  preferences.putUInt("bootLogo3", bootLogo3);
  preferences.putUInt("pcbRev", pcbRev);
  preferences.putUInt("quickstart", quickstart);
  preferences.putUInt("logoTime_ms", logoTime_ms);
  preferences.putBool("startWifi", startWifi);
  preferences.putBool("startCan", startCan);
  preferences.end();
}

void restoreBootConfig()
{

  preferences.begin("boot", false);
  bootLogo1 = preferences.getUInt("bootLogo1", BMM);
  bootLogo2 = preferences.getUInt("bootLogo2", FOME);
  bootLogo3 = preferences.getUInt("bootLogo3", KAN);
  quickstart = preferences.getUInt("quickstart", 0);
  pcbRev = preferences.getUInt("pcbRev", pcbRev);
  logoTime_ms = preferences.getUInt("logoTime_ms", logoTime_ms);
  startWifi = preferences.getBool("startWifi", startWifi);
  startCan = preferences.getBool("startCan", startCan);
  preferences.end();
}

void checkNvsVer()
{

  //   Check NVS config version and wipe if it is not as expected
  //   Save startup config
  //   This will allow cleaning up stored configs if changes are made to the format

  preferences.begin("startup", false);
  int nvsBuf = preferences.getUInt("nvs", 0);
  restoreBootConfig();
  restoreWifi();
  restoreSensorMinMax();
  preferences.end();

  if (nvsBuf != nvs || nvsBuf == 99 || setToDefaults == true)
  {

    eraseNVS();

    preferences.begin("startup", false);
    preferences.putUInt("nvs", nvs);
    preferences.end();

    // Save default config
    saveBootConfig();
    saveWifi();
    saveSensorMinMax();
    saveSensorAlerts();

    nvsReset = true;
    setToDefaults = false;
  }
}

void saveTextConfig()
{

  preferences.begin("text", false);
  preferences.putUInt("text0", selectedColor[0]);
  preferences.putUInt("text1", selectedColor[1]);
  preferences.putUInt("text2", selectedColor[2]);
  preferences.putUInt("text3", selectedColor[3]);
  preferences.end();
}

void restoreTextConfig()
{

  preferences.begin("text", false);
  selectedColor[0] = preferences.getUInt("text0", selectedColor[0]);
  selectedColor[1] = preferences.getUInt("text1", selectedColor[1]);
  selectedColor[2] = preferences.getUInt("text2", selectedColor[2]);
  selectedColor[3] = preferences.getUInt("text3", selectedColor[3]);

  preferences.end();
}

void saveArcConfig()
{

  preferences.begin("arc", false);
  preferences.putUInt("arcColor1", arcColor1);
  preferences.putUInt("arcColor2", arcColor2);
  preferences.putUInt("arcSeg1", arcSeg1);
  preferences.putUInt("arcSeg2", arcSeg1);
  preferences.putUInt("arcInc1", arcInc1);
  preferences.putUInt("arcInc2", arcInc2);

  preferences.end();
}

void restoreArcConfig()
{

  preferences.begin("arc", false);

  arcColor1 = preferences.getUInt("arcColor1", arcColor1);
  arcColor2 = preferences.getUInt("arcColor2", arcColor2);
  arcSeg1 = preferences.getUInt("arcSeg1", arcSeg1);
  arcSeg2 = preferences.getUInt("arcSeg2", arcSeg2);
  arcInc1 = preferences.getUInt("arcInc1", arcInc1);
  arcInc2 = preferences.getUInt("arcInc2", arcInc2);
  preferences.end();
}
void restoreLedColor()
{

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

void saveNewLedColor(const int index, int red, int green, int blue)
{

  if (red > 255 || red < 0)
  {
    red = 255;
  }

  if (green > 255 || green < 0)
  {
    green = 255;
  }

  if (blue > 255 || blue < 0)
  {
    blue = 255;
  }

  preferences.begin("led", false);

  switch (index)
  {

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

void checkNewConfig()
{

  if (readyToUpdateGaugeConfig == true)
  {

#ifdef DEBUG_SERIAL
    Serial.println("Updating Config");
#endif

    gaugeSensor[selectedGauge] = selectedSensor;

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

    for (int p = 0; (p < numDataPtr); p++)
    {
      ptrData[p] = selectSensor(gaugeSensor[p]);
    }

    saveSensorSetting();
    restoreSensorSetting();
    saveBrightnessSettings();
    saveGaugeType();
    
    readyToUpdateGaugeConfig = false;
    resetDisplay = true;
  }

  if (readyToUpdateLimits == true)
  {
    setSensorMinMax(selectedSensor, selectedLimit, inputNewValue);
    saveSensorMinMax();
    saveSensorAlerts();


    readyToUpdateLimits = false;
  }

  if (updateWifiConfig == true)
  {
    saveWifi();
    updateWifiConfig = false;
  }

  if (updateArcConfig == true)
  {
    saveArcConfig();
    updateArcConfig = false;
  }

  if (updateGaugeType == true)
  {
    saveGaugeType();
    updateGaugeType = false;
  }
}
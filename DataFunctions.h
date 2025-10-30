//==============================================
/*
   
   'dataFunctions.h'

   This takes the recieved CAN messages and processes them based on defined scaling factors and offsets,
    then stores them inside the data structs.

*/
//==============================================
#pragma once

#include "wifi.h"
#include "display.h"
#include "pinMap.h"
#include "SensorData.h"
#include "config.h"
#include "led.h"
#include "nvs.h"

// Configure how test data increments
int lastTestIncrement = 0;
int testTime = 25;
float testIncrementValue = 1.01;
int warningLimit = 1;

bool INC = true;
bool ALERT = false;

int mpgCount = 1;
int mpgTimer = 500;
int lastMpgTime = 0;
int mpgTimeDelay = 60000;

// ========================================================== Functions =========================================================================

void incrementTestData() {
  // Increment test data

  if ((lastTestIncrement + testTime) < millis()) {
    lastTestIncrement = millis();

    if (INC == true) {
      testData.scaledValue = testData.scaledValue + testIncrementValue;
    }

    else {
      testData.scaledValue = testData.scaledValue - testIncrementValue;
    }

    if (testData.scaledValue > 110) {
      INC = false;
    }

    if (testData.scaledValue < -110) {
      INC = true;
    }

#ifdef DEBUG_SERIAL
//    Serial.print("Incremented Test data : ");
//    Serial.println(testData.scaledValue);
#endif
  }
}

void checkAlert() {

  if (warningCounter > warningLimit || checkEngine > 0) {
    ALERT = TRUE;
  } else {
    ALERT = FALSE;
  }
}

bool sensorAlertCheck(float min, float max, float val) {

  if (val < min) {
    return true;
  }

  if (val > max) {
    return true;
  }

  return false;
}

void getMPG() {

  // Consumption in g/s
  // 1Gal = 2754 g
  // g/s -> Gal / Hr
  // MPH / (Gal / Hr) -> MPG

  if (millis() < mpgTimeDelay) {
    return;
  }

  if (mpgCount < 1) {
    mpgCount = 1;
  }

  if (millis() - lastMpgTime > mpgTimer) {

    // If no fuel is being used set MPG
    if (fuelConsumption.scaledValue > 0) {
      mpgShort.scaledValue = vss_mph.scaledValue / (fuelConsumption.scaledValue * 3600 / 2754);
    } else {
      mpgShort.scaledValue = 99;
    }

    // Set some limits on MPG
    if (mpgShort.scaledValue < 0) { mpgShort.scaledValue = 0; }
    if (mpgShort.scaledValue > 99) { mpgShort.scaledValue = 99; }

    // Calculate long term MPG for trip
    mpgLong.scaledValue = (mpgLong.scaledValue * (mpgCount - 1) / mpgCount) + (mpgShort.scaledValue / mpgCount);
    mpgCount++;
    lastMpgTime = millis();
  }
}

void SAVE_CAN_DATA(twai_message_t CANmsg) {

  // Check the ID of the recieved CAN message, scale and store the sensor values
  // Some data is sent in two bytes and is combined into a word before scaling

  // FOME CAN
  if (CANmsg.identifier == (canBaseID_FOME)) {
    warningCounter = ((int)word(CANmsg.data[1], CANmsg.data[0]));
    lastError = ((int)word(CANmsg.data[3], CANmsg.data[2]));
    revLimit = ((int)CANmsg.data[4]) & 0x01;
    mainRelay = ((int)CANmsg.data[4]) & 0x02;
    fuelPump = ((int)CANmsg.data[4]) & 0x04;
    checkEngine = ((int)CANmsg.data[4]) & 0x08;
    egoHeater = ((int)CANmsg.data[4]) & 0x10;
    gear.scaledValue = ((int)CANmsg.data[5]);
  }

  if (CANmsg.identifier == (canBaseID_FOME + 1)) {
    rpm.scaledValue = ((((int)word(CANmsg.data[1], CANmsg.data[0])) * (rpm.scaleMultiplier)) + rpm.offset);
    ignitionTiming.scaledValue = ((((short)word(CANmsg.data[3], CANmsg.data[2])) * (ignitionTiming.scaleMultiplier)) + ignitionTiming.offset);
    injectorDuty.scaledValue = ((((float)(CANmsg.data[4])) * (injectorDuty.scaleMultiplier)) + injectorDuty.offset);

    vss.scaledValue = ((((float)(CANmsg.data[6])) * (vss.scaleMultiplier)) + vss.offset);
    vss_mph.scaledValue = ((((float)(CANmsg.data[6])) * (vss_mph.scaleMultiplier)) + vss_mph.offset);
    ethanol.scaledValue = ((((float)(CANmsg.data[7])) * (ethanol.scaleMultiplier)) + ethanol.offset);
  }

  if (CANmsg.identifier == (canBaseID_FOME + 2)) {
    accelerator.scaledValue = ((((short)word(CANmsg.data[1], CANmsg.data[0])) * (accelerator.scaleMultiplier)) + accelerator.offset);
    throttle1.scaledValue = ((((short)word(CANmsg.data[3], CANmsg.data[2])) * (throttle1.scaleMultiplier)) + throttle1.offset);
    throttle2.scaledValue = ((((short)word(CANmsg.data[5], CANmsg.data[4])) * (throttle2.scaleMultiplier)) + throttle2.offset);
    wastegate.scaledValue = ((((short)word(CANmsg.data[7], CANmsg.data[6])) * (wastegate.scaleMultiplier)) + wastegate.offset);
  }

  if (CANmsg.identifier == (canBaseID_FOME + 3)) {

    manifoldPressure.scaledValue = ((((float)word(CANmsg.data[1], CANmsg.data[0])) * (manifoldPressure.scaleMultiplier)) + manifoldPressure.offset);
    boost_kpa.scaledValue = manifoldPressure.scaledValue + boost_kpa.offset;
    manifoldPressure_psi.scaledValue = ((((float)word(CANmsg.data[1], CANmsg.data[0])) * (manifoldPressure_psi.scaleMultiplier)) + manifoldPressure_psi.offset);
    boost_psi.scaledValue = manifoldPressure_psi.scaledValue + boost_psi.offset;

    fuelPressDelta_kpa.scaledValue = fuelPressureLow.scaledValue - manifoldPressure.scaledValue;
    //fuelPressDelta_psi.scaledValue = fuelPressureLow_psi.scaledValue - manifoldPressure_psi.scaledValue;

    coolantTemperature.scaledValue = ((((float)(CANmsg.data[2])) * (coolantTemperature.scaleMultiplier)) + coolantTemperature.offset);
    coolantTemperature_f.scaledValue = ((coolantTemperature.scaledValue * (coolantTemperature_f.scaleMultiplier)) + coolantTemperature_f.offset);
    intakeTemperature.scaledValue = ((((float)(CANmsg.data[3])) * (intakeTemperature.scaleMultiplier)) + intakeTemperature.offset);
    intakeTemperature_f.scaledValue = ((intakeTemperature.scaledValue * intakeTemperature_f.scaleMultiplier) + intakeTemperature_f.offset);

    auxTemp1.scaledValue = ((((float)(CANmsg.data[4])) * (auxTemp1.scaleMultiplier)) + auxTemp1.offset);
    auxTemp2.scaledValue = ((((float)(CANmsg.data[5])) * (auxTemp2.scaleMultiplier)) + auxTemp2.offset);
    auxTemp1_f.scaledValue = ((auxTemp1.scaledValue * auxTemp1_f.scaleMultiplier) + auxTemp1_f.offset);
    auxTemp2_f.scaledValue = ((auxTemp2.scaledValue * auxTemp2_f.scaleMultiplier) + auxTemp2_f.offset);

    mcuTemp.scaledValue = ((((float)(CANmsg.data[6])) * (mcuTemp.scaleMultiplier)) + mcuTemp.offset);
    fuel.scaledValue = ((((float)(CANmsg.data[7])) * (fuel.scaleMultiplier)) + fuel.offset);
  }

  if (CANmsg.identifier == (canBaseID_FOME + 4)) {
    //afr.scaledValue = ((((float)word(CANmsg.data[1], CANmsg.data[0])) * (afr.scaleMultiplier)) + afr.offset);
    oilPressure_psi.scaledValue = ((((float)word(CANmsg.data[3], CANmsg.data[2])) * (oilPressure_psi.scaleMultiplier)) + oilPressure_psi.offset);
    oilPressure.scaledValue = ((((float)word(CANmsg.data[3], CANmsg.data[2])) * (oilPressure.scaleMultiplier)) + oilPressure.offset);

    oilTemperature.scaledValue = (((float)(CANmsg.data[4]) * (oilTemperature.scaleMultiplier)) + oilTemperature.offset);
    oilTemperature_f.scaledValue = ((oilTemperature.scaledValue * (oilTemperature_f.scaleMultiplier)) + oilTemperature_f.offset);

    fuelTemperature.scaledValue = (((float)(CANmsg.data[5]) * (fuelTemperature.scaleMultiplier)) + fuelTemperature.offset);
    fuelTemperature_f.scaledValue = ((fuelTemperature.scaledValue * fuelTemperature_f.scaleMultiplier) + fuelTemperature_f.offset);

    //vvtPosition.scaledValue = ((((float)word(CANmsg.data[5], CANmsg.data[4])) * (vvtPosition.scaleMultiplier)) + vvtPosition.offset);
    batteryVoltage.scaledValue = ((((float)word(CANmsg.data[7], CANmsg.data[6])) * (batteryVoltage.scaleMultiplier)) + batteryVoltage.offset);
  }

  if (CANmsg.identifier == (canBaseID_FOME + 5)) {
    airMass.scaledValue = ((((float)word(CANmsg.data[1], CANmsg.data[0])) * (airMass.scaleMultiplier)) + airMass.offset);
    estimatedAirflow.scaledValue = ((((float)word(CANmsg.data[3], CANmsg.data[2])) * (estimatedAirflow.scaleMultiplier)) + estimatedAirflow.offset);
    injectorPulse.scaledValue = ((((float)word(CANmsg.data[5], CANmsg.data[4])) * (injectorPulse.scaleMultiplier)) + injectorPulse.offset);
  }

  if (CANmsg.identifier == (canBaseID_FOME + 6)) {
    fuelConsumed.scaledValue = ((((float)word(CANmsg.data[1], CANmsg.data[0])) * (fuelConsumed.scaleMultiplier)) + fuelConsumed.offset);
    fuelConsumption.scaledValue = ((((float)word(CANmsg.data[3], CANmsg.data[2])) * (fuelConsumption.scaleMultiplier)) + fuelConsumption.offset);
    fuelTrim.scaledValue = ((((short)word(CANmsg.data[5], CANmsg.data[4])) * (fuelTrim.scaleMultiplier)) + fuelTrim.offset);
  }

  if (CANmsg.identifier == (canBaseID_FOME + 7)) {
    lambda1.scaledValue = ((((float)word(CANmsg.data[1], CANmsg.data[0])) * (lambda1.scaleMultiplier)) + lambda1.offset);
    lambda2.scaledValue = ((((float)word(CANmsg.data[3], CANmsg.data[2])) * (lambda2.scaleMultiplier)) + lambda2.offset);
    afr.scaledValue = lambda1.scaledValue * STOICH_RATIO;

    fuelPressureLow.scaledValue = ((((float)word(CANmsg.data[5], CANmsg.data[4])) * (fuelPressureLow.scaleMultiplier)) + fuelPressureLow.offset);
    fuelPressureHigh.scaledValue = ((((float)word(CANmsg.data[7], CANmsg.data[6])) * (fuelPressureHigh.scaleMultiplier)) + fuelPressureHigh.offset);
  }

  if (CANmsg.identifier == (canBaseID_FOME + 8)) {
    vvtIntake1.scaledValue = (float)CANmsg.data[0] * vvtIntake1.scaleMultiplier + vvtIntake1.offset;
    vvtIntake2.scaledValue = (float)CANmsg.data[4] * vvtIntake2.scaleMultiplier + vvtIntake2.offset;
    vvtExhaust1.scaledValue = (float)CANmsg.data[2] * vvtExhaust1.scaleMultiplier + vvtExhaust1.offset;
    vvtExhaust2.scaledValue = (float)CANmsg.data[6] * vvtExhaust2.scaleMultiplier + vvtExhaust2.offset;
  }

  canBaseID_MS = canBaseID_FOME + 1000;

  if (CANmsg.identifier == (canBaseID_MS)) {
    manifoldPressure.scaledValue = (((float)word(CANmsg.data[0], CANmsg.data[1])) / 10);
    boost_kpa.scaledValue = manifoldPressure.scaledValue + boost_kpa.offset;

    manifoldPressure_psi.scaledValue = ((manifoldPressure.scaledValue) * (0.1450377377));
    boost_psi.scaledValue = manifoldPressure_psi.scaledValue + boost_psi.offset;

    rpm.scaledValue = (((int)word(CANmsg.data[2], CANmsg.data[3])));

    coolantTemperature_f.scaledValue = ((((int)word(CANmsg.data[4], CANmsg.data[5])) / 10));
    coolantTemperature.scaledValue = (coolantTemperature_f.scaledValue - 32) / 1.8;

    throttle1.scaledValue = ((((short)word(CANmsg.data[6], CANmsg.data[7])) / 10));
  }

  if (CANmsg.identifier == (canBaseID_MS + 1)) {
    // PW1
    injectorPulse.scaledValue = (((float)word(CANmsg.data[0], CANmsg.data[1])) / 1000);
    // mat
    intakeTemperature_f.scaledValue = ((float)word((CANmsg.data[4]), (CANmsg.data[5]))) / 10;
    intakeTemperature.scaledValue = (intakeTemperature_f.scaledValue - 32) / 1.8;
    // adv_deg
    ignitionTiming.scaledValue = ((float)word(CANmsg.data[6], CANmsg.data[7])) / 10;
  }

  if (CANmsg.identifier == (canBaseID_MS + 2)) {
    // b1 afr target
    // AFR1
    afr.scaledValue = (((float)(CANmsg.data[1]) / 10));
    // EGO corr 1
    fuelTrim.scaledValue = (((float)word(CANmsg.data[2], CANmsg.data[3])) / 10);
    // EGT 1
    // pwseq1
  }

  if (CANmsg.identifier == (canBaseID_MS + 3)) {
    // Battery
    batteryVoltage.scaledValue = (((float)word(CANmsg.data[0], CANmsg.data[1])) / 10);
    // Sensor 1
    auxTemp1.scaledValue = (((float)word(CANmsg.data[2], CANmsg.data[3])) / 100);
    // Sensor 2
    auxTemp2.scaledValue = (((float)word(CANmsg.data[4], CANmsg.data[5])) / 100);
    // knock retard
  }

  if (CANmsg.identifier == (canBaseID_MS + 4)) {
    // Vss 1
    vss.scaledValue = ((((float)word(CANmsg.data[0], CANmsg.data[1])) * 3.6) / 10);
    vss_mph.scaledValue = vss.scaledValue * vss_mph.scaleMultiplier;
    // tc_rtd
    // Launch time
  }


  // LINK

  if (CANmsg.identifier == canBaseID_LINK) {

    if (CANmsg.data[0] == 0) {
      // Handle ID 0
      rpm.scaledValue = ((int)word(CANmsg.data[3], CANmsg.data[2]));
      manifoldPressure.scaledValue = ((float)word(CANmsg.data[5], CANmsg.data[4]));

    } else if (CANmsg.data[0] == 1) {
      // Handle ID 1
      throttle1.scaledValue = (((short)word(CANmsg.data[5], CANmsg.data[4])) / 10);
      injectorDuty.scaledValue = (((short)word(CANmsg.data[7], CANmsg.data[6])) / 10);

    } else if (CANmsg.data[0] == 2) {
      // Handle ID 2

    } else if (CANmsg.data[0] == 3) {
      // Handle ID 3
      intakeTemperature.scaledValue = ((float)word(CANmsg.data[3], CANmsg.data[2])) - 50;
      intakeTemperature_f.scaledValue = (intakeTemperature.scaledValue * 1.8) + 32;
      batteryVoltage.scaledValue = (((float)word(CANmsg.data[5], CANmsg.data[4])) / 100);


    } else if (CANmsg.data[0] == 4) {
      // Handle ID 4

    } else if (CANmsg.data[0] == 5) {
      // Handle ID 5

    } else if (CANmsg.data[0] == 6) {
      // Handle ID 6
      lambda1.scaledValue = (((float)word(CANmsg.data[5], CANmsg.data[4])) / 1000);
      lambda2.scaledValue = (((float)word(CANmsg.data[7], CANmsg.data[6])) / 1000);

    } else if (CANmsg.data[0] == 7) {
      // Handle ID 7

    } else if (CANmsg.data[0] == 8) {
      // Handle ID 8
      oilPressure.scaledValue = ((float)word(CANmsg.data[5], CANmsg.data[4]));
      oilTemperature.scaledValue = ((float)word(CANmsg.data[3], CANmsg.data[2]));
      oilTemperature_f.scaledValue = (oilTemperature.scaledValue * 1.8) + 32;

    } else if (CANmsg.data[0] == 9) {
      // Handle ID 9
    }
  }
}

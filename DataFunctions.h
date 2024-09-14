/*
   'dataFunctions.h'

   This takes the recieved CAN messages and processes them based on defined scaling factors and offsets,
    then stores them inside the data structs.

*/
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

// ========================================================== Functions =========================================================================

float rollOverAdjust(float t, float scale, int b)
{

  switch (b)
  {

  case 16:

    if (t > (65535 / 2 * scale))
    {
      t = t - (65535 * scale);
    }

    break;

  default:
    break;
  }

  return t;
}

void incrementTestData()
{
  // Increment test data

  if ((lastTestIncrement + testTime) < millis())
  {
    lastTestIncrement = millis();

    if (INC == true)
    {
      testData.scaledValue = testData.scaledValue + testIncrementValue;
    }

    else
    {
      testData.scaledValue = testData.scaledValue - testIncrementValue;
    }

    if (testData.scaledValue > 110)
    {
      INC = false;
    }

    if (testData.scaledValue < -110)
    {
      INC = true;
    }

#ifdef DEBUG_SERIAL
//    Serial.print("Incremented Test data : ");
//    Serial.println(testData.scaledValue);
#endif
  }
}

void checkAlert()
{

  if (warningCounter > warningLimit || checkEngine > 0)
  {
    ALERT = TRUE;
  }
  else
  {
    ALERT = FALSE;
  }
}

bool sensorAlertCheck(float min, float max, float val) 
{

  if (val < min)
  {
    return true;
  }

  if (val > max)
  {
    return true;
  }

  return false;
}

void SAVE_CAN_DATA(twai_message_t CANmsg)
{

  // Check the ID of the recieved CAN message, scale and store the sensor values
  // Some data is sent in two bytes and is combined into a word before scaling

  switch (CANmsg.identifier)
  {

    // FOME CAN

  case (512):
    warningCounter = ((int)word(CANmsg.data[1], CANmsg.data[0]));
    lastError = ((int)word(CANmsg.data[3], CANmsg.data[2]));
    revLimit = ((int)CANmsg.data[4]) & 0x01;
    mainRelay = ((int)CANmsg.data[4]) & 0x02;
    fuelPump = ((int)CANmsg.data[4]) & 0x04;
    checkEngine = ((int)CANmsg.data[4]) & 0x08;
    egoHeater = ((int)CANmsg.data[4]) & 0x10;
    gear.scaledValue = ((int)CANmsg.data[5]);
    break;

  case (513):
    rpm.scaledValue = ((((int)word(CANmsg.data[1], CANmsg.data[0])) * (rpm.scaleMultiplier)) + rpm.offset);
    ignitionTiming.scaledValue = ((((float)word(CANmsg.data[3], CANmsg.data[2])) * (ignitionTiming.scaleMultiplier)) + ignitionTiming.offset);
    injectorDuty.scaledValue = ((((float)word(CANmsg.data[5], CANmsg.data[4])) * (injectorDuty.scaleMultiplier)) + injectorDuty.offset);
    vss.scaledValue = ((((float)(CANmsg.data[6])) * (vss.scaleMultiplier)) + vss.offset);
    vss_mph.scaledValue = ((((float)(CANmsg.data[6])) * (vss_mph.scaleMultiplier)) + vss_mph.offset);
    ethanol.scaledValue = ((((float)(CANmsg.data[7])) * (ethanol.scaleMultiplier)) + ethanol.offset);

    break;

  case (514):
    accelerator.scaledValue = ((((int)word(CANmsg.data[1], CANmsg.data[0])) * (accelerator.scaleMultiplier)) + accelerator.offset);
    throttle1.scaledValue = ((((int)word(CANmsg.data[3], CANmsg.data[2])) * (throttle1.scaleMultiplier)) + throttle1.offset);
    throttle2.scaledValue = ((((int)word(CANmsg.data[5], CANmsg.data[4])) * (throttle2.scaleMultiplier)) + throttle2.offset);
    wastegate.scaledValue = ((((int)word(CANmsg.data[7], CANmsg.data[6])) * (wastegate.scaleMultiplier)) + wastegate.offset);

    // If a negative/large value is calculated
    accelerator.scaledValue = rollOverAdjust(accelerator.scaledValue, accelerator.scaleMultiplier, 16);
    throttle1.scaledValue = rollOverAdjust(throttle1.scaledValue, throttle1.scaleMultiplier, 16);
    throttle2.scaledValue = rollOverAdjust(throttle2.scaledValue, throttle2.scaleMultiplier, 16);
    wastegate.scaledValue = rollOverAdjust(wastegate.scaledValue, wastegate.scaleMultiplier, 16);

    break;

  case (515):

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
    break;

  case (516):
    //afr.scaledValue = ((((float)word(CANmsg.data[1], CANmsg.data[0])) * (afr.scaleMultiplier)) + afr.offset);
    oilPressure_psi.scaledValue = ((((float)word(CANmsg.data[3], CANmsg.data[2])) * (oilPressure_psi.scaleMultiplier)) + oilPressure_psi.offset);
    oilPressure.scaledValue = ((((float)word(CANmsg.data[3], CANmsg.data[2])) * (oilPressure.scaleMultiplier)) + oilPressure.offset);

    oilTemperature.scaledValue = (((float)(CANmsg.data[4]) * (oilTemperature.scaleMultiplier)) + oilTemperature.offset);
    oilTemperature_f.scaledValue = ((oilTemperature.scaledValue * (oilTemperature_f.scaleMultiplier)) + oilTemperature_f.offset);

    vvtPosition.scaledValue = ((((float)word(CANmsg.data[5], CANmsg.data[4])) * (vvtPosition.scaleMultiplier)) + vvtPosition.offset);
    batteryVoltage.scaledValue = ((((float)word(CANmsg.data[7], CANmsg.data[6])) * (batteryVoltage.scaleMultiplier)) + batteryVoltage.offset);
    break;

  case (517):
    airMass.scaledValue = ((((float)word(CANmsg.data[1], CANmsg.data[0])) * (airMass.scaleMultiplier)) + airMass.offset);
    estimatedAirflow.scaledValue = ((((float)word(CANmsg.data[3], CANmsg.data[2])) * (estimatedAirflow.scaleMultiplier)) + estimatedAirflow.offset);
    injectorPulse.scaledValue = ((((float)word(CANmsg.data[5], CANmsg.data[4])) * (injectorPulse.scaleMultiplier)) + injectorPulse.offset);
    break;

  case (518):
    fuelConsumed.scaledValue = ((((float)word(CANmsg.data[1], CANmsg.data[0])) * (fuelConsumed.scaleMultiplier)) + fuelConsumed.offset);
    fuelConsumption.scaledValue = ((((float)word(CANmsg.data[3], CANmsg.data[2])) * (fuelConsumption.scaleMultiplier)) + fuelConsumption.offset);
    fuelTrim.scaledValue = ((((float)word(CANmsg.data[5], CANmsg.data[4])) * (fuelTrim.scaleMultiplier)) + fuelTrim.offset);
    fuelTrim.scaledValue = rollOverAdjust(fuelTrim.scaledValue, fuelTrim.scaleMultiplier, 16);

    break;

  case (519):
    lambda1.scaledValue = ((((float)word(CANmsg.data[1], CANmsg.data[0])) * (lambda1.scaleMultiplier)) + lambda1.offset);
    lambda2.scaledValue = ((((float)word(CANmsg.data[3], CANmsg.data[2])) * (lambda2.scaleMultiplier)) + lambda2.offset);
    afr.scaledValue = lambda1.scaledValue * STOICH_RATIO;

    fuelPressureLow.scaledValue = ((((float)word(CANmsg.data[5], CANmsg.data[4])) * (fuelPressureLow.scaleMultiplier)) + fuelPressureLow.offset);
    fuelPressureHigh.scaledValue = ((((float)word(CANmsg.data[7], CANmsg.data[6])) * (fuelPressureHigh.scaleMultiplier)) + fuelPressureHigh.offset);

    break;

  case (520):
    vvtIntake1.scaledValue = (float) CANmsg.data[0] * vvtIntake1.scaleMultiplier + vvtIntake1.offset;
    vvtIntake2.scaledValue = (float) CANmsg.data[4] * vvtIntake2.scaleMultiplier + vvtIntake2.offset;
    vvtExhaust1.scaledValue = (float) CANmsg.data[2] * vvtExhaust1.scaleMultiplier + vvtExhaust1.offset;
    vvtExhaust2.scaledValue = (float) CANmsg.data[6] * vvtExhaust2.scaleMultiplier + vvtExhaust2.offset;
    break;

    // MS CAN
  case (1512):

    manifoldPressure.scaledValue = (((float)word(CANmsg.data[1], CANmsg.data[0])) / 10);
    rpm.scaledValue = (((int)word(CANmsg.data[3], CANmsg.data[2])));

    // Add scale to temp C only F in broadcast
    coolantTemperature_f.scaledValue = ((((int)word(CANmsg.data[5], CANmsg.data[4])) / 10));
    throttle1.scaledValue = ((((int)word(CANmsg.data[7], CANmsg.data[6])) / 10));
    break;

  case (1513):
    // PW1
    injectorPulse.scaledValue = (((float)word(CANmsg.data[1], CANmsg.data[0])) / 1000);
    // PW2
    // injectorPulse2.scaledValue = ((((float)word(CANmsg.data[3], CANmsg.data[2])) / 1000;
    // mat
    intakeTemperature_f.scaledValue = ((float)word((CANmsg.data[5]), (CANmsg.data[4]))) / 10;
    // adv_deg
    ignitionTiming.scaledValue = ((float)word(CANmsg.data[7], CANmsg.data[6])) / 10;
    break;

  case (1514):
    // b1 afr target
    // AFR1
    afr.scaledValue = (((float)(CANmsg.data[1]) / 10));
    // EGO corr 1
    fuelTrim.scaledValue = (((float)word(CANmsg.data[3], CANmsg.data[2])) / 10);
    // EGT 1
    // pwseq1
    break;

  case (1515):
    // Battery
    batteryVoltage.scaledValue = (((float)word(CANmsg.data[1], CANmsg.data[0])) / 10);
    // Sensor 1
    // Sensor 2
    // knock retard
    break;

  case (1516):
    // Vss 1
    vss.scaledValue = (((float)word(CANmsg.data[1], CANmsg.data[0])) / 10);
    // tc_rtd
    // Launch time
    break;
  }
}

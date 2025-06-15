//==============================================
/*
  
  'can.h'

 
 */
//==============================================

#pragma once
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
#include "pid.h"

twai_message_t CANMessage;
TaskHandle_t TASK_CAN;

/*
Setup CAN in Normal mode using GPIO defined in pinMap
Speed: 500k
No Filters
*/

void canSetup() {

  twai_general_config_t g_config = TWAI_GENERAL_CONFIG_DEFAULT((gpio_num_t)CAN_TX, (gpio_num_t)CAN_RX, TWAI_MODE_NORMAL);
  // twai_general_config_t g_config = TWAI_GENERAL_CONFIG_DEFAULT((gpio_num_t)CAN_TX, (gpio_num_t)CAN_RX, TWAI_MODE_LISTEN_ONLY);
  twai_timing_config_t t_config = TWAI_TIMING_CONFIG_500KBITS();
  twai_filter_config_t f_config = TWAI_FILTER_CONFIG_ACCEPT_ALL();

  // Install TWAI driver
  if (twai_driver_install(&g_config, &t_config, &f_config) == ESP_OK) {
#ifdef DEBUG_SERIAL
    Serial.println("Driver installed");
#endif
  } else {
#ifdef DEBUG_SERIAL
    Serial.println("Failed to install driver");
#endif

    return;
  }

  // Start TWAI driver
  if (twai_start() == ESP_OK) {
    canEnabled = true;
#ifdef DEBUG_SERIAL
    Serial.println("Driver started");
#endif
  } else {
#ifdef DEBUG_SERIAL
    Serial.println("Failed to start driver");
#endif

    return;
  }
}

/*
When a CAN message is recieved, pass it to be processed and values saved
*/

void obdRequest(int requestedPID) {

  // Send message
  // Configure message to transmit
  twai_message_t message;
  //message.identifier = 0x0F6;
  message.identifier = 0x7DF;
  message.data_length_code = 8;
  message.data[0] = 02;
  message.data[1] = 01;
  message.data[2] = requestedPID;
  message.data[3] = 55;
  message.data[4] = 55;
  message.data[5] = 55;
  message.data[6] = 55;
  message.data[7] = 55;

  // Queue message for transmission
  if (twai_transmit(&message, pdMS_TO_TICKS(100)) == ESP_OK) {
    printf("Message queued for transmission\n");
  } else {
    printf("Failed to queue message for transmission\n");
  }
}

void obdReceive() {
  if (CANMessage.identifier == 0x7E8) {
    switch (CANMessage.data[2]) {

      case ENGINE_COOLANT_TEMP:
        coolantTemperature.scaledValue = (CANMessage.data[3] - 40);
        coolantTemperature_f.scaledValue = ((coolantTemperature.scaledValue * (coolantTemperature_f.scaleMultiplier)) + coolantTemperature_f.offset);
        break;

      case INTAKE_AIR_TEMP:
        intakeTemperature.scaledValue = (CANMessage.data[3] - 40);
        intakeTemperature_f.scaledValue = (intakeTemperature.scaledValue * 1.8) + 32;
        break;

      case ENGINE_RPM:
        rpm.scaledValue = ((256 * CANMessage.data[3] + CANMessage.data[4]) / 4);
        break;

      case OXYGEN_SENSOR_1_B:
        lambda1.scaledValue = (word(CANMessage.data[3], CANMessage.data[4]) * 2 / 65536);
        break;

      case ENGINE_OIL_TEMP:
        oilTemperature.scaledValue = (CANMessage.data[3] - 40);
        oilTemperature_f.scaledValue = ((oilTemperature.scaledValue * (oilTemperature_f.scaleMultiplier)) + oilTemperature_f.offset);
        break;

      case INTAKE_MANIFOLD_ABS_PRESSURE:
        manifoldPressure.scaledValue = CANMessage.data[3];
        manifoldPressure_psi.scaledValue = manifoldPressure.scaledValue * 0.1450377;
        boost_kpa.scaledValue = manifoldPressure.scaledValue - baroPressure.scaledValue;
        boost_psi.scaledValue = boost_kpa.scaledValue * 0.1450377;
        break;

      case ABS_BAROMETRIC_PRESSURE:
        baroPressure.scaledValue = CANMessage.data[3];
        boost_kpa.scaledValue = manifoldPressure.scaledValue - baroPressure.scaledValue;
        boost_psi.scaledValue = boost_kpa.scaledValue * 0.1450377;
        break;

      case AIR_TEMPERATURE_SENSOR:
        intakeTemperature.scaledValue = (CANMessage.data[4] - 40);
        intakeTemperature_f.scaledValue = (intakeTemperature.scaledValue * 1.8) + 32;
        break;
    }
  }
}

void canReceive() {

  if (twai_receive(&CANMessage, 0) == ESP_OK) {

    if (printCan == true) {
      Serial.print("0x");
      // id = CANMessage.identifier;
      Serial.print(CANMessage.identifier, HEX);
      Serial.print("\t");
      Serial.print(CANMessage.extd);
      Serial.print("\t");
      Serial.print(CANMessage.rtr);
      Serial.print("\t");
      Serial.print(CANMessage.data_length_code);
      for (int i = 0; i < CANMessage.data_length_code; i++) {
        Serial.print("\t0x");
        if (CANMessage.data[i] <= 0x0F) {
          Serial.print(0);
        }
        Serial.print(CANMessage.data[i], HEX);
      }
      Serial.println();
    }

    SAVE_CAN_DATA(CANMessage);
  }
}

void canReceiveTask(void *pvParameters) {

#ifdef DEBUG_SERIAL
  Serial.print("CAN Task on core: ");
  Serial.println(xPortGetCoreID());
#endif
  int currentPID = 0;

  for (;;) {

    if (dataRequestOBD == true) {
      obdRequest(selectedPIDs[currentPID]);
      currentPID++;
      if (currentPID > 5) { currentPID = 0; }
    }

    canReceive();
    obdReceive();
  }
}
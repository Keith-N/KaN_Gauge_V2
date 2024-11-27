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

  for (;;) {
    canReceive();
  }
}
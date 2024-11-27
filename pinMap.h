//==============================================
/*
  
  'pinmap.h'



*/
//==============================================

#pragma once

#define CAN_RX 8
#define CAN_TX 18

#define USER_INPUT_A1 17
#define USER_INPUT_A2 9

#define USER_INPUT_D1 48
#define USER_INPUT_D2 47

#define R24 5
#define R25 4
#define R26 2
#define R27 1

#define LED_1 21
#define LED_2 14


void setupPinMode() {
  pinMode(USER_INPUT_D1, INPUT_PULLUP);
  pinMode(USER_INPUT_D2, INPUT_PULLUP);
  pinMode(USER_INPUT_A1, INPUT);
  pinMode(USER_INPUT_A2, INPUT);
}


String checkResistorConfig() {
  pinMode(R24, INPUT_PULLUP);
  pinMode(R25, INPUT_PULLUP);
  pinMode(R26, INPUT_PULLUP);
  pinMode(R27, INPUT_PULLUP);

  /* 
  Shift and OR each pull-down resistor 
  0 = populated, 1 = not populated
  binary values will range from 0000 (all populated) to 1111 (none populated)
  |R27|R26|R25|R24|
  */

  int ResConfig = 0;
  ResConfig |= (bool) analogRead(R24) << 0;
  ResConfig |= (bool) analogRead(R25) << 1;
  ResConfig |= (bool) analogRead(R26) << 2;
  ResConfig |= (bool) analogRead(R27) << 3;


#ifdef DEBUG_SERIAL
  Serial.print("Resistors = ");
  Serial.println(ResConfig, BIN);
  Serial.println(ResConfig);
#endif

  // Choose board Revision based on resistor configuration
  String Rev = "";
  switch(ResConfig){

    case (0):
    Rev = "1.4";
    break;

    case(12):
    //1.2 and 1.3 are equivalent
    Rev = "1.3";
    break;

    default:
    Rev = "0";
    break;
  }

  // Returns hardware revision
  return Rev;
}

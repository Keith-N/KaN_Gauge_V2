//==============================================
/*

  config.h


*/
//==============================================
//==============================================
//  Define / Config
//==============================================
 
#pragma once

int bootConfig;
const String build = "0.48";
const int nvs = 4;
const String buildType = "";

// Software version and build note will displayed as entered
String softwareVersion = "0.48";
String buildNote = "";

// Hardware configuration should be updated based on populated resistors
// use "hardwareConfig = checkResistorConfig();" during setup to do so
String hardwareConfig = "";


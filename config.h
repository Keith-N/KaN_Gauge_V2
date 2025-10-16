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
const String build = "0.54";
const int nvs = 5;
const String buildType = "Link Test";

// Software version and build note will displayed as entered
String softwareVersion = build;
String buildNote = buildType;

// Hardware configuration should be updated based on populated resistors
// use "hardwareConfig = checkResistorConfig();" during setup to do so
String hardwareConfig = "";


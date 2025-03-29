//==============================================
/*

  'sensorData.h'

  Contains unique IDs for sensor identification, formatting, and calculation

*/
//==============================================
#pragma once

// Assigned unique IDs for all sensor data
#define AFR 0
#define RPM 1
#define SPEED_KPH 2
#define SPEED_MPH 3
#define MANIFOLD_PRESS_KPA 4
#define MANIFOLD_PRESS_PSI 5
#define COOLANT_TEMP_C 6
#define COOLANT_TEMP_F 7
#define INTAKE_TEMP_C 8
#define INTAKE_TEMP_F 9
#define ACCELERATOR 10
#define IGNITION_TIMING 11
#define INJECTOR_DUTY 12
#define INJECTOR_PULSE 13
#define THROTTLE_POSITION_1 14
#define THROTTLE_POSITION_2 15
#define VALVE_TIMING 16
#define AIR_MASS 17
#define ESTIMATED_AIRFLOW 18
#define FUEL 19
#define MCU_C 20
#define AUX_TEMP_1_C 21
#define AUX_TEMP_1_F 22
#define AUX_TEMP_2_C 23
#define AUX_TEMP_2_F 24
#define BATTERY_VOLTAGE 25
#define ETHANOL 26
#define LAMBDA_1 27
#define LAMBDA_2 28
#define FUEL_PRESS_LO 29
#define FUEL_PRESS_HI 30
#define FUEL_CONSUMED 31
#define FUEL_RATE 32
#define FUEL_TRIM 33
#define INTAKE_VALVE_1 34
#define INTAKE_VALVE_2 35
#define EXHAUST_VALVE_1 36
#define EXHAUST_VALVE_2 37
#define OIL_PRESS_KPA 38
#define OIL_PRESS_PSI 39
#define GEAR 40
#define NO_DATA 41
#define TEST_DATA 42
#define BOOST_KPA 43
#define BOOST_PSI 44
#define WASTEGATE_DUTY 45
#define FUEL_PRESS_DELTA 46
#define OIL_TEMP 47
#define OIL_TEMP_F 48
#define FUEL_TEMP 49
#define FUEL_TEMP_F 50
#define FUEL_MPG_SHORT 51
#define FUEL_MPG_LONG 52

#define STOICH_RATIO 14.7f



// Data structure for each sensor value
struct sensorData {
  const char *dataNameFull;   // Full Name shown for data
  const char *dataName;   // Name shown for data on gauge
  const char *units;      // Units shown for data
  float scaleMultiplier;  // Used to scale the recieved value
  float offset;           // The offset applied to the recieved value
  float scaledValue;      // Stored value for the sensor data, after scale and offset
  float minimum;          // Minimum value used for LEDs or graphing
  float maximum;          // Maxumum value used for LEDs or graphing
  float alertLow;         // Minimum value before alerting
  float alertHigh;        // Maximum value before alerting
  int digits;              // Total number of digits before decimal
  int decimal;          // Number of values after the decimal that are used
  bool alert;             // Set when the value is outside of the alert window defined by Min -> Max
};

sensorData testData = {
  "Test Data",
  "Test",  // Name shown for data
  "%@#",   // Units shown for data
  1,       // Used to scale the recieved value
  0,       // The offset applied to the recieved value
  0,       // Stored value for the sensor data, after scale and offset
  -65,     // Minimum value used for LEDs or graphing
  65,      // Maxumum value used for LEDs or graphing
  -50,     // Minimum value before alerting
  50,      // Maximum value before alerting
  3,
  2,       // Number of values after the decimal that are used
};

sensorData noData = {
  "No Data",
  "None",  // Name shown for data
  "",      // Units shown for data
  0,       // Used to scale the recieved value
  0,       // The offset applied to the recieved value
  0,       // Stored value for the sensor data, after scale and offset
  0,       // Minimum value used for LEDs or graphing
  100,     // Maxumum value used for LEDs or graphing
  -10000,  // Minimum value before alerting
  10000,    // Maximum value before alerting
  2,
  2        // Number of values after the decimal that are used
};

// -- ID 512 --
sensorData warningStatus = {
  "Warning Status",
  "Warn",  // Name shown for data
  "",      // Units shown for data
  1,       // Used to scale the recieved value
  0,       // The offset applied to the recieved value
  0,       // Stored value for the sensor data, after scale and offset
  0,       // Minimum value used for LEDs or graphing
  100,     // Maxumum value used for LEDs or graphing
  -10000,  // Minimum value before alerting
  10000,   // Maximum value before alerting
  1,
  0        // Number of values after the decimal that are used
};



sensorData gear = {
  "Detected Gear",
  "Gear",  // Name shown for data
  "",      // Units shown for data
  1,       // Used to scale the recieved value
  0,       // The offset applied to the recieved value
  0,       // Stored value for the sensor data, after scale and offset
  0,       // Minimum value used for LEDs or graphing
  6,       // Maxumum value used for LEDs or graphing
  -10000,  // Minimum value before alerting
  10000,    // Maximum value before alerting
  1,
  0        // Number of values after the decimal that are used

};




int warningCounter = 0;
int lastError;
int revLimit;
int mainRelay;
int fuelPump;
int checkEngine = 0;
int egoHeater;

// -- ID 513 --

sensorData rpm = {
  "RPM",
  "RPM",  // Name shown for data
  "",     // Units shown for data
  1,      // Used to scale the recieved value
  0,      // The offset applied to the recieved value
  0,      // Stored value for the sensor data, after scale and offset
  0,      // Minimum value used for LEDs or graphing
  6500,   // Maxumum value used for LEDs or graphing
  -10000,  // Minimum value before alerting
  10000,   // Maximum value before alerting
  5,
  0       // Number of values after the decimal that are used
};


sensorData ignitionTiming = {
  "Ignition Timing",
  "Ign",  // Name shown for data
  "o",    // Units shown for data
  0.02,   // Used to scale the recieved value
  0,      // The offset applied to the recieved value
  0,      // Stored value for the sensor data, after scale and offset
  -35,    // Minimum value used for LEDs or graphing
  35,     // Maxumum value used for LEDs or graphing
  -50,    // Minimum value before alerting
  50,     // Maximum value before alerting
  2,
  1       // Number of values after the decimal that are used
};

sensorData injectorDuty = {
  "Injector Dutycycle",
  "Inj",  // Name shown for data
  "%",    // Units shown for data
  0.5,    // Used to scale the recieved value
  0,      // The offset applied to the recieved value
  0,      // Stored value for the sensor data, after scale and offset
  0,      // Minimum value used for LEDs or graphing
  100,    // Maxumum value used for LEDs or graphing
  -10,    // Minimum value before alerting
  110,    // Maximum value before alerting
  3,
  0       // Number of values after the decimal that are used
};

sensorData vss_mph = {
  "Spped MPH",
  "Speed",       // Name shown for data
  "mph",         // Units shown for data
  0.6213711922,  // Used to scale the recieved value
  0,             // The offset applied to the recieved value
  0,             // Stored value for the sensor data, after scale and offset
  0,             // Minimum value used for LEDs or graphing
  120,           // Maxumum value used for LEDs or graphing
  -200,          // Minimum value before alerting
  200,           // Maximum value before alerting
  3,
  0              // Number of values after the decimal that are used
};              

sensorData vss = {
  "Speed km/h",
  "Speed",  // Name shown for data
  "km/h",   // Units shown for data
  1,        // Used to scale the recieved value
  0,        // The offset applied to the recieved value
  0,        // Stored value for the sensor data, after scale and offset
  0,        // Minimum value used for LEDs or graphing
  255,      // Maxumum value used for LEDs or graphing
  -255,     // Minimum value before alerting
  2555,     // Maximum value before alerting
  3,
  0         // Number of values after the decimal that are used
};          

// -- ID 514 --

sensorData accelerator = {
  "Accelerator Position",
  "Accel",  // Name shown for data
  "%",      // Units shown for data
  0.01,     // Used to scale the recieved value
  0,        // The offset applied to the recieved value
  0,        // Stored value for the sensor data, after scale and offset
  0,        // Minimum value used for LEDs or graphing
  100,      // Maxumum value used for LEDs or graphing
  -10,      // Minimum value before alerting
  110,      // Maximum value before alerting
  3,
  0         // Number of values after the decimal that are used
}; 

sensorData throttle1 = {
  "Throttle Position 1",
  "Tps1",  // Name shown for data
  "%",     // Units shown for data
  0.01,    // Used to scale the recieved value
  0,       // The offset applied to the recieved value
  0,       // Stored value for the sensor data, after scale and offset
  -10,     // Minimum value used for LEDs or graphing
  100,     // Maxumum value used for LEDs or graphing
  -200,    // Minimum value before alerting
  200,     // Maximum value before alerting
  3,
  0        // Number of values after the decimal that are used
};


sensorData throttle2 = {
  "Throttle Position 2",  
  "Tps2",  // Name shown for data
  "%",     // Units shown for data
  0.01,    // Used to scale the recieved value
  0,       // The offset applied to the recieved value
  0,       // Stored value for the sensor data, after scale and offset
  0,       // Minimum value used for LEDs or graphing
  100,     // Maxumum value used for LEDs or graphing
  -10,     // Minimum value before alerting
  110,     // Maximum value before alerting
  3,
  0        // Number of values after the decimal that are used
}; 


sensorData wastegate = {
  "Wastegate Dutycycle",
  "WG",  // Name shown for data
  "%",   // Units shown for data
  0.01,  // Used to scale the recieved value
  0,     // The offset applied to the recieved value
  0,     // Stored value for the sensor data, after scale and offset
  0,     // Minimum value used for LEDs or graphing
  100,   // Maxumum value used for LEDs or graphing
  -200,  // Minimum value before alerting
  200,   // Maximum value before alerting
  3,
  0      // Number of values after the decimal that are used
}; 

// -- ID 515 --

sensorData manifoldPressure_psi = {
  "Manifold Prssure psi",
  "MAP",                        // Name shown for data
  "psi",                        // Units shown for data
  ((0.033333) * 0.1450377377),  // Used to scale the recieved value
  0,                            // The offset applied to the recieved value
  0,                            // Stored value for the sensor data, after scale and offset
  0,                            // Minimum value used for LEDs or graphing
  25,                           // Maxumum value used for LEDs or graphing
  999,                          // Minimum value before alerting
  -999,                         // Maximum value before alerting
  3,
  2                           // Number of values after the decimal that are used
};                        

sensorData boost_psi = {
  "Boost Pressure psi",
  "Boost",    // Name shown for data
  "psi",      // Units shown for data
  1,          // Used to scale the recieved value
  -14.69595,  // The offset applied to the recieved value
  0,  // Stored value for the sensor data, after scale and offset
  0,          // Minimum value used for LEDs or graphing
  25,         // Maxumum value used for LEDs or graphing
  -999,        // Minimum value before alerting
  999,       // Maximum value before alerting
  3,
  2           // Number of values after the decimal that are used
}; 


sensorData manifoldPressure = {
  "Manifold Pressure kPa",
  "MAP",       // Name shown for data
  "kPa",       // Units shown for data
  (0.033333),  // Used to scale the recieved value
  0,           // The offset applied to the recieved value
  0,           // Stored value for the sensor data, after scale and offset
  0,           // Minimum value used for LEDs or graphing
  250,         // Maxumum value used for LEDs or graphing
  -999,         // Minimum value before alerting
  999,        // Maximum value before alerting
  3,
  2            // Number of values after the decimal that are used
};             

sensorData boost_kpa = {
  "Boost Pressure kPa",
  "boost",   // Name shown for data
  "kPa",     // Units shown for data
  1,         // Used to scale the recieved value
  -101.325,  // The offset applied to the recieved value
  0,  // Stored value for the sensor data, after scale and offset
  0,         // Minimum value used for LEDs or graphing
  250,       // Maxumum value used for LEDs or graphing
  999,       // Minimum value before alerting
  -999,      // Maximum value before alerting
  3,
  2          // Number of values after the decimal that are used
};           

// Convert from C to F
sensorData coolantTemperature_f = {
  "Coolant Temperature F",
  "CLT",  // Name shown for data
  "F",    // Units shown for data
  1.8,    // Used to scale the recieved value
  (32),   // The offset applied to the recieved value
  0,      // Stored value for the sensor data, after scale and offset
  100,    // Minimum value used for LEDs or graphing
  250,    // Maxumum value used for LEDs or graphing
  -200,      // Minimum value before alerting
  240,    // Maximum value before alerting
  3,
  0       // Number of values after the decimal that are used
};

// Convert from C to F
sensorData intakeTemperature_f = {
  "Intake Temperature F",
  "IAT",  // Name shown for data
  "F",    // Units shown for data
  1.8,    // Used to scale the recieved value
  (32),   // The offset applied to the recieved value
  0,      // Stored value for the sensor data, after scale and offset
  0,      // Minimum value used for LEDs or graphing
  0,      // Maxumum value used for LEDs or graphing
  -120,    // Minimum value before alerting
  250,    // Maximum value before alerting
  3,
  0     // Number of values after the decimal that are used
};  

sensorData coolantTemperature = {
  "Coolant Temperature C",
  "CLT",  // Name shown for data
  "C",    // Units shown for data
  1,      // Used to scale the recieved value
  -40,    // The offset applied to the recieved value
  0,      // Stored value for the sensor data, after scale and offset
  0,      // Minimum value used for LEDs or graphing
  120,    // Maxumum value used for LEDs or graphing
  -120,    // Minimum value before alerting
  200,      // Maximum value before alerting
  3,
  0     // Number of values after the decimal that are used
};

sensorData oilTemperature = {
  "Oil Temperature C",
  "Oil",  // Name shown for data
  "C",    // Units shown for data
  1,      // Used to scale the recieved value
  -40,    // The offset applied to the recieved value
  0,      // Stored value for the sensor data, after scale and offset
  0,      // Minimum value used for LEDs or graphing
  120,    // Maxumum value used for LEDs or graphing
  -120,    // Minimum value before alerting
  200,      // Maximum value before alerting
  3,
  0     // Number of values after the decimal that are used
};

sensorData oilTemperature_f = {
  "Oil Temperature F",
  "Oil",  // Name shown for data
  "F",    // Units shown for data
  1.8,    // Used to scale the recieved value
  (32),   // The offset applied to the recieved value
  0,      // Stored value for the sensor data, after scale and offset
  0,      // Minimum value used for LEDs or graphing
  250,      // Maxumum value used for LEDs or graphing
  -120,    // Minimum value before alerting
  250,    // Maximum value before alerting
  3,
  0     // Number of values after the decimal that are used
};

sensorData fuelTemperature = {
  "Fuel Temperature C",
  "Fuel",  // Name shown for data
  "C",    // Units shown for data
  1,      // Used to scale the recieved value
  -40,    // The offset applied to the recieved value
  0,      // Stored value for the sensor data, after scale and offset
  0,      // Minimum value used for LEDs or graphing
  120,    // Maxumum value used for LEDs or graphing
  -120,    // Minimum value before alerting
  200,      // Maximum value before alerting
  3,
  0     // Number of values after the decimal that are used
};

sensorData fuelTemperature_f = {
  "Fuel Temperature F",
  "Fuel",  // Name shown for data
  "F",    // Units shown for data
  1.8,    // Used to scale the recieved value
  (32),   // The offset applied to the recieved value
  0,      // Stored value for the sensor data, after scale and offset
  0,      // Minimum value used for LEDs or graphing
  250,      // Maxumum value used for LEDs or graphing
  -120,    // Minimum value before alerting
  250,    // Maximum value before alerting
  3,
  0     // Number of values after the decimal that are used
};

sensorData intakeTemperature = {
  "Intake Temperature C",
  "IAT",  // Name shown for data
  "C",    // Units shown for data
  1,      // Used to scale the recieved value
  -40,    // The offset applied to the recieved value
  0,      // Stored value for the sensor data, after scale and offset
  0,      // Minimum value used for LEDs or graphing
  55,     // Maxumum value used for LEDs or graphing
  -100,    // Minimum value before alerting
  250,      // Maximum value before alerting
  3,
  0     // Number of values after the decimal that are used
};        

sensorData auxTemp1 = {
  "Auxiliary Temperature 1 C",
  "Aux1",  // Name shown for data
  "C",     // Units shown for data
  1,       // Used to scale the recieved value
  -40,     // The offset applied to the recieved value
  0,       // Stored value for the sensor data, after scale and offset
  0,       // Minimum value used for LEDs or graphing
  200,     // Maxumum value used for LEDs or graphing
  -1000,     // Minimum value before alerting
  1000,      // Maximum value before alerting
  3,
  0        // Number of values after the decimal that are used
};         

sensorData auxTemp1_f = {
  "Auxiliary Temperature 1 F",
  "Aux1",  // Name shown for data
  "F",     // Units shown for data
  1.8,     // Used to scale the recieved value
  32,      // The offset applied to the recieved value
  0,       // Stored value for the sensor data, after scale and offset
  0,       // Minimum value used for LEDs or graphing
  200,     // Maxumum value used for LEDs or graphing
  -1000,     // Minimum value before alerting
  1000,      // Maximum value before alerting
  3,
  0        // Number of values after the decimal that are used
};         

sensorData auxTemp2 = {
  "Auxiliary Temperature 2 C",
  "Aux2",  // Name shown for data
  "C",     // Units shown for data
  1,       // Used to scale the recieved value
  -40,     // The offset applied to the recieved value
  0,       // Stored value for the sensor data, after scale and offset
  0,       // Minimum value used for LEDs or graphing
  200,     // Maxumum value used for LEDs or graphing
  -1000,     // Minimum value before alerting
  1000,      // Maximum value before alerting
  3,
  0        // Number of values after the decimal that are used
};         

sensorData auxTemp2_f = {
  "Auxiliary Temperature 2 F",
  "Aux2",  // Name shown for data
  "F",     // Units shown for data
  1.8,     // Used to scale the recieved value
  32,      // The offset applied to the recieved value
  0,       // Stored value for the sensor data, after scale and offset
  0,       // Minimum value used for LEDs or graphing
  200,     // Maxumum value used for LEDs or graphing
  -1000,     // Minimum value before alerting
  1000,      // Maximum value before alerting
  3,
  0        // Number of values after the decimal that are used
};         

sensorData mcuTemp = {
  "Processor Temperature C",
  "MCU",  // Name shown for data
  "C",    // Units shown for data
  1,      // Used to scale the recieved value
  -40,    // The offset applied to the recieved value
  0,      // Stored value for the sensor data, after scale and offset
  0,      // Minimum value used for LEDs or graphing
  65,    // Maxumum value used for LEDs or graphing
  -40,     // Minimum value before alerting
  80,    // Maximum value before alerting
  3,
  0       // Number of values after the decimal that are used
};        

sensorData fuel = {
  "Fuel Level",
  "Fuel",  // Name shown for data
  "%",     // Units shown for data
  0.5,     // Used to scale the recieved value
  0,       // The offset applied to the recieved value
  0,       // Stored value for the sensor data, after scale and offset
  0,       // Minimum value used for LEDs or graphing
  100,     // Maxumum value used for LEDs or graphing
  -200,     // Minimum value before alerting
  200,      // Maximum value before alerting
  3,
  0        // Number of values after the decimal that are used
};         

// -- ID 516 --
sensorData afr = {
  "AFR",
  "AFR",  // Name shown for data
  "",        // Units shown for data
  0.001,     // Used to scale the recieved value
  0,         // The offset applied to the recieved value
  0,         // Stored value for the sensor data, after scale and offset
  10,        // Minimum value used for LEDs or graphing
  20,        // Maxumum value used for LEDs or graphing
  -10,        // Minimum value before alerting
  160,        // Maximum value before alerting
  2,
  2          // Number of values after the decimal that are used
};

sensorData oilPressure_psi = {
  "Oil Pressure psi",
  "Oil",                      // Name shown for data
  "psi",                      // Units shown for data
  (0.033333) * 0.1450377377,  // Used to scale the recieved value
  0,                          // The offset applied to the recieved value
  0,                          // Stored value for the sensor data, after scale and offset
  0,                          // Minimum value used for LEDs or graphing
  100,                        // Maxumum value used for LEDs or graphing
  10,                         // Minimum value before alerting
  90,                         // Maximum value before alerting
  3,
  2                           // Number of values after the decimal that are used
};                           

sensorData oilPressure = {
  "Oil Pressure kPa",
  "Oil",       // Name shown for data
  "kPa",       // Units shown for data
  (0.033333),  // Used to scale the recieved value
  0,           // The offset applied to the recieved value
  0,           // Stored value for the sensor data, after scale and offset
  0,           // Minimum value used for LEDs or graphing
  100,         // Maxumum value used for LEDs or graphing
  999,         // Minimum value before alerting
  -999,        // Maximum value before alerting
  3,
  2            // Number of values after the decimal that are used
};             

sensorData vvtPosition = {
  "VVT Position",
  "VVT",  // Name shown for data
  "o",    // Units shown for data
  0.02,   // Used to scale the recieved value
  0,      // The offset applied to the recieved value
  0,      // Stored value for the sensor data, after scale and offset
  -25,    // Minimum value used for LEDs or graphing
  25,     // Maxumum value used for LEDs or graphing
  -100,    // Minimum value before alerting
  100,   // Maximum value before alerting
  3,
  1       // Number of values after the decimal that are used
};        

sensorData batteryVoltage = {
  "Battery Voltage",
  "Bat",  // Name shown for data
  "V",    // Units shown for data
  0.001,  // Used to scale the recieved value
  0,      // The offset applied to the recieved value
  0,      // Stored value for the sensor data, after scale and offset
  10,      // Minimum value used for LEDs or graphing
  16,     // Maxumum value used for LEDs or graphing
  -11,     // Minimum value before alerting
  160,     // Maximum value before alerting
  2,
  1       // Number of values after the decimal that are used
};        

// -- ID 517 --

sensorData airMass = {
  "Air Mass mg",
  "Air",  // Name shown for data
  "mg",   // Units shown for data
  1,      // Used to scale the recieved value
  0,      // The offset applied to the recieved value
  0,      // Stored value for the sensor data, after scale and offset
  0,      // Minimum value used for LEDs or graphing
  100,   // Maxumum value used for LEDs or graphing
  9999,   // Minimum value before alerting
  -9999,  // Maximum value before alerting
  3,
  0       // Number of values after the decimal that are used
};        

sensorData estimatedAirflow = {
  "Estimated Air Flow kg/h",
  "Air",   // Name shown for data
  "kg/h",  // Units shown for data
  0.01,    // Used to scale the recieved value
  0,       // The offset applied to the recieved value
  0,       // Stored value for the sensor data, after scale and offset
  0,       // Minimum value used for LEDs or graphing
  100,     // Maxumum value used for LEDs or graphing
  999,     // Minimum value before alerting
  -999,    // Maximum value before alerting
  3,
  0        // Number of values after the decimal that are used
};         

sensorData injectorPulse = {
  "Injector Pulse ms",
  "Injector",  // Name shown for data
  "ms",        // Units shown for data
  0.003,       // Used to scale the recieved value
  0,           // The offset applied to the recieved value
  0,           // Stored value for the sensor data, after scale and offset
  0,           // Minimum value used for LEDs or graphing
  100,         // Maxumum value used for LEDs or graphing
  999,         // Minimum value before alerting
  -999,        // Maximum value before alerting
  3,
  2            // Number of values after the decimal that are used
};             

sensorData injectorPulse2 = {
  "Injector Pulse 2 ms",
  "Injector2",  // Name shown for data
  "ms",        // Units shown for data
  0.003,       // Used to scale the recieved value
  0,           // The offset applied to the recieved value
  0,           // Stored value for the sensor data, after scale and offset
  0,           // Minimum value used for LEDs or graphing
  100,         // Maxumum value used for LEDs or graphing
  999,         // Minimum value before alerting
  -999,        // Maximum value before alerting
  3,
  2            // Number of values after the decimal that are used
}; 

// NEW - Fueling 3
sensorData lambda1 = {
  "Lambda 1",
  "Lambda",   // Name shown for data
  "",         // Units shown for data
  (0.0001),   // Used to scale the recieved value
  0,          // The offset applied to the recieved value
  0,          // Stored value for the sensor data, after scale and offset
  0.7 * 100,  // Minimum value used for LEDs or graphing
  1.3 * 100,  // Maxumum value used for LEDs or graphing
  -5,  // Minimum value before alerting
  5,  // Maximum value before alerting
  1,
  2           // Number of values after the decimal that are used
};            

sensorData lambda2 = {
  "Lambda2",
  "Lambda2",  // Name shown for data
  "",         // Units shown for data
  (0.0001),   // Used to scale the recieved value
  0,          // The offset applied to the recieved value
  0,          // Stored value for the sensor data, after scale and offset
  0.7 * 100,  // Minimum value used for LEDs or graphing
  1.3 * 100,  // Maxumum value used for LEDs or graphing
  -5,  // Minimum value before alerting
  5,  // Maximum value before alerting
  1,
  2           // Number of values after the decimal that are used
};            

sensorData fuelPressureLow = {
  "Low Fuel Pressure kPa",
  "Fuel",      // Name shown for data
  "kPa",       // Units shown for data
  (0.033333),  // Used to scale the recieved value
  0,           // The offset applied to the recieved value
  0,           // Stored value for the sensor data, after scale and offset
  0,           // Minimum value used for LEDs or graphing
  50,           // Maxumum value used for LEDs or graphing
  999,         // Minimum value before alerting
  -999,        // Maximum value before alerting
  3,
  2            // Number of values after the decimal that are used
};             

sensorData fuelPressureLow_psi = {
  "Low Fuel Pressure psi",
  "Fuel",      // Name shown for data
  "psi",       // Units shown for data
  (0.033333),  // Used to scale the recieved value
  0,           // The offset applied to the recieved value
  0,           // Stored value for the sensor data, after scale and offset
  0,           // Minimum value used for LEDs or graphing
  50,           // Maxumum value used for LEDs or graphing
  999,         // Minimum value before alerting
  -999,        // Maximum value before alerting
  3,
  2            // Number of values after the decimal that are used
};             

sensorData fuelPressureHigh = {
  "High Fuel Pressure bar",
  "Fuel",  // Name shown for data
  "bar",   // Units shown for data
  0.1,     // Used to scale the recieved value
  0,       // The offset applied to the recieved value
  0,       // Stored value for the sensor data, after scale and offset
  0,       // Minimum value used for LEDs or graphing
  250,       // Maxumum value used for LEDs or graphing
  999,     // Minimum value before alerting
  -999,    // Maximum value before alerting
  3,
  1        // Number of values after the decimal that are used
};         

sensorData fuelPressureHigh_psi = {
  "High Fuel Pressure psi",
  "Fuel",  // Name shown for data
  "psi",   // Units shown for data
  0.1,     // Used to scale the recieved value
  0,       // The offset applied to the recieved value
  0,       // Stored value for the sensor data, after scale and offset
  0,       // Minimum value used for LEDs or graphing
  250,       // Maxumum value used for LEDs or graphing
  999,     // Minimum value before alerting
  -999,    // Maximum value before alerting
  3,
  2        // Number of values after the decimal that are used
};         


sensorData vvtIntake1 = {
  "Intake VVT 1 Position",
  "InVVT 1",  // Name shown for data
  "o",        // Units shown for data
  1,       // Used to scale the recieved value
  0,          // The offset applied to the recieved value
  0,          // Stored value for the sensor data, after scale and offset
  -100,          // Minimum value used for LEDs or graphing
  100,          // Maxumum value used for LEDs or graphing
  999,        // Minimum value before alerting
  -999,       // Maximum value before alerting
  3,
  1           // Number of values after the decimal that are used
};            

sensorData vvtIntake2 = {
  "Intake VVT 2 Position",
  "InVVT 2",  // Name shown for data
  "o",        // Units shown for data
  1,       // Used to scale the recieved value
  0,          // The offset applied to the recieved value
  0,          // Stored value for the sensor data, after scale and offset
  -100,          // Minimum value used for LEDs or graphing
  100,          // Maxumum value used for LEDs or graphing
  999,        // Minimum value before alerting
  -999,       // Maximum value before alerting
  3,
  1           // Number of values after the decimal that are used
};            

sensorData vvtExhaust1 = {
  "Exhaust VVT 1 Position",
  "ExVVT 1",  // Name shown for data
  "o",        // Units shown for data
  1,       // Used to scale the recieved value
  0,          // The offset applied to the recieved value
  0,          // Stored value for the sensor data, after scale and offset
  -100,          // Minimum value used for LEDs or graphing
  100,          // Maxumum value used for LEDs or graphing
  999,        // Minimum value before alerting
  -999,       // Maximum value before alerting
  3,
  1           // Number of values after the decimal that are used
};            

sensorData vvtExhaust2 = {
  "Exhaust VVT 2 Position",
  "ExVVT 2",  // Name shown for data
  "o",        // Units shown for data
  1,       // Used to scale the recieved value
  0,          // The offset applied to the recieved value
  0,          // Stored value for the sensor data, after scale and offset
  -100,          // Minimum value used for LEDs or graphing
  100,          // Maxumum value used for LEDs or graphing
  999,        // Minimum value before alerting
  -999,       // Maximum value before alerting
  3,
 1           // Number of values after the decimal that are used
};            

// NEW fueling 2

sensorData fuelConsumed = {
  "Fuel Consumed g",
  "Fuel",  // Name shown for data
  "g",     // Units shown for data
  1,       // Used to scale the recieved value
  0,       // The offset applied to the recieved value
  0,       // Stored value for the sensor data, after scale and offset
  0,       // Minimum value used for LEDs or graphing
  100,       // Maxumum value used for LEDs or graphing
  999,     // Minimum value before alerting
  -999,    // Maximum value before alerting
  3,
  2        // Number of values after the decimal that are used
};         

sensorData fuelConsumption = {
  "Fuel Consumption g/s",
  "Fuel",  // Name shown for data
  "g/s",   // Units shown for data
  0.005,   // Used to scale the recieved value
  0,       // The offset applied to the recieved value
  5,       // Stored value for the sensor data, after scale and offset
  0,       // Minimum value used for LEDs or graphing
  100,       // Maxumum value used for LEDs or graphing
  999,     // Minimum value before alerting
  -999,    // Maximum value before alerting
  3,
  2        // Number of values after the decimal that are used
};         

sensorData fuelTrim = {
  "Fuel Trim",
  "FuelTrim",  // Name shown for data
  "%",         // Units shown for data
  0.01,        // Used to scale the recieved value
  0,           // The offset applied to the recieved value
  0,           // Stored value for the sensor data, after scale and offset
  -10,           // Minimum value used for LEDs or graphing
  10,           // Maxumum value used for LEDs or graphing
  999,         // Minimum value before alerting
  -999,        // Maximum value before alerting
  3,
  2            // Number of values after the decimal that are used
};             

sensorData ethanol = {
  "Ethanol",
  "Ethanol",  // Name shown for data
  "%",        // Units shown for data
  1,          // Used to scale the recieved value
  0,          // The offset applied to the recieved value
  0,          // Stored value for the sensor data, after scale and offset
  0,          // Minimum value used for LEDs or graphing
  100,        // Maxumum value used for LEDs or graphing
  999,        // Minimum value before alerting
  -999,       // Maximum value before alerting
  3,
  1           // Number of values after the decimal that are used
};            

sensorData fuelPressDelta_kpa = {
  "Fuel Pressure Delta kPa",
  "F Delta",  // Name shown for data
  "kpa",      // Units shown for data
  1,          // Used to scale the recieved value
  0,          // The offset applied to the recieved value
  0,          // Stored value for the sensor data, after scale and offset
  0,          // Minimum value used for LEDs or graphing
  100,        // Maxumum value used for LEDs or graphing
  999,        // Minimum value before alerting
  -999,       // Maximum value before alerting
  3,
  2           // Number of values after the decimal that are used
};            

sensorData fuelPressDelta_psi = {
  "Fuel Pressure Delta psi",
  "FDelta",  // Name shown for data
  "psi",     // Units shown for data
  1,         // Used to scale the recieved value
  0,         // The offset applied to the recieved value
  0,         // Stored value for the sensor data, after scale and offset
  0,         // Minimum value used for LEDs or graphing
  100,       // Maxumum value used for LEDs or graphing
  999,       // Minimum value before alerting
  -999,      // Maximum value before alerting
  3,
  2          // Number of values after the decimal that are used
};

sensorData mpgShort = {
  "MPG",
  "MPG",  // Name shown for data
  "",      // Units shown for data
  0,       // Used to scale the recieved value
  0,       // The offset applied to the recieved value
  0,       // Stored value for the sensor data, after scale and offset
  0,       // Minimum value used for LEDs or graphing
  50,     // Maxumum value used for LEDs or graphing
  -10000,  // Minimum value before alerting
  10000,    // Maximum value before alerting
  2,
  2        // Number of values after the decimal that are used
};

sensorData mpgLong = {
  "MPG",
  "MPG",  // Name shown for data
  "avg",      // Units shown for data
  0,       // Used to scale the recieved value
  0,       // The offset applied to the recieved value
  0,       // Stored value for the sensor data, after scale and offset
  0,       // Minimum value used for LEDs or graphing
  50,     // Maxumum value used for LEDs or graphing
  -10000,  // Minimum value before alerting
  10000,    // Maximum value before alerting
  2,
  2        // Number of values after the decimal that are used
};

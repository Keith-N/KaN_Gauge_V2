/*

  'sensorData.h'

  Contains unique IDs for sensor identification, formatting, and calculation

*/

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

// Data structure for each sensor value
struct sensorData {
  const char *dataName;   // Name shown for data
  const char *units;      // Units shown for data
  float scaleMultiplier;  // Used to scale the recieved value
  float offset;           // The offset applied to the recieved value
  float scaledValue;      // Stored value for the sensor data, after scale and offset
  float minimum;          // Minimum value used for LEDs or graphing
  float maximum;          // Maxumum value used for LEDs or graphing
  float alertLow;         // Minimum value before alerting
  float alertHigh;        // Maximum value before alerting
  int precision;          // Number of values after the decimal that are used
  bool alert;             // Set when the value is outside of the alert window defined by Min -> Max
};

sensorData testData = {
  "Test",
  "%@#",
  1,
  0,
  0,
  -100,
  100,
  -50,
  50,
  0
};

sensorData noData = {
  "None",
  "",
  0,
  0,
  0,
  0,
  100,
  100,
  -100,
  0
};

// -- ID 512 --
sensorData warningStatus = {
  "Warn",
  "",
  1,
  0,
  0,
  0,
  100,
  100,
  0,
  0
};

sensorData gear = {
  "Gear",
  "",
  1,
  0,
  0,
  0,
  6,
  100,
  0,
  0
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
  "",
  1,
  0,
  0,
  0,
  7000,
  6800,
  -100,
  0
};

sensorData ignitionTiming = {
  "Ign",
  "o",
  0.02,
  0,
  0,
  -35,
  35,
  50,
  -50,
  2
};

sensorData injectorDuty = {
  "Inj",
  "%",
  0.5,
  0,
  0,
  0,
  100,
  90,
  -100,
  0
};

sensorData vss_mph = {
  "Speed",
  "mph",
  0.6213711922,
  0,
  0,
  0,
  120,
  255,
  -255,
  0
};

sensorData vss = {
  "Speed",
  "km/h",
  1,
  0,
  0,
  0,
  255,
  255,
  -255,
  0
};

// -- ID 514 --

sensorData accelerator = {
  "Accel",
  "%",
  0.01,
  0,
  0,
  0,
  100,
  200,
  -100,
  0
};

sensorData throttle1 = {
  "Tps1",
  "%",
  0.01,
  0,
  0,
  0,
  100,
  200,
  -200,
  0
};

sensorData throttle2 = {
  "Tps2",
  "%",
  0.01,
  0,
  0,
  0,
  100,
  200,
  -200,
  0
};

sensorData wastegate = {
  "WG",
  "%",
  0.01,
  0,
  0,
  0,
  100,
  200,
  -200,
  0
};

// -- ID 515 --

sensorData manifoldPressure_psi = {
  "MAP",
  "psi",
  ((0.033333) * 0.1450377377),
  0,
  0,
  0,
  25,
  999,
  -999,
  2
};

sensorData boost_psi = {
  "Boost",
  "psi",
  1,
  -14.69595,
  -14.69595,
  0,
  25,
  999,
  -999,
  2
};

sensorData manifoldPressure = {
  "MAP",
  "kPa",
  (0.033333),
  0,
  0,
  0,
  250,
  999,
  -999,
  2
};

sensorData boost_kpa = {
  "boost",
  "kPa",
  1,
  -101.325,
  -101.325,
  0,
  250,
  999,
  -999,
  2
};

// Convert from C to F
sensorData coolantTemperature_f = {
  "CLT",
  "F",
  1.8,
  (32),
  0,
  120,
  260,
  250,
  50,
  0
};

// Convert from C to F
sensorData intakeTemperature_f = {
  "IAT",
  "F",
  1.8,
  (32),
  0,
  0,
  55,
  120,
  50,
  0
};

sensorData coolantTemperature = {
  "CLT",
  "C",
  1,
  -40,
  0,
  0,
  120,
  120,
  10,
  0
};

sensorData intakeTemperature = {
  "IAT",
  "C",
  1,
  -40,
  0,
  0,
  55,
  100,
  10,
  0
};

sensorData auxTemp1 = {
  "Aux1",
  "C",
  1,
  -40,
  0,
  0,
  200,
  100,
  10,
  0
};

sensorData auxTemp1_f = {
  "Aux1",
  "F",
  1.8,
  32,
  0,
  0,
  200,
  100,
  10,
  0
};

sensorData auxTemp2 = {
  "Aux2",
  "C",
  1,
  -40,
  0,
  0,
  200,
  100,
  10,
  0
};

sensorData auxTemp2_f = {
  "Aux2",
  "F",
  1.8,
  32,
  0,
  0,
  200,
  100,
  10,
  0
};

sensorData mcuTemp = {
  "MCU",
  "C",
  1,
  -40,
  0,
  0,
  200,
  80,
  -10,
  0
};

sensorData fuel = {
  "Fuel",
  "%",
  0.5,
  0,
  0,
  0,
  100,
  200,
  15,
  0
};

// -- ID 516 --
sensorData afr = {
  "AFR",
  "",
  0.001,
  0,
  0,
  10,
  20,
  28,
  -10,
  2
};

sensorData oilPressure_psi = {
  "Oil",
  "psi",
  (0.033333) * 0.1450377377,
  0,
  0,
  0,
  100,
  999,
  -999,
  0
};

sensorData oilPressure = {
  "Oil",
  "kPa",
  (0.033333),
  0,
  0,
  0,
  100,
  999,
  -999,
  0
};

sensorData vvtPosition = {
  "VVT",
  "o",
  0.02,
  0,
  0,
  -50,
  50,
  100,
  -100,
  2
};

sensorData batteryVoltage = {
  "Bat",
  "V",
  0.001,
  0,
  0,
  8,
  16,
  15,
  11,
  2
};

// -- ID 517 --

sensorData airMass = {
  "Air",
  "mg",
  1,
  0,
  0,
  0,
  1000,
  9999,
  -9999,
  0
};

sensorData estimatedAirflow = {
  "Air",
  "kg/h",
  0.01,
  0,
  0,
  0,
  100,
  999,
  -999,
  0
};

sensorData injectorPulse = {
  "Injector",
  "ms",
  0.003,
  0,
  0,
  0,
  100,
  999,
  -999,
  2
};

// NEW - Fueling 3
sensorData lambda1 = {
  "Lambda",
  "",
  (0.0001),
  0,
  0,
  0.5 * 100,
  1.2 * 100,
  10,
  -10,
  2
};

sensorData lambda2 = {
  "Lambda2",
  "",
  (0.0001),
  0,
  0,
  0.5 * 100,
  1.2 * 100,
  100,
  -100,
  2
};

sensorData fuelPressureLow = {
  "Fuel",
  "kPa",
  (0.033333),
  0,
  0,
  0,
  0,
  999,
  -999,
  2
};

sensorData fuelPressureLow_psi = {
  "Fuel",
  "psi",
  (0.033333),
  0,
  0,
  0,
  0,
  999,
  -999,
  2
};

sensorData fuelPressureHigh = {
  "Fuel",
  "bar",
  0.1,
  0,
  0,
  0,
  0,
  999,
  -999,
  1
};

sensorData fuelPressureHigh_psi = {
  "Fuel",
  "psi",
  0.1,
  0,
  0,
  0,
  0,
  999,
  -999,
  1
};


sensorData vvtIntake1 = {
  "InVVT 1",
  "o",
  0.02,
  0,
  0,
  0,
  0,
  999,
  -999,
  2
};

sensorData vvtIntake2 = {
  "InVVT 2",
  "o",
  0.02,
  0,
  0,
  0,
  0,
  999,
  -999,
  2
};

sensorData vvtExhaust1 = {
  "ExVVT 1",
  "o",
  0.02,
  0,
  0,
  0,
  0,
  999,
  -999,
  2
};

sensorData vvtExhaust2 = {
  "ExVVT 2",
  "o",
  0.02,
  0,
  0,
  0,
  0,
  999,
  -999,
  2
};

// NEW fueling 2

sensorData fuelConsumed = {
  "Fuel",
  "g",
  1,
  0,
  0,
  0,
  0,
  999,
  -999,
  0
};

sensorData fuelConsumption = {
  "Fuel",
  "g/s",
  0.005,
  0,
  0,
  0,
  0,
  999,
  -999,
  2
};

sensorData fuelTrim = {
  "FuelTrim",
  "%",
  0.01,
  0,
  0,
  0,
  0,
  999,
  -999,
  2
};

sensorData ethanol = {
  "Ethanol",
  "%",
  1,
  0,
  0,
  0,
  100,
  999,
  -999,
  0
};

sensorData fuelPressDelta_kpa = {
  "F Delta",
  "kpa",
  1,
  0,
  0,
  0,
  100,
  999,
  -999,
  0
};

sensorData fuelPressDelta_psi = {
  "FDelta",
  "psi",
  1,
  0,
  0,
  0,
  100,
  999,
  -999,
  0
};

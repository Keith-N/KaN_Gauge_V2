#pragma once
#include <SimpleCLI.h>
#include "config.h"
#include "wifi.h"
#include "nvs.h"
#include "driver/twai.h"

// Create CLI Object
SimpleCLI cli;

// Commands
Command cmdReset;
Command cmdHelp;
Command cmdVersion;
Command cmdWifiConfig;
Command cmdSerial;
Command cmdSimulate;
Command cmdSensor;
Command cmdSensorList;
Command cmdSetSensor;
Command cmdSaveSensor;
Command cmdDefaults;
Command cmdCan;
Command cmdWifiOff;
Command cmdCanOff;
Command cmdCanPrint;
Command cmdGaugeType;
Command cmdSensorLimits;
Command cmdSensorAlerts;
Command cmdBrightness;
Command cmdGaugeColor;
Command cmdLedColor;
Command cmdLedCustomColor;
Command cmdBootOpt;
Command cmdBoardConfig;
Command cmdDisplayRate;
Command cmdTestData;
Command cmdUserConfig;
Command cmdIncUserConfig;
Command cmdSetUserConfig;

bool canEnabled = false;
bool printCan = false;

void setupCLI()
{
  cmdVersion = cli.addCmd("version");
  cmdVersion.setDescription(" display versions");

  cmdSerial = cli.addCmd("serial");
  cmdSerial.setDescription(" serial Info");

  cmdGaugeType = cli.addCommand("gauge_type");
  cmdGaugeType.addArg("t");
  cmdGaugeType.setDescription(" Select gauge type");

  cmdWifiConfig = cli.addCommand("wifi");
  cmdWifiConfig.setDescription(" Print WiFi Info");

  cmdCan = cli.addCommand("can");
  cmdCan.setDescription(" Print CAN info");

  cmdCanOff = cli.addCommand("can_enable");
  cmdCanOff.setDescription(" enable/disable can from starting on boot");

  cmdWifiOff = cli.addCommand("wifi_enable");
  cmdWifiOff.setDescription(" enable/disable Wifi from starting on boot");

  cmdCanPrint = cli.addCommand("can_print");
  cmdCanPrint.setDescription(" Print CAN messages");

  cmdSimulate = cli.addCommand("sensor_simulate");
  cmdSimulate.addArg("s");
  cmdSimulate.addArg("v");
  cmdSimulate.setDescription(" Simulate a sensor (s) value (v)");

  cmdSensor = cli.addCommand("sensor_print");
  cmdSensor.setDescription(" Prints selected sensor list and values");

  cmdSensorList = cli.addCommand("sensor_list");
  cmdSensorList.setDescription(" Print sensor list #");

  cmdSetSensor = cli.addCommand("sensor_set");
  cmdSetSensor.addArg("s");
  cmdSetSensor.addArg("v");
  cmdSetSensor.setDescription(" Select sensor(s) for specified position (v)");

  cmdSensorAlerts = cli.addCommand("sensor_alert");
  cmdSensorAlerts.addArg("s");
  cmdSensorAlerts.addArg("l");
  cmdSensorAlerts.addArg("h");
  cmdSensorAlerts.setDescription(" Set a sensor(s) alert (low / high) values");

  cmdBrightness = cli.addCommand("brightness");
  cmdBrightness.addArg("s");
  cmdBrightness.addArg("l");
  cmdBrightness.addArg("h");
  cmdBrightness.setDescription(" Set brightness low(l) and high(h) values 0-100");

  cmdSensorLimits = cli.addCommand("sensor_mm");
  cmdSensorLimits.addArg("s");
  cmdSensorLimits.addArg("l");
  cmdSensorLimits.addArg("h");
  cmdSensorLimits.setDescription(" Set a sensor (s) min (low) / max (high) values");

  cmdGaugeColor = cli.addCommand("gauge_color");
  cmdGaugeColor.addArg("s");
  cmdGaugeColor.addArg("c");
  cmdGaugeColor.setDescription(" Set gauge colors");

  cmdLedColor = cli.addCommand("led_color");
  cmdLedColor.addArg("s");
  cmdLedColor.addArg("c");
  cmdLedColor.setDescription(" Set LED colors");

  cmdLedCustomColor = cli.addCommand("led_custom");
  cmdLedCustomColor.addArg("l");
  cmdLedCustomColor.addArg("r");
  cmdLedCustomColor.addArg("g");
  cmdLedCustomColor.addArg("b");
  cmdLedCustomColor.setDescription(" Set custom LED colors");

  cmdTestData = cli.addCommand("test_data");
  cmdTestData.addArg("i");
  cmdTestData.addArg("r");
  cmdLedCustomColor.setDescription(" Set test data increment and rate");

  cmdSaveSensor = cli.addCommand("save_config");
  cmdSaveSensor.setDescription(" Save new config");

  cmdDefaults = cli.addCommand("restore_defaults");
  cmdDefaults.setDescription(" Restore gauge configuration to defaults");

  cmdReset = cli.addCmd("restart");
  cmdReset.setDescription(" Restarts device");

  cmdBootOpt = cli.addCmd("boot");
  cmdBootOpt.addArg("a");
  cmdBootOpt.addArg("b");
  cmdBootOpt.addArg("c");
  cmdBootOpt.addArg("l");
  cmdBootOpt.addArg("t");

  cmdBoardConfig = cli.addCmd("pcbrev");
  cmdBoardConfig.addArg("r");

  cmdDisplayRate = cli.addCmd("display_rate");
  cmdDisplayRate.setDescription(" Set display refresh rate in ms");
  cmdDisplayRate.addArg("r");

  cmdHelp = cli.addCommand("help");
  cmdHelp.setDescription(" Prints commands");

  cmdUserConfig = cli.addCommand("current_config");
  cmdHelp.setDescription(" Prints config");

  cmdIncUserConfig = cli.addCommand("next_config");
  cmdHelp.setDescription(" Go to next config");

}

void CLItask()
{

  if (Serial.available())
  {
    String input = Serial.readStringUntil('\n');

    if (input.length() > 0)
    {
      Serial.print("# ");
      Serial.println(input);

      cli.parse(input);
    }
  }

  if (cli.available())
  {
    Command c = cli.getCmd();
    int argNum = c.countArgs();
    Serial.print("> ");
    Serial.print(c.getName());
    Serial.print(' ');
    for (int i = 0; i < argNum; ++i)
    {
      Argument arg = c.getArgument(i);
      // if(arg.isSet()) {
      Serial.print(arg.toString());
      Serial.print(' ');
      // }
    }

    Serial.println();

    if (c == cmdReset)
    {
      Serial.println("RESTARTING!!!");
      ESP.restart();
    }

    if (c == cmdSensorList)
    {
      Serial.println("Sensors");
      for (int snsInc = 0; snsInc < 47; snsInc++)
      {
        Serial.print(snsInc);
        Serial.print(" : ");
        Serial.print(selectSensor(snsInc)->dataName);
        Serial.print(" ");
        Serial.println(selectSensor(snsInc)->units);
      }
    }

    else if (c == cmdHelp)
    {
      Serial.println("Help:");
      Serial.println(cli.toString());
    }

    else if (c == cmdWifiOff)
    {
      startWifi = !startWifi;

      saveBootConfig();
      Serial.println();
      Serial.print("Wifi : ");
      Serial.println(startWifi);
    }

    else if (c == cmdCanOff)
    {
      startCan = !startCan;

      saveBootConfig();
      Serial.println();
      Serial.print("CAN : ");
      Serial.println(startCan);
    }

    else if (c == cmdVersion)
    {
      Serial.println();
      Serial.print("SW Version : ");
      Serial.println(build);
      Serial.print("Build Type : ");
      Serial.println(buildType);
      Serial.print("PCB Revision : ");
      Serial.println(pcbRev);
      Serial.print("NVS Version : ");
      Serial.println(nvs);
    }

    else if (c == cmdGaugeType)
    {
      Command gauge(c);
      Argument gType = gauge.getArgument("t");

      int gaugeType = gType.getValue().toInt();
      Serial.println();
      Serial.println("Gauge Type set to: ");
      Serial.print(gType);
      Serial.print(" : ");


      switch (gaugeType)
      {
      case 0:
        gaugeDisplayType = 0;
        Serial.println("Arc Style");
        break;

      case 1:
        gaugeDisplayType = 1;
        Serial.println("Meter Style");
        break;

      case 2:
        gaugeDisplayType = 2;
        Serial.println("Arc Large Numbers");
        break;

      case 3:
        gaugeDisplayType = 3;
        Serial.println("Meter Large Numbers");
        break;

      case 4:
        gaugeDisplayType = 4;
        Serial.println("Large Numbers");
        break;

      default:
        gaugeDisplayType = 0;
        Serial.println("Arc Style");
        break;
      }
      resetDisplay = true;
      updateGaugeType = true;
    }

    else if (c == cmdCan)
    {
      Serial.println();
      Serial.print("Speed : 500KBITS");
      Serial.println();
      Serial.print("Mode : NORMAL");
      Serial.println();
      Serial.print("Filter : NONE");
      Serial.println();
      Serial.print("Enabled : ");
      Serial.println(canEnabled);
    }

    else if (c == cmdCanPrint)
    {
      Serial.println();
      printCan = !printCan;
      if (printCan == true)
      {
        Serial.println("Start printing CAN messages");
      }
      else
      {
        Serial.println("stop printing CAN messages");
      }
    }

    else if (c == cmdSimulate)
    {
      Command sim(c);
      Argument sensorType = sim.getArgument("s");
      Argument sensorValue = sim.getArgument("v");

      int simSensor = sensorType.getValue().toInt();
      float simVal = sensorValue.getValue().toFloat();

      Serial.println();
      Serial.println("Simulated Value");
      Serial.print("Sensor ");
      Serial.print(simSensor);
      Serial.print(" : ");
      Serial.println(ptrData[simSensor]->dataName);
      Serial.print("Value : ");
      Serial.println(simVal);
      ptrData[simSensor]->scaledValue = simVal;
    }

    else if (c == cmdTestData)
    {
      Command sim(c);
      Argument sensorType = sim.getArgument("r");
      Argument sensorValue = sim.getArgument("i");

      testIncrementValue = sensorValue.getValue().toFloat();
      testTime = sensorType.getValue().toInt();
    }

    else if (c == cmdDisplayRate)
    {
      Command sim(c);
      Argument refreshRate = sim.getArgument("r");

      int rate = refreshRate.getValue().toInt();

      Serial.println();
      Serial.println("New refresh rate");
      Serial.print(rate);
      Serial.print(" ms");
      displayRefresh_ms = rate;

    }

    else if (c == cmdGaugeColor)
    {
      Command sim(c);
      Argument sensorType = sim.getArgument("s");
      Argument sensorValue = sim.getArgument("c");

      int simSensor = sensorType.getValue().toInt();
      int simVal = sensorValue.getValue().toFloat();

      if (simSensor > 3)
      {
        simSensor = 3;
      }

      if (simSensor < 0)
      {
        simSensor = 0;
      }

      Serial.println();
      Serial.println("New Color");
      Serial.print("Color ");
      Serial.print(simSensor);
      Serial.print(" : ");
      Serial.print(colorName[simSensor]);
      Serial.print(" : ");
      Serial.println(simVal);

      selectedColor[simSensor] = simVal;
    }

    else if (c == cmdSensor)
    {

      Serial.println();
      Serial.println("Sensor List");
      for (int snsIndex = 0; snsIndex < 10; snsIndex++)
      {
        Serial.print(snsIndex);
        Serial.print(" : ");
        Serial.print(dataLocation[snsIndex]);
        Serial.print(" : ");
        Serial.print(ptrData[snsIndex]->dataName);
        Serial.print(" : ");
        Serial.print(ptrData[snsIndex]->scaledValue);
        Serial.print(" ");
        Serial.println(ptrData[snsIndex]->units);
      }
    }

    else if (c == cmdLedColor)
    {
      Command sim(c);
      Argument sensorType = sim.getArgument("s");
      Argument sensorValue = sim.getArgument("c");

      int simSensor = sensorType.getValue().toInt();
      int simVal = sensorValue.getValue().toFloat();

      if (simSensor > 3)
      {
        simSensor = 3;
      }
      if (simSensor < 0)
      {
        simSensor = 0;
      }
      if (simVal > 3)
      {
        simVal = 2;
      }
      if (simVal < 0)
      {
        simVal = 0;
      }

      Serial.println();
      Serial.println("New LED config");
      Serial.print("Style : ");
      Serial.println(ledStyleName[simSensor]);
      Serial.print("Color : ");
      Serial.println(ledColorName[simVal]);

      LEDcolor = simVal;
      LEDstyle = simSensor;
      //saveLedConfig();
    }

    else if (c == cmdBootOpt)
    {
      Command sim(c);

      Argument boota = sim.getArgument("a");
      Argument bootb = sim.getArgument("b");
      Argument bootc = sim.getArgument("c");
      Argument boottime = sim.getArgument("t");
      Argument level = sim.getArgument("l");

      bootLogo1 = boota.getValue().toInt();
      bootLogo2 = bootb.getValue().toInt();
      bootLogo3 = bootc.getValue().toInt();
      logoTime_ms = boottime.getValue().toFloat();
      quickstart = level.getValue().toFloat();

      Serial.println("New boot Config saved");
      saveBootConfig();
    }

    else if (c == cmdBoardConfig)
    {
      Command sim(c);

      Argument rev = sim.getArgument("r");
      pcbRev = rev.getValue().toInt();
      Serial.println("New rev Config saved");
      saveBootConfig();
    }

    else if (c == cmdSensorAlerts)
    {
      Command sim(c);
      Argument sensorType = sim.getArgument("s");
      Argument sensorValueH = sim.getArgument("h");
      Argument sensorValueL = sim.getArgument("l");

      int simSensor = sensorType.getValue().toInt();
      float sValH = sensorValueH.getValue().toFloat();
      float sValL = sensorValueL.getValue().toFloat();

      ptrData[10] = selectSensor(simSensor);

      Serial.println();
      Serial.println("New Alert Values");
      Serial.print("Sensor ");
      Serial.print(simSensor);
      Serial.print(" : ");
      Serial.print(ptrData[10]->dataName);
      Serial.print(" ");
      Serial.println(ptrData[10]->units);
      Serial.print("Low ");
      Serial.println(sValL);
      Serial.print("High ");
      Serial.println(sValH);

      ptrData[10]->alertHigh = sValH;
      ptrData[10]->alertLow = sValL;
      readyToUpdateLimits = true;
    }

    else if (c == cmdSensorLimits)
    {
      Command sim(c);
      Argument sensorType = sim.getArgument("s");
      Argument sensorValueH = sim.getArgument("h");
      Argument sensorValueL = sim.getArgument("l");

      int simSensor = sensorType.getValue().toInt();
      float sValH = sensorValueH.getValue().toFloat();
      float sValL = sensorValueL.getValue().toFloat();

      ptrData[10] = selectSensor(simSensor);

      Serial.println();
      Serial.println("New Min/Max Values");
      Serial.print("Sensor ");
      Serial.print(simSensor);
      Serial.print(" : ");
      Serial.print(ptrData[10]->dataName);
      Serial.print(" ");
      Serial.println(ptrData[10]->units);
      Serial.print("Min ");
      Serial.println(sValL);
      Serial.print("Max ");
      Serial.println(sValH);

      ptrData[10]->maximum = sValH;
      ptrData[10]->minimum = sValL;
      readyToUpdateLimits = true;
    }

    else if (c == cmdBrightness)
    {
      Command sim(c);
      Argument sensorType = sim.getArgument("s");
      Argument sensorValueH = sim.getArgument("h");
      Argument sensorValueL = sim.getArgument("l");

      int simSensor = sensorType.getValue().toInt();
      float sValH = sensorValueH.getValue().toInt();
      float sValL = sensorValueL.getValue().toInt();

      switch (simSensor)
      {
      case 0:
        brightness[simSensor] = sValH;
        brightness[simSensor + 1] = sValL;

        Serial.println();
        Serial.println("New display brightness");
        Serial.print("Low ");
        Serial.println(sValL);
        Serial.print("High ");
        Serial.println(sValH);

        readyToUpdateGaugeConfig = true;
        break;

      case 1:
        brightness[simSensor + 1] = sValH;
        brightness[simSensor + 2] = sValL;

        Serial.println();
        Serial.println("New LED brightness");
        Serial.print("Low ");
        Serial.println(sValL);
        Serial.print("High ");
        Serial.println(sValH);

        readyToUpdateGaugeConfig = true;
        break;

      default:
        Serial.println();
        Serial.print(" Reenter command and select 0(display) or 1 LEDs, instead of ");
        Serial.print(simSensor);

        break;
      }
    }

    else if (c == cmdLedCustomColor)
    {
      Command sim(c);
      Argument sensorType = sim.getArgument("l");
      Argument redValue = sim.getArgument("r");
      Argument blueValue = sim.getArgument("b");
      Argument greenValue = sim.getArgument("g");

      int simSensor = sensorType.getValue().toInt();
      int redVal = redValue.getValue().toFloat();
      int blueVal = blueValue.getValue().toFloat();
      int greenVal = greenValue.getValue().toFloat();

      if (simSensor > 5)
      {
        simSensor = 5;
      }
      if (simSensor < 0)
      {
        simSensor = 0;
      }

      Serial.println();
      Serial.println("New LED config");
      Serial.print("LED : ");
      Serial.println(simSensor);
      Serial.print("R ");
      Serial.print(redVal);
      Serial.print("G ");
      Serial.print(greenVal);
      Serial.print("B ");
      Serial.print(blueVal);

      saveNewLedColor(simSensor, redVal, greenVal, blueVal);
    }
    else if (c == cmdSetSensor)
    {
      Command set(c);
      Argument sensorType = set.getArgument("s");
      Argument sensorValue = set.getArgument("v");

      int newSensor = sensorType.getValue().toInt();
      int sensVal = sensorValue.getValue().toFloat();

      gaugeSensor[newSensor] = sensVal;
      ptrData[newSensor] = selectSensor(sensVal);

      Serial.println();
      Serial.println("New Sensor");
      Serial.print("Sensor ");
      Serial.print(newSensor);
      Serial.print(" : ");
      Serial.print(ptrData[newSensor]->dataName);
      Serial.print(" ");
      Serial.print(ptrData[newSensor]->units);
      resetDisplay = true;
    }

    else if (c == cmdSaveSensor)
    {
      Serial.println();
      Serial.println("Saving new config... ");
      readyToUpdate = true;
      readyToUpdateGaugeConfig = true;

      Serial.println("Done! ");
    }

    else if (c == cmdUserConfig)
    {
      Serial.println();

      // Print Config
      Serial.print("Config : ");
      Serial.println(config_selectedConfig[0]);

      // Print Gauge Style
      Serial.print("Gauge Style : ");
      Serial.println(config_gaugeStyle[config_selectedConfig[0]]);

      // Print Selected Data
      Serial.print("Data Selected : ");

      for (int inc1 = 0;  inc1 <9; inc1++){
         Serial.print(config_sensorData[config_selectedConfig[0]][inc1]);
        Serial.print(",");
      }
        Serial.println(config_sensorData[config_selectedConfig[0]][9]);

    }

     else if (c == cmdIncUserConfig)
    {
      Serial.println();
      Serial.println("Going to next config... ");
      config_selectedConfig[0]++;
      setupUserConfig();
      resetDisplay = true;

    }

    else if (c == cmdDefaults)
    {
      Serial.println();
      Serial.println("Resetting config... ");

      setToDefaults = true;
      checkNvsVer();

      Serial.println("Restarting... ");
      ESP.restart();
    }
    else if (c == cmdWifiConfig)
    {
      Serial.println();
      Serial.println("WiFi Configuration");
      Serial.print("SSID : ");
      Serial.println(ssid);
      Serial.print("PW : ");
      Serial.println(password);
      Serial.print("Name : ");
      Serial.println(host);
      Serial.print("Enabled : ");
      Serial.print(wifiEnabled);
    }

    else if (c == cmdSerial)
    {
      Serial.println();
      Serial.println("Serial / CLI");
      Serial.println("Connect with settings:");
      Serial.print("Rate : ");
      Serial.println(115200);
      Serial.println("DTR : OFF");
      Serial.println("RTS : OFF");
    }
  }

  if (cli.errored())
  {
    CommandError cmdError = cli.getError();

    Serial.print("CLI ERROR: ");
    Serial.println(cmdError.toString());

    if (cmdError.hasCommand())
    {
      Serial.print("Did you mean \"");
      Serial.print(cmdError.getCommand().toString());
      Serial.println("\"?");
    }
  }
}

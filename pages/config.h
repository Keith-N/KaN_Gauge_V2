
/*
 *
 * Config Update Page
 *
 *  Adjusting the gauge configurations are done here
 *    Gauge sensor selection for display and LEDs
 *    Change LED mode
 *    Change display update rate
 *    Change sensor limits for LED display and alert LED
 *
 *
 */

const char gaugeConfigPage[] = R"rawliteral(
<!DOCTYPE HTML><html>

<meta name="viewport" content="width=device-width, initial-scale=1">

<style>
input{background:#f1f1f1;border:0;padding:0 15px}
body{background:#cc8943;font-family:sans-serif;font-size:14px;color:#777}
#file-input,input{width: 100%;height:44px;border-radius:4px;margin:10px auto;font-size:15px}
#file-input{padding:0 10px;box-sizing:border-box;border:1px solid #ddd;line-height:44px;text-align:left;display:block;cursor:pointer; white-space: nowrap; overflow: hidden; text-overflow: ellipsis;}
#bar,#prgbar{background-color:#f1f1f1;border-radius:10px}#bar{background-color:#cc8943;width:0%;height:10px;}
form{background:#fff;max-width:258px;margin:75px auto;padding:35px; padding-bottom: 30px;border: 1px solid #cc8943;border-radius:5px;text-align:center}
.btn {background-color: #3498db1;box-shadow: 0 0 8px 0 rgba(0, 0, 0, 0.08), 0 0 15px 0 rgba(0, 0, 0, 0.02), 0 0 20px 4px rgba(0, 0, 0, 0.06);color: white;border-radius: 4px;padding: 9px 16px;background-image: none;
text-decoration: none;border: none;letter-spacing:1.25px;cursor: pointer;text-transform:uppercase;font-size:14px;line-height: 18px;display: inline-block;vertical-align: middle;}
.btn:hover {background-color: #0097a7;box-shadow: 0px 2px 4px -1px rgba(0, 0, 0, 0.2), 0px 4px 5px 0px rgba(0, 0, 0, 0.14), 0px 1px 10px 0px rgba(0,0,0,.12);}
.btn:visited {color: white;}
.btn:focus {outline: none;}
.btn:active {color: white;background-color: #007c91;}

.btn2 {background-color: #e29425;box-shadow: 0 0 8px 0 rgba(0, 0, 0, 0.08), 0 0 15px 0 rgba(0, 0, 0, 0.02), 0 0 20px 4px rgba(0, 0, 0, 0.06);color: white;border-radius: 4px;padding: 9px 16px;background-image: none;
text-decoration: none;border: none;letter-spacing:1.25px;cursor: pointer;text-transform:uppercase;font-size:14px;line-height: 18px;display: inline-block;vertical-align: middle;}
.btn2:hover:enabled {background-color: #d68a1d;box-shadow: 0px 2px 4px -1px rgba(0, 0, 0, 0.2), 0px 4px 5px 0px rgba(0, 0, 0, 0.14), 0px 1px 10px 0px rgba(0,0,0,.12);}
.btn2:visited {color: white;}
.btn2:focus {outline: none;}
.btn2:active {color: white;background-color: #ca7125;}
.btn2:disabled {
  cursor: default;
    background: #DDD;
}
   html {
     font-family: Roboto, Arial, sans-serif;
     display: inline-block;
     margin: 0px auto;
     text-align: center;
    }
    h2 { font-size: 3.0rem; 
       font-family: Arial;
      text-align: center;
      font-weight: normal;
      color: #fafcfc;
     }
    p { font-size: 1.0rem; margin-top: 0;}
    .units { font-size: 1.2rem; }
    .dht-labels{
      font-size: 1.5rem;
      vertical-align:middle;
      padding-bottom: 15px;
      font-weight: normal;
      color: #FFFFFFFF;
    }
</style>
<head>
  
  <title> Gauge Configuration </title>

</head>
<body>

  <script type="text/javascript">
      function notify(message) {
          alert(message);
      }
  </script>

  <h1 style="color:white;">Gauge Configuration</h1>

<form action="/setConfig">
  <p>Select current configuration</p>
  
  <label for="B"></label>
  <select id="B" name="B"> 
    <option value="0">1</option>
    <option value="1">2</option>
    <option value="2">3</option>
    </select>
  <br>
  <br>
  <input type="submit" value = "Set new configuration" onClick="notify('New Configuration Sent')">
  <br>
</form> 

<form action="/setGaugeType">
  <p>Select Gauge Type</p>
  <p1> for current configuration </p1><br><br>
  <label for="B"></label>
  <select id="B" name="B"> 
    <option value="0">2x Arc with 4x Digital</option>
    <option value="1">1x Meter with 5x Digital</option>
    <option value="2">1x Arc with large numbers</option>
    <option value="3">1x Meter with large numbers</option>
    <option value="4">1x Large numbers</option>
    </select>
  <br>
  <br>
  <input type="submit" value = "Set new configuration" onClick="notify('New Configuration Sent')">
  <br>
</form> 


<form action="/setGaugeConfig">
  <p>Select Gauge Sensors FOME</p>
  <p1>Selects displayed sensor for selected location in current configuration</p1> <br><br>
  
  <label for="B"></label>
  <select id="B" name="B"> 
    <option value="0">Arc Inside</option>
    <option value="1">Arc Outside</option>
    <option value="9">Analog Meter</option>
    <option value="6">LEDs</option>
    <option value="2">Digits Top</option>
    <option value="7">Digits Left</option>
    <option value="8">Digits Right</option>
    <option value="4">Digits Center </option>
    <option value="3">Digits Bottom Left</option>
    <option value="5">Digits Bottom Right</option>
    </select>
  <br>
  
  <label for="C"></label>
  <select id="C" name="C"> 
    <option value="0">E0 AFR</option>
    <option value="1">RPM</option>
    <option value="2">Speed KPH</option>
    <option value="3">Speed MPH</option>
    <option value="4">MAP kpa</option>
    <option value="5">MAP psi</option>
    <option value="6">Coolant Temp C</option>
    <option value="7">Coolant Temp F</option>
    <option value="8">Intake Temp C</option>
    <option value="9">Intake Temp F</option>
    <option value="10">Accelerator</option>
    <option value="11">Ignition Timing</option>
    <option value="12">Injector Duty</option>
    <option value="13">Injector Pulse</option>
    <option value="14">TPS 1</option>
    <option value="15">TPS 2</option>
    <option value="16">VVT Position</option>
    <option value="17">Air Mass</option>
    <option value="18">Est Air Flow</option>
    <option value="19">Fuel Level</option>
    <option value="20">MCU Temp</option>
    <option value="21">Aux Temp 1 C</option>
    <option value="22">Aux Temp 1 F</option>
    <option value="23">Aux Temp 2 C</option>
    <option value="24">Aux Temp 2 F</option>
    <option value="25">Battery Voltage</option>
    <option value="26">Fuel Ethanol</option>
    <option value="27">Lambda 1</option>
    <option value="28">Lambda 2</option>
    <option value="29">Fuel Pressure (Low)</option>
    <option value="30">Fuel Pressure (High)</option>
    <option value="31">Fuel Consumed</option>
    <option value="32">Fuel Flow</option>
    <option value="33">Fuel Trim</option>
    <option value="34">Intake VVT 1</option>
    <option value="35">Intake VVT 2</option>
    <option value="36">Exhaust VVT 1</option>
    <option value="37">Exhaust VVT 2</option>
    <option value="38">Oil Pressure kpa</option>
    <option value="39">Oil Pressure psi</option>
    <option value="40">Detected Gear</option>
    <option value="41">No Data</option>
    <option value="42">Test Data</option>
    <option value="43">Boost kPa</option>
    <option value="44">Boost Psi</option>
    <option value="45">Wastegate Duty</option>
    <option value="46">Fuel Pressure Delta</option>
    <option value="47">Oil Temp</option>
    <option value="48">Oil Temp F</option>
    <option value="49">Fuel Temp</option>
    <option value="50">Fuel Temp F</option>
    </select>

  <br>
  <input type="submit" value = "Set new configuration" onClick="notify('New Configuration Sent')">
  <br>
<button>
<a href="https://github.com/Keith-N/KaN_Gauge_V2/wiki/Gauge-Types" target="_blank">Gauge Types</a>
</button>
</form>

<form action="/setGaugeConfig">
<p>Select Gauge Sensors MS</p>
  <p1>Selects displayed sensor for selected location in current configuration</p1> 
  <br><br>
  <label for="B"></label>
  <select id="B" name="B"> 
    <option value="0">Arc Inside</option>
    <option value="1">Arc Outside</option>
    <option value="9">Analog Meter</option>
    <option value="6">LEDs</option>
    <option value="2">Digits Top</option>
    <option value="7">Digits Left</option>
    <option value="8">Digits Right</option>
    <option value="4">Digits Center </option>
    <option value="3">Digits Bottom Left</option>
    <option value="5">Digits Bottom Right</option>
    </select>
  <br>
  
  <label for="C"></label>
  <select id="C" name="C"> 
    <option value="0">AFR</option>

    <option value="1">RPM</option>

    <option value="2">Speed KPH</option>
    <option value="3">Speed MPH</option>

    <option value="4">MAP kpa</option>
    <option value="5">MAP psi</option>

    <option value="6">Coolant Temp C</option>
    <option value="7">Coolant Temp F</option>

    <option value="8">Intake Temp C</option>
    <option value="9">Intake Temp F</option>

    <option value="11">Ignition Timing</option>

    <option value="12">Injector Duty</option>
    <option value="13">Injector Pulse</option>

    <option value="14">TPS</option>
    <option value="21">Aux 1</option>
    <option value="23">Aux 2</option>
    <option value="25">Battery Voltage</option>

    <option value="33">Fuel Trim</option>

    <option value="41">No Data</option>
    <option value="42">Test Data</option>

    <option value="43">Boost kPa</option>
    <option value="44">Boost Psi</option>


    </select>

  <br>
  <input type="submit" value = "Set new configuration" onClick="notify('New Configuration Sent')">
  <br>
<button>
<a href="https://github.com/Keith-N/KaN_Gauge_V2/wiki/Gauge-Types" target="_blank">Gauge Types</a>
</button>
</form>


<form action="/setAlertType">
  <p>Select Alert Type</p>
  <p1>Occurs when a displayed value exceeds Alert High/Low</p1>
  <br> <br>
  
  <label for="B"></label>
  <select id="B" name="B"> 
    <option value="0">Only Text Color</option>
    <option value="1">Exclamation</option>
    <option value="2">FF (Fullscreen)</option>
    <option value="3">LED flash</option>
    </select>
  <br>

  <br>
  <input type="submit" value = "Set new configuration" onClick="notify('New Configuration Sent')">
  <br> 
</form> 

<form action="/setLimitConfig"> 
<p>Configure Data Limits</p><br>
<p1> Min/Max used Arc/Meter/LEDs </p1> <br>
<p1> Alert Low/High used to activate Alert </p1> <br> 
<br>
<p1>Sensor</p1>
  <label for="A"></label>
  <select id="A" name="A">
    <option value="0">E0 AFR</option>
    <option value="1">RPM</option>
    <option value="2">Speed KPH</option>
    <option value="3">Speed MPH</option>
    <option value="4">MAP kpa</option>
    <option value="5">MAP psi</option>
    <option value="6">Coolant Temp C</option>
    <option value="7">Coolant Temp F</option>
    <option value="8">Intake Temp C</option>
    <option value="9">Intake Temp F</option>
    <option value="10">Accelerator</option>
    <option value="11">Ignition Timing</option>
    <option value="12">Injector Duty</option>
    <option value="13">Injector Pulse</option>
    <option value="14">TPS 1</option>
    <option value="15">TPS 2</option>
    <option value="16">VVT Position</option>
    <option value="17">Air Mass</option>
    <option value="18">Est Air Flow</option>
    <option value="19">Fuel Level</option>
    <option value="20">MCU Temp</option>
    <option value="21">Aux Temp 1 C</option>
    <option value="22">Aux Temp 1 F</option>
    <option value="23">Aux Temp 2 C</option>
    <option value="24">Aux Temp 2 F</option>
    <option value="25">Battery Voltage</option>
    <option value="26">Fuel Ethanol</option>
    <option value="27">Lambda 1</option>
    <option value="28">Lambda 2</option>
    <option value="29">Fuel Pressure (Low)</option>
    <option value="30">Fuel Pressure (High)</option>
    <option value="31">Fuel Consumed</option>
    <option value="32">Fuel Flow</option>
    <option value="33">Fuel Trim</option>
    <option value="34">Intake VVT 1</option>
    <option value="35">Intake VVT 2</option>
    <option value="36">Exhaust VVT 1</option>
    <option value="37">Exhaust VVT 2</option>
    <option value="38">Oil Pressure kpa</option>
    <option value="39">Oil Pressure psi</option>
    <option value="40">Detected Gear</option>
    <option value="41">No Data</option>
    <option value="42">Test Data</option>
    <option value="43">Boost kpa</option>
    <option value="44">Boost psi</option>
    <option value="45">Wastegate Duty</option>
    <option value="46">Fuel Pressure Delta</option>
    <option value="47">Oil Temp</option>
    <option value="48">Oil Temp F</option>
    <option value="49">Fuel Temp</option>
    <option value="50">Fuel Temp F</option>
    </select>
  <br> <br>
  
  <p1>Minimum</p1>
  <label for="B"></label>
  <input type="text" id="B" name="B">
  <br>
   
  <p1>Maximum</p1>
  <label for="C"></label>
  <input type="text" id="C" name="C">
  <br>
  
  <p1>Alert Low</p1> 
  <label for="D"></label>
  <input type="text" id="D" name="D">
  <br>
  
  <p1>Alert High</p1>
  <label for="E"></label>
  <input type="text" id="E" name="E">
  <br>
  
  <br>
  <input type="submit" value ="Set new value" onClick="notify('New limit sent')">
  <br>
</form>


<form action="/setDisplayRate"> 
<p> Display Update Rate </p><br>
 
  <label for="A"></label>
  <input type="text" id="A" name="A">
  <p1>ms</p1>
  <br> <br>
  <input type="submit" value ="Set new value" onClick="notify('New value sent')">
  <br>
</form>

<form action="/setBrightness"> 
  <p>Set Brightness</p><br>
  <p1>Values from 0 to 100 Brightness based on Analog input </p1> <br> <br>
  
    <label for="A"></label>
    <select id="A" name="A">
    <option value="0">Display</option>
    <option value="2">LEDs</option>
    </select>
  <br> <br>

  <p1>Input 0V</p1>
  <label for="B"></label>
  <input type="text" id="B" name="B"><br>
  
  <p1>Input 12V</p1>
  <label for="C"></label>
  <input type="text" id="C" name="C"><br>
  
  
  <br>
  <input type="submit" value ="Set new value" onClick="notify('New limit sent')">
  <br>
</form>

<form action="/setArc1"> 
  <p>Inner Arc Configuration</p>
  <p1>Color</p1>
    <label for="A"></label>
    <select id="A" name="A">
    <option value="0">Red</option>
    <option value="1">Green</option>
    <option value="2">Blue</option>
    <option value="3">Blue-Red</option>
    <option value="4">Green-Red</option>
    <option value="5">Red-Green</option>
    <option value="6">White</option>
    </select>
  <br>
  <br>

  <p1>Segments Width</p1>
  <label for="B"></label>
  <input type="text" id="B" name="B"><br>
  <br>

  <p1>Segment Spacing</p1>
  <label for="C"></label>
  <input type="text" id="C" name="C"><br>
  
  <br>
  <input type="submit" value ="Set new value" onClick="notify('New config sent')">
  <br>
</form>

<form action="/setArc2"> 
  <p>Outer Arc Configuration</p>
  <p1>Color</p1>
    <label for="A"></label>
    <select id="A" name="A">
    <option value="0">Red</option>
    <option value="1">Green</option>
    <option value="2">Blue</option>
    <option value="3">Blue-Red</option>
    <option value="4">Green-Red</option>
    <option value="5">Red-Green</option>
    <option value="6">White</option>
    </select>
  <br>
  <br>

  <p1>Segments Width</p1>
  <label for="B"></label>
  <input type="text" id="B" name="B"><br>
  <br>

  <p1>Segment Spacing</p1>
  <label for="C"></label>
  <input type="text" id="C" name="C"><br>
  
  <br>
  <input type="submit" value ="Set new value" onClick="notify('New config sent'')">
  <br>
</form>

<form action="/setTextColor"> 
  <p>Set Display Colors</p>
    <label for="A"></label>
    <select id="A" name="A">
    <option value="0">Value Digits</option>
    <option value="1">Unit Text</option>
    <option value="2">Alert Digits</option>
    <option value="3">Meter Needle</option>
    </select>

    <label for="B"></label>
    <select id="B" name="B">
    <option value="65535">White</option>
    <option value="2047">Cyan</option>
    <option value="31">Blue</option>
    <option value="65504">Yellow</option>
    <option value="64928">Orange</option>
    <option value="63488">Red</option>
    <option value="65049">Pink</option>
    <option value="2016">Green</option>
    <option value="30735">Purple</option>
    <option value="0">Black</option>
    </select>

<br>

  <br>
  <input type="submit" value ="Set new value" onClick="notify('New Config Sent')">
  <br>
</form>

<form action="/setLedColor"> 
  <p>Set LED Colors</p>
    <label for="A"></label>
    <select id="A" name="A">
    <option value="1">Blue -> Green -> Red</option>
    <option value="2">Green -> Red</option>
    <option value="0">No LEDs</option>
    <option value="3">Custom</option>
    </select>
<br>

<br>
    <p>Set LED Style</p>
    <label for="B"></label>
    <select id="B" name="B">
    <option value="0">One Color Sequential LEDs</option>
    <option value="1">Multi-Color Sequential LEDs</option>
    <option value="2">Single LED</option>
    </select>

  <br>

  
  <br>
  <input type="submit" value ="Set new value" onClick="notify('New Config Sent')">
  <br>
</form>

<form action="/setLEDCustom"> 
  <p>Set Custom LED Color</p>
  <p1>Values from 0 to 100</p1>
<br> <br>
  

 <p1> LED 1 </p1>
  <br>
  <p1> R </p1>
  <label for="R1"></label>
  <input type="text" id="R1" name="R1"><br>

  <p1> G </p1>
  <label for="G1"></label>
  <input type="text" id="G1" name="G1"><br>

  <p1> B </p1>
  <label for="B1"></label>
  <input type="text" id="B1" name="B1"><br>
  
   <br> <br>
    
  <p1> LED 2 </p1>
  <br>
  <p1> R </p1>
  <label for="R2"></label>
  <input type="text" id="R2" name="R2"><br>

  <p1> G </p1>
  <label for="G2"></label>
  <input type="text" id="G2" name="G2"><br>

  <p1> B </p1>
  <label for="B2"></label>
  <input type="text" id="B2" name="B2"><br>
  
   <br> 
   
  <p1> LED 3 </p1>
  <br>
  <p1> R </p1>
  <label for="R3"></label>
  <input type="text" id="R3" name="R3"><br>

  <p1> G </p1>
  <label for="G3"></label>
  <input type="text" id="G3" name="G3"><br>

  <p1> B </p1>
  <label for="B3"></label>
  <input type="text" id="B3" name="B3"><br>
  <br>
  
  <p1> LED 4 </p1>
  <br>
  <p1> R </p1>
  <label for="R4"></label>
  <input type="text" id="R4" name="R4"><br>

  <p1> G </p1>
  <label for="G4"></label>
  <input type="text" id="G4" name="G4"><br>

  <p1> B </p1>
  <label for="B4"></label>
  <input type="text" id="B4" name="B4"><br>
  <br>
  
  <p1> LED 5 </p1>
  <br>
  <p1> R </p1>
  <label for="R5"></label>
  <input type="text" id="R5" name="R5"><br>

  <p1> G </p1>
  <label for="G5"></label>
  <input type="text" id="G5" name="G5"><br>

  <p1> B </p1>
  <label for="B5"></label>
  <input type="text" id="B5" name="B5"><br>
  <br>
  
  <p1> LED 6 </p1>
  <br>
  <p1> R </p1>
  <label for="R6"></label>
  <input type="text" id="R6" name="R6"><br>

  <p1> G </p1>
  <label for="G6"></label>
  <input type="text" id="G6" name="G6"><br>

  <p1> B </p1>
  <label for="B6"></label>
  <input type="text" id="B6" name="B6"><br>
   
  <br>
  <input type="submit" value ="Set new value" onClick="notify('New limit sent')">
  <br>
</form>


  <form action="/">
  <input type="submit" value = "Back">
  </form>


</body>
</html>
)rawliteral";
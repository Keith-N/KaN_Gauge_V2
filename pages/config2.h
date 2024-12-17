
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

const char gaugeConfigPage2[] PROGMEM = R"=====(
<!DOCTYPE HTML>
<html>

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

<!-- ------------------------------------------------------------------ Header ------------------------------------------------------------------ -->

<head>
  
  <title> Gauge Configuration </title>

</head>
<body>

  <script type="text/javascript">
      function notify(message) {
          alert(message);
      }
  </script>

<!-- ------------------------------------------------------------------ Gauge config 1-3 ------------------------------------------------------------------ -->


  <form action="/setConfig">
  <p>Select configuration</p>
  <h4> Current : <span id = "currentGaugeConfig"></span></h4>
  
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


<!-- ---------------------------------------------------------------- Gauge Type ------------------------------------------------------------------ -->



<form action="/setGaugeType">
  <p>Select Gauge Type</p>
  <h4>Current : <span id = "currentGaugeType"></span></h4>
  <label for="B"></label>
  <select id="B" name="B"> 
    <option value="0">2x Arc with 4x Digital</option>
    <option value="1">1x Meter with 5x Digital</option>
    <option value="2">1x Arc with large numbers</option>
    <option value="3">1x Meter with large numbers</option>
    <option value="4">1x Large numbers</option>
	<option value="5">4x Digital</option>
    </select>
  <br>
  <br>
  <input type="submit" value = "Set new configuration" onClick="notify('New Configuration Sent')">
  <br>
</form> 


<!-- ---------------------------------------------------------------- Gauge Sensors ------------------------------------------------------------------ -->

<form>
<p> Current Sensor Selection <p>
  <h4>Inside Arc : <span id = "currentSensor1"></span></h4>
  
  <h4>Outside Arc : <span id = "currentSensor2"></span></h4>
  
  <h4>Center : <span id = "currentSensor3"></span></h4>
  
  <h4>Bottom Left : <span id = "currentSensor4"></span></h4>
  
  <h4>Center Bottom : <span id = "currentSensor5"></span></h4>
  
  <h4>Bottom Right : <span id = "currentSensor6"></span></h4>
  
  <h4>LEDs : <span id = "currentSensor7"></span></h4>
  
  <h4>Top Left : <span id = "currentSensor8"></span></h4>
  
  <h4>Top Right : <span id = "currentSensor9"></span></h4>
  
  <h4>Meter : <span id = "currentSensor10"></span></h4>
  
<button>
<a href="https://github.com/Keith-N/KaN_Gauge_V2/wiki/Gauge-Types" target="_blank">Gauge Types</a>
</button>
</form>

<!-- ---------------------------------------------------------------- Set Gauge Sensors FOME ------------------------------------------------------------------ -->
<form action="/setGaugeConfig">
  <p>Select Gauge Sensors FOME</p>  
  <label for="B"></label>
  <select id="B" name="B"> 
    <option value="0">Arc Inside / Bottom</option>
    <option value="1">Arc Outside / Top</option>
    <option value="9">Analog Meter</option>
    <option value="6">LEDs</option>
    <option value="2">Top Center</option>
    <option value="7">Top Left</option>
    <option value="8">Top Right</option>
    <option value="4">Bottom Center </option>
    <option value="3">Bottom Left / Left</option>
    <option value="5">Bottom Right / Right</option>
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
</form>

<!-- ---------------------------------------------------------------- Set Gauge Sensors MS ------------------------------------------------------------------ -->
<form action="/setGaugeConfig">
<p>Select Gauge Sensors MS</p>
  <label for="B"></label>
  <select id="B" name="B"> 
    <option value="0">Arc Inside</option>
    <option value="1">Arc Outside</option>
    <option value="9">Analog Meter</option>
    <option value="6">LEDs</option>
    <option value="2">Top Center</option>
    <option value="7">Top Left</option>
    <option value="8">Top Right</option>
    <option value="4">Bottom Center </option>
    <option value="3">Bottom Left</option>
    <option value="5">Bottom Right</option>
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
</form>

<!-- ------------------------------------------------------------------ Configure sensor limits ------------------------------------------------------------------ -->

  <form action="/sensorConfiguration">
  <input type="submit" value = "Configure Sensor Limits">
  </form>

<!-- ------------------------------------------------------------------ Back Button ------------------------------------------------------------------ -->


  <form action="/">
  <input type="submit" value = "Back">
  </form>



<!-- ------------------------------------------------------------------ Intervals ------------------------------------------------------------------ -->

<script>

function getData() {
	getGaugeConfig();
	getGaugeType();
	
	getSensor1();
	getSensor2();
	getSensor3();
	getSensor4();
	getSensor5();
	getSensor6();
	getSensor7();
	getSensor8();
	getSensor9();
	getSensor10();
	
	
}; 

getData();


<!-- ------------------------------------------------------------------ Functions ------------------------------------------------------------------ -->

function getGaugeConfig() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("currentGaugeConfig").innerHTML = this.responseText;
    }
  };

  xhttp.open("GET", "gaugeConfig", true);
  xhttp.send();
}


function getGaugeType() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("currentGaugeType").innerHTML = this.responseText;
    }
  };

  xhttp.open("GET", "gaugeType", true);
  xhttp.send();
}

function getSensor1() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("currentSensor1").innerHTML = this.responseText;
    }
  };

  xhttp.open("GET", "sensor1", true);
  xhttp.send();
}

function getSensor2() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("currentSensor2").innerHTML = this.responseText;
    }
  };

  xhttp.open("GET", "sensor2", true);
  xhttp.send();
}

function getSensor3() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("currentSensor3").innerHTML = this.responseText;
    }
  };

  xhttp.open("GET", "sensor3", true);
  xhttp.send();
}

function getSensor4() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("currentSensor4").innerHTML = this.responseText;
    }
  };

  xhttp.open("GET", "sensor4", true);
  xhttp.send();
}

function getSensor5() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("currentSensor5").innerHTML = this.responseText;
    }
  };

  xhttp.open("GET", "sensor5", true);
  xhttp.send();
}

function getSensor6() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("currentSensor6").innerHTML = this.responseText;
    }
  };

  xhttp.open("GET", "sensor6", true);
  xhttp.send();
}

function getSensor7() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("currentSensor7").innerHTML = this.responseText;
    }
  };

  xhttp.open("GET", "sensor7", true);
  xhttp.send();
}

function getSensor8() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("currentSensor8").innerHTML = this.responseText;
    }
  };

  xhttp.open("GET", "sensor8", true);
  xhttp.send();
}

function getSensor9() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("currentSensor9").innerHTML = this.responseText;
    }
  };

  xhttp.open("GET", "sensor9", true);
  xhttp.send();
}

function getSensor10() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("currentSensor10").innerHTML = this.responseText;
    }
  };

  xhttp.open("GET", "sensor10", true);
  xhttp.send();
}

</script>
</body>
</html>
)=====";
const char sensorConfigPage[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>


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
	<title> Sensor Limits Configuration </title>
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

<!-- ------------------------------------------------------------------ Limits ------------------------------------------------------------------ -->	

<form action="/setLimitConfig"> 
<p>Configure Sensor Limits</p><br>
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


<form>
<p> Inside Arc <p>
<h4><span id = "currentSensor1"></span></h4>
  <h4> Minimum <span id = "currentSensor1min"></span></h4>
  <h4> Maximum <span id = "currentSensor1max"></span></h4>
  <h4> Alert Low <span id = "currentSensor1low"></span></h4>
  <h4> Alert High <span id = "currentSensor1high"></span></h4>
  <br>


<p> Outside Arc <p>
<h4><span id = "currentSensor2"></span></h4>
  <h4> Minimum <span id = "currentSensor2min"></span></h4>
  <h4> Maximum <span id = "currentSensor2max"></span></h4>
  <h4> Alert Low <span id = "currentSensor2low"></span></h4>
  <h4> Alert High <span id = "currentSensor2high"></span></h4>
  <br>



<p> Top Center <p>
<h4><span id = "currentSensor3"></span></h4>
  <h4> Minimum <span id = "currentSensor3min"></span></h4>
  <h4> Maximum <span id = "currentSensor3max"></span></h4>
  <h4> Alert Low <span id = "currentSensor3low"></span></h4>
  <h4> Alert High <span id = "currentSensor3high"></span></h4>
  <br>



<p> Bottom Left <p>
<h4><span id = "currentSensor4"></span></h4>
  <h4> Minimum <span id = "currentSensor4min"></span></h4>
  <h4> Maximum <span id = "currentSensor4max"></span></h4>
  <h4> Alert Low <span id = "currentSensor4low"></span></h4>
  <h4> Alert High <span id = "currentSensor4high"></span></h4>
  <br>



<p> Center Bottom <p>
<h4><span id = "currentSensor5"></span></h4>
  <h4> Minimum <span id = "currentSensor5min"></span></h4>
  <h4> Maximum <span id = "currentSensor5max"></span></h4>
  <h4> Alert Low <span id = "currentSensor5low"></span></h4>
  <h4> Alert High <span id = "currentSensor5high"></span></h4>
  <br>


<p> Bottom Right <p>
<h4><span id = "currentSensor6"></span></h4>
  <h4> Minimum <span id = "currentSensor6min"></span></h4>
  <h4> Maximum <span id = "currentSensor6max"></span></h4>
  <h4> Alert Low <span id = "currentSensor6low"></span></h4>
  <h4> Alert High <span id = "currentSensor6high"></span></h4>
  <br>



<p> LEDs <p>
<h4><span id = "currentSensor7"></span></h4>
  <h4> Minimum <span id = "currentSensor7min"></span></h4>
  <h4> Maximum <span id = "currentSensor7max"></span></h4>
  <h4> Alert Low <span id = "currentSensor7low"></span></h4>
  <h4> Alert High <span id = "currentSensor7high"></span></h4>
  <br>



<p> Top Left <p>
<h4><span id = "currentSensor8"></span></h4>
  <h4> Minimum <span id = "currentSensor8min"></span></h4>
  <h4> Maximum <span id = "currentSensor8max"></span></h4>
  <h4> Alert Low <span id = "currentSensor8low"></span></h4>
  <h4> Alert High <span id = "currentSensor8high"></span></h4>
  <br>



<p> Top Right <p>
<h4><span id = "currentSensor9"></span></h4>
  <h4> Minimum <span id = "currentSensor9min"></span></h4>
  <h4> Maximum <span id = "currentSensor9max"></span></h4>
  <h4> Alert Low <span id = "currentSensor9low"></span></h4>
  <h4> Alert High <span id = "currentSensor9high"></span></h4>
  <br>



<p> Meter <p>
<h4><span id = "currentSensor10"></span></h4>
  <h4> Minimum <span id = "currentSensor10min"></span></h4>
  <h4> Maximum <span id = "currentSensor10max"></span></h4>
  <h4> Alert Low <span id = "currentSensor10low"></span></h4>
  <h4> Alert High <span id = "currentSensor10high"></span></h4>
</form>

<!-- ------------------------------------------------------------------ Configure sensor limits ------------------------------------------------------------------ -->

  <form action="/gaugeConfiguration">
  <input type="submit" value = "Gauge Configuration">
  </form>


<!-- ------------------------------------------------------------------ Back Button ------------------------------------------------------------------ -->

  <form action="/">
  <input type="submit" value = "Back">
  </form>



<!-- ------------------------------------------------------------------ Intervals ------------------------------------------------------------------ -->

<script>

setInterval(function() {
	
	getGaugeConfig();

	getSensor1();
	getSensor1min();
	getSensor1max();
	getSensor1low();
	getSensor1high();
	
	getSensor2();
	getSensor2min();
	getSensor2max();
	getSensor2low();
	getSensor2high();
	
		getSensor3();
	getSensor3min();
	getSensor3max();
	getSensor3low();
	getSensor3high();
	
		getSensor4();
	getSensor4min();
	getSensor4max();
	getSensor4low();
	getSensor4high();
	
		getSensor5();
	getSensor5min();
	getSensor5max();
	getSensor5low();
	getSensor5high();
	
		getSensor6();
	getSensor6min();
	getSensor6max();
	getSensor6low();
	getSensor6high();
	
		getSensor7();
	getSensor7min();
	getSensor7max();
	getSensor7low();
	getSensor7high();
	
		getSensor8();
	getSensor8min();
	getSensor8max();
	getSensor8low();
	getSensor8high();
	
		getSensor9();
	getSensor9min();
	getSensor9max();
	getSensor9low();
	getSensor9high();
	
		getSensor10();
	getSensor10min();
	getSensor10max();
	getSensor10low();
	getSensor10high();

	
	
}, 1000); 


<!-- ------------------------------------------------------------------ Functions Sensor 1 ------------------------------------------------------------------ -->

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

function getSensor1min() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("currentSensor1min").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "sensor1min", true);
  xhttp.send();
}

function getSensor1max() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("currentSensor1max").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "sensor1max", true);
  xhttp.send();
}

function getSensor1low() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("currentSensor1low").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "sensor1low", true);
  xhttp.send();
}

function getSensor1high() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("currentSensor1high").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "sensor1high", true);
  xhttp.send();
}

<!-- ------------------------------------------------------------------ Functions Sensor 2 ------------------------------------------------------------------ -->

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

function getSensor2min() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("currentSensor2min").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "sensor2min", true);
  xhttp.send();
}

function getSensor2max() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("currentSensor2max").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "sensor2max", true);
  xhttp.send();
}

function getSensor2low() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("currentSensor2low").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "sensor2low", true);
  xhttp.send();
}

function getSensor2high() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("currentSensor2high").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "sensor2high", true);
  xhttp.send();
}

<!-- ------------------------------------------------------------------ Functions Sensor 3 ------------------------------------------------------------------ -->

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

function getSensor3min() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("currentSensor3min").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "sensor3min", true);
  xhttp.send();
}

function getSensor3max() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("currentSensor3max").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "sensor3max", true);
  xhttp.send();
}

function getSensor3low() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("currentSensor3low").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "sensor3low", true);
  xhttp.send();
}

function getSensor3high() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("currentSensor3high").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "sensor3high", true);
  xhttp.send();
}

<!-- ------------------------------------------------------------------ Functions Sensor 4 ------------------------------------------------------------------ -->

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

function getSensor4min() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("currentSensor4min").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "sensor4min", true);
  xhttp.send();
}

function getSensor4max() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("currentSensor4max").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "sensor4max", true);
  xhttp.send();
}

function getSensor4low() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("currentSensor4low").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "sensor4low", true);
  xhttp.send();
}

function getSensor4high() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("currentSensor4high").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "sensor4high", true);
  xhttp.send();
}

<!-- ------------------------------------------------------------------ Functions Sensor 5 ------------------------------------------------------------------ -->

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

function getSensor5min() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("currentSensor5min").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "sensor5min", true);
  xhttp.send();
}

function getSensor5max() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("currentSensor5max").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "sensor5max", true);
  xhttp.send();
}

function getSensor5low() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("currentSensor5low").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "sensor5low", true);
  xhttp.send();
}

function getSensor5high() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("currentSensor5high").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "sensor5high", true);
  xhttp.send();
}

<!-- ------------------------------------------------------------------ Functions Sensor 6 ------------------------------------------------------------------ -->

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

function getSensor6min() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("currentSensor6min").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "sensor6min", true);
  xhttp.send();
}

function getSensor6max() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("currentSensor6max").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "sensor6max", true);
  xhttp.send();
}

function getSensor6low() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("currentSensor6low").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "sensor6low", true);
  xhttp.send();
}

function getSensor6high() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("currentSensor6high").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "sensor6high", true);
  xhttp.send();
}

<!-- ------------------------------------------------------------------ Functions Sensor 7 ------------------------------------------------------------------ -->

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

function getSensor7min() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("currentSensor7min").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "sensor7min", true);
  xhttp.send();
}

function getSensor7max() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("currentSensor7max").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "sensor7max", true);
  xhttp.send();
}

function getSensor7low() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("currentSensor7low").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "sensor7low", true);
  xhttp.send();
}

function getSensor7high() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("currentSensor7high").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "sensor7high", true);
  xhttp.send();
}

<!-- ------------------------------------------------------------------ Functions Sensor 8 ------------------------------------------------------------------ -->

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

function getSensor8min() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("currentSensor8min").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "sensor8min", true);
  xhttp.send();
}

function getSensor8max() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("currentSensor8max").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "sensor8max", true);
  xhttp.send();
}

function getSensor8low() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("currentSensor8low").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "sensor8low", true);
  xhttp.send();
}

function getSensor8high() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("currentSensor8high").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "sensor8high", true);
  xhttp.send();
}

<!-- ------------------------------------------------------------------ Functions Sensor 9 ------------------------------------------------------------------ -->

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

function getSensor9min() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("currentSensor9min").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "sensor9min", true);
  xhttp.send();
}

function getSensor9max() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("currentSensor9max").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "sensor9max", true);
  xhttp.send();
}

function getSensor9low() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("currentSensor9low").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "sensor9low", true);
  xhttp.send();
}

function getSensor9high() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("currentSensor9high").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "sensor9high", true);
  xhttp.send();
}

<!-- ------------------------------------------------------------------ Functions Sensor 10 ------------------------------------------------------------------ -->

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

function getSensor10min() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("currentSensor10min").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "sensor10min", true);
  xhttp.send();
}

function getSensor10max() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("currentSensor10max").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "sensor10max", true);
  xhttp.send();
}

function getSensor10low() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("currentSensor10low").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "sensor10low", true);
  xhttp.send();
}

function getSensor10high() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("currentSensor10high").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "sensor10high", true);
  xhttp.send();
}

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



</script>

</body>
</html>
)=====";
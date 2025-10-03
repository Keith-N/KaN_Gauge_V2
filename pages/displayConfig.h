const char displayConfigPage[] PROGMEM = R"=====(
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
  
  <title> Display Configuration </title>

</head>
<body>

  <script type="text/javascript">
      function notify(message) {
          alert(message);
      }
  </script>
  
  <!-- ------------------------------------------------------------------ Set Alert Type ------------------------------------------------------------------ -->
  
<form action="/setAlertType">
  <p>Select Alert Type</p>
  <p1>Occurs when a displayed value exceeds Alert High/Low</p1>
  <h4>Alert : <span id = "cAlertType"></span></h4>
  <br>
  
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
  
  
  
  
    <!-- ------------------------------------------------------------------ Set Update Rate ------------------------------------------------------------------ -->
  
<form action="/setDisplayRate"> 
<p> Display Update Rate </p><br>
 <h4>Rate (ms) : <span id = "cDisplayRate"></span></h4>
  <label for="A"></label>
  <input type="text" id="A" name="A">
  <p1>ms</p1>
  <br>
  <input type="submit" value ="Set new value" onClick="notify('New value sent')">
  <br>
</form>
  
   <!-- ------------------------------------------------------------------ Set brightness ------------------------------------------------------------------ --> 
  <form action="/setBrightnessDisplay"> 
  <p>Set Brightness</p><br>
  <p1>Values from 0 to 100 Brightness based on Analog input </p1> 
  <h4>0V / Disconnected : <span id = "cDisplayLow"></span></h4>
  <h4>12V : <span id = "cDisplayHigh"></span></h4>
  
  <br> 
  
 
  <p1>Input 0V</p1>
  <label for="A"></label>
  <input type="text" id="A" name="A"><br>
  
  <p1>Input 12V</p1>
  <label for="B"></label>
  <input type="text" id="B" name="B"><br>
  
  
  <br>
  <input type="submit" value ="Set new value" onClick="notify('New limit sent')">
  <br>
</form>


  <!-- ------------------------------------------------------------------ Set Arcs ------------------------------------------------------------------ --> 



<form action="/setArc1"> 
  <p>Inner Arc Configuration</p>
  <p1> Color </p1>
  <h4>Current : <span id = "cInnerArcColor"> </span></h4>
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
  <h4>Current : <span id = "cInnerArcWidth"></span> </h4>
  <label for="B"></label>
  <input type="text" id="B" name="B"><br>
  <br>

  <p1>Segment Spacing</p1>
  <h4>Current : <span id = cInnerArcIncrement></span> </h4>
  <label for="C"></label>
  <input type="text" id="C" name="C"><br>
  
  <br>
  <input type="submit" value ="Set new value" onClick="notify('New config sent')">
  <br>
</form>

<form action="/setArc2"> 
  <p>Outer Arc Configuration</p>
  <p1>Color </p1>
  <h4>Current : <span id = "cOuterArcColor"> </span></h4>
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
  <h4>Current : <span id = "cOuterArcWidth"></span> </h4>
  <label for="B"></label>
  <input type="text" id="B" name="B"><br>
  <br>

  <p1>Segment Spacing</p1>
  <h4>Current : <span id = "cOuterArcIncrement"></span> </h4>
  <label for="C"></label>
  <input type="text" id="C" name="C"><br>
  
  <br>
  <input type="submit" value ="Set new value" onClick="notify('New config sent'')">
  <br>
</form>


  <!-- ------------------------------------------------------------------ Set Colors ------------------------------------------------------------------ --> 


<form action="/setTextColor"> 
  <p>Set Display Colors</p>
    <label for="A"></label>
    <select id="A" name="A">
    <option value="0">Value Digits</option>
    <option value="1">Unit Text</option>
    <option value="2">Alert Digits</option>
    <option value="3">Meter Needle</option>
	<option value="4"> Background </option>
    </select>

    <label for="B"></label>
    <select id="B" name="B">
    <option value="65535">White</option>
    <option value="2047">Cyan</option>
    <option value="31">Blue</option>
    <option value="65504">Yellow</option>
    <option value="60512">Orange</option>
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





<!-- ------------------------------------------------------------------ Back Button ------------------------------------------------------------------ -->


  <form action="/">
  <input type="submit" value = "Back">
  </form>
  
  
  <!-- ------------------------------------------------------------------ Intervals ------------------------------------------------------------------ -->

<script>

function getData() {
getAlertType();
getDisplayRate();
getDisplayLow();
getDisplayHigh();

getOuterArcWidth();
getOuterArcIncrement();
getOuterArcColor();

getInnerArcWidth();
getInnerArcIncrement();
getInnerArcColor();


}; 

getData();
  
  <!-- ------------------------------------------------------------------ Functions ------------------------------------------------------------------ -->

function getAlertType() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("cAlertType").innerHTML = this.responseText;
    }
  };

  xhttp.open("GET", "alertType", true);
  xhttp.send();
}

function getDisplayRate() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("cDisplayRate").innerHTML = this.responseText;
    }
  };

  xhttp.open("GET", "displayRate", true);
  xhttp.send();
}
  
function getDisplayLow() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("cDisplayLow").innerHTML = this.responseText;
    }
  };

  xhttp.open("GET", "displayLow", true);
  xhttp.send();
}

function getDisplayHigh() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("cDisplayHigh").innerHTML = this.responseText;
    }
  };

  xhttp.open("GET", "displayHigh", true);
  xhttp.send();
}


function getOuterArcWidth() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("cOuterArcWidth").innerHTML = this.responseText;
    }
  };

  xhttp.open("GET", "outerArcWidth", true);
  xhttp.send();
}


function getInnerArcWidth() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("cInnerArcWidth").innerHTML = this.responseText;
    }
  };

  xhttp.open("GET", "innerArcWidth", true);
  xhttp.send();
}

function getOuterArcIncrement() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("cOuterArcIncrement").innerHTML = this.responseText;
    }
  };

  xhttp.open("GET", "outerArcIncrement", true);
  xhttp.send();
}


function getInnerArcIncrement() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("cInnerArcIncrement").innerHTML = this.responseText;
    }
  };

  xhttp.open("GET", "innerArcIncrement", true);
  xhttp.send();
}

function getInnerArcColor() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("cInnerArcColor").innerHTML = this.responseText;
    }
  };

  xhttp.open("GET", "innerArcColor", true);
  xhttp.send();
}

function getOuterArcColor() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("cOuterArcColor").innerHTML = this.responseText;
    }
  };

  xhttp.open("GET", "outerArcColor", true);
  xhttp.send();
}
  
</script>
</body>
</html>
)=====";
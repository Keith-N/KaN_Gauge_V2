const char ledConfigPage[] PROGMEM = R"=====(
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
  
  <title> LED Configuration </title>

</head>

<body>

  <script type="text/javascript">
      function notify(message) {
          alert(message);
      }
  </script>
   
  
 <!-- ------------------------------------------------------------------ Set LEDs ------------------------------------------------------------------ --> 


<form action="/setLedColor"> 
  <p>Set LED Colors</p>
  <h4> Current : <span id = "cLedColor"></span></h4>
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
	<h4> Current : <span id = "cLedStyle"></span></h4>
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

   <!-- ------------------------------------------------------------------ Set brightness ------------------------------------------------------------------ --> 
  <form action="/setBrightnessLeds"> 
  <p>Set Brightness</p><br>
  <p1>Values from 0 to 100 Brightness based on Analog input </p1> <br>
  <h4> 0V / Disconnected : <span id = "cLedLow"></span></h4>
  <h4> 12V : <span id = "cLedHigh"></span></h4>
  
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

<form action="/setLEDCustom"> 
  <p>Set Custom LED Color</p>
  <p1>Values from 0 to 255</p1>
<br>
  
<p1> LED 1 </p1>
<h4> R : <span id="currentLed1"></span></h4>
  <label for="R1"></label>
  <input type="text" id="R1" name="R1">
<h4> G : <span id="currentLed2"></span></h4>
  <label for="G1"></label>
  <input type="text" id="G1" name="G1">

<h4> B : <span id="currentLed3"></span></h4>
  <label for="B1"></label>
  <input type="text" id="B1" name="B1"><br>

<p1> LED 2 </p1>
<h4> R : <span id="currentLed4"></span></h4>
  <label for="R2"></label>
  <input type="text" id="R2" name="R2">
<h4> G : <span id="currentLed5"></span></h4>
  <label for="G2"></label>
  <input type="text" id="G2" name="G2">
<h4> B : <span id="currentLed6"></span></h4>
  <label for="B2"></label>
  <input type="text" id="B2" name="B2"><br>

<p1> LED 3 </p1>
<h4> R : <span id="currentLed7"></span></h4>
  <label for="R3"></label>
  <input type="text" id="R3" name="R3">
<h4> G : <span id="currentLed8"></span></h4>
  <label for="G3"></label>
  <input type="text" id="G3" name="G3">
<h4> B : <span id="currentLed9"></span></h4>
  <label for="B3"></label>
  <input type="text" id="B3" name="B3"><br>

<p1> LED 4 </p1>
<h4> R : <span id="currentLed10"></span></h4>
  <label for="R4"></label>
  <input type="text" id="R4" name="R4">
<h4> G : <span id="currentLed11"></span></h4>
  <label for="G4"></label>
  <input type="text" id="G4" name="G4">
<h4> B : <span id="currentLed12"></span></h4>
  <label for="B4"></label>
  <input type="text" id="B4" name="B4"><br>

<p1> LED 5 </p1>
<h4> R : <span id="currentLed13"></span></h4>
  <label for="R5"></label>
  <input type="text" id="R5" name="R5">
<h4> G : <span id="currentLed14"></span></h4>
  <label for="G5"></label>
  <input type="text" id="G5" name="G5">
<h4> B : <span id="currentLed15"></span></h4>
  <label for="B5"></label>
  <input type="text" id="B5" name="B5"><br>

<p1> LED 6 </p1>
<h4> R : <span id="currentLed16"></span></h4>
  <label for="R6"></label>
  <input type="text" id="R6" name="R6"><br>
<h4> G : <span id="currentLed17"></span></h4>
  <label for="G6"></label>
  <input type="text" id="G6" name="G6"><br>
<h4> B : <span id="currentLed18"></span></h4>
  <label for="B6"></label>
  <input type="text" id="B6" name="B6"><br>
  <br>
  <input type="submit" value ="Set new value" onClick="notify('New limit sent')">
</form>

<!-- ------------------------------------------------------------------ Back Button ------------------------------------------------------------------ -->

  <form action="/">
  <input type="submit" value = "Back">
  </form>

<!-- ------------------------------------------------------------------ Intervals ------------------------------------------------------------------ -->

<script>

function getData() {
	getLedColor();
	getLedStyle();
	getLedLow();
	getLedHigh();

	getLed1();
	getLed2();
	getLed3();
	getLed4();
	getLed5();
	getLed6();
	getLed7();
	getLed8();
	getLed9();
	getLed10();
	getLed11();
	getLed12();
	getLed13();
	getLed14();
	getLed15();
	getLed16();
	getLed17();
	getLed18();
	
}; 

getData();

  
<!-- ------------------------------------------------------------------ Functions ------------------------------------------------------------------ -->
  

  
  function getLedLow() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("cLedLow").innerHTML = this.responseText;
    }
  };

  xhttp.open("GET", "ledLow", true);
  xhttp.send();
}

function getLedHigh() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("cLedHigh").innerHTML = this.responseText;
    }
  };

  xhttp.open("GET", "ledHigh", true);
  xhttp.send();
}
  
  
  function getLedColor() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("cLedColor").innerHTML = this.responseText;
    }
  };

  xhttp.open("GET", "ledColor", true);
  xhttp.send();
}
  
  
    function getLedStyle() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("cLedStyle").innerHTML = this.responseText;
    }
  };

  xhttp.open("GET", "ledStyle", true);
  xhttp.send();
}
  
  

function getLed1() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("currentLed1").innerHTML = this.responseText;
    }
  };

  xhttp.open("GET", "led1", true);
  xhttp.send();
}

function getLed2() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("currentLed2").innerHTML = this.responseText;
    }
  };

  xhttp.open("GET", "led2", true);
  xhttp.send();
}

function getLed3() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("currentLed3").innerHTML = this.responseText;
    }
  };

  xhttp.open("GET", "led3", true);
  xhttp.send();
}

function getLed4() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("currentLed4").innerHTML = this.responseText;
    }
  };

  xhttp.open("GET", "led4", true);
  xhttp.send();
}

function getLed5() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("currentLed5").innerHTML = this.responseText;
    }
  };

  xhttp.open("GET", "led5", true);
  xhttp.send();
}

function getLed6() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("currentLed6").innerHTML = this.responseText;
    }
  };

  xhttp.open("GET", "led6", true);
  xhttp.send();
}

function getLed7() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("currentLed7").innerHTML = this.responseText;
    }
  };

  xhttp.open("GET", "led7", true);
  xhttp.send();
}

function getLed8() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("currentLed8").innerHTML = this.responseText;
    }
  };

  xhttp.open("GET", "led8", true);
  xhttp.send();
}

function getLed9() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("currentLed9").innerHTML = this.responseText;
    }
  };

  xhttp.open("GET", "led9", true);
  xhttp.send();
}

function getLed10() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("currentLed10").innerHTML = this.responseText;
    }
  };

  xhttp.open("GET", "led10", true);
  xhttp.send();
}


function getLed11() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("currentLed11").innerHTML = this.responseText;
    }
  };

  xhttp.open("GET", "led11", true);
  xhttp.send();
}

function getLed12() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("currentLed12").innerHTML = this.responseText;
    }
  };

  xhttp.open("GET", "led12", true);
  xhttp.send();
}

function getLed13() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("currentLed13").innerHTML = this.responseText;
    }
  };

  xhttp.open("GET", "led13", true);
  xhttp.send();
}

function getLed14() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("currentLed14").innerHTML = this.responseText;
    }
  };

  xhttp.open("GET", "led14", true);
  xhttp.send();
}

function getLed15() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("currentLed15").innerHTML = this.responseText;
    }
  };

  xhttp.open("GET", "led15", true);
  xhttp.send();
}

function getLed16() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("currentLed16").innerHTML = this.responseText;
    }
  };

  xhttp.open("GET", "led16", true);
  xhttp.send();
}

function getLed17() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("currentLed17").innerHTML = this.responseText;
    }
  };

  xhttp.open("GET", "led17", true);
  xhttp.send();
}

function getLed18() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("currentLed18").innerHTML = this.responseText;
    }
  };

  xhttp.open("GET", "led18", true);
  xhttp.send();
}
  
</script>
</body>
</html>
)=====";
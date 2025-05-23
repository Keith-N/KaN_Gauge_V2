
/*
 *
 * Boot Config
 *
 *
 */
const char bootConfigPage[] PROGMEM = R"=====(
<!DOCTYPE html>
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

 
<!-- ------------------------------------------------------------------ Page ------------------------------------------------------------------ -->
 

	
<head>
  <title> Boot Configuration </title>
</head>


<form action="/bootConfig"> 
  <p>Boot 1</p>
  <h4>Current : <span id = "currentBoot1"></span></h4>
    <label for="A"></label>
    <select id="A" name="A">
    <option value="0">KaN</option>
    <option value="1">BMM</option>
    <option value="2">FOME</option>
    <option value="3">Mazda</option>

    </select>
  <br><br>

  <p>Boot 2</p>
  <h4>Current : <span id = "currentBoot2"></span></h4>
    <label for="B"></label>
    <select id="B" name="B">
    <option value="0">KaN</option>
    <option value="1">BMM</option>
    <option value="2">FOME</option>
    <option value="3">Mazda</option>

    </select>
<br><br>

  <p>Boot 3</p>
  <h4>Current : <span id = "currentBoot3"></span></h4>
    <label for="C"></label>
    <select id="C" name="C">
    <option value="0">KaN</option>
    <option value="1">BMM</option>
    <option value="2">FOME</option>
    <option value="3">Mazda</option>

    </select>
<br><br>

  <p>Logo Print Level</p>
  <h4>Current : <span id = "currentBootLevel"></span></h4>
    <label for="D"></label>
    <select id="D" name="D">
    <option value="0">3 Logo</option>
    <option value="1">2 Logo</option>
    <option value="2">1 Logo</option>
    <option value="3">Skip</option>
    </select>
<br><br>


  <p>Logo Time ms</p>
  <h4>Current : <span id = "currentBootTime"></span></h4>
  <label for="E"></label>
  <input type="text" id="E" name="E"><br>
  
  <br>
  <input type="submit" value ="Set Config" onClick="notify('New config sent')">
  <br>

</form>


<!-- ------------------------------------------------------------------ Back Button ------------------------------------------------------------------ -->
    <form action='/'>
    </button>
    <input type='submit' value = 'Back'>
    </form>


<!-- ------------------------------------------------------------------ Function ------------------------------------------------------------------ -->
<script>

function getData() {
getBoot1();
getBoot2();
getBoot3();
getBootTime();
getBootLevel();	
};
getData();


<!-- ------------------------------------------------------------------ Functions ------------------------------------------------------------------ -->

function getTest() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("displayTest").innerHTML = this.responseText;
    }
  };

  xhttp.open("GET", "testValue", true);
  xhttp.send();
}






function getBoot1() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("currentBoot1").innerHTML = this.responseText;
    }
  };

  xhttp.open("GET", "boot1", true);
  xhttp.send();
}


function getBoot2() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("currentBoot2").innerHTML = this.responseText;
    }
  };

  xhttp.open("GET", "boot2", true);
  xhttp.send();
}


function getBoot3() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("currentBoot3").innerHTML = this.responseText;
    }
  };

  xhttp.open("GET", "boot3", true);
  xhttp.send();
}



function getBootLevel() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("currentBootLevel").innerHTML = this.responseText;
    }
  };

  xhttp.open("GET", "bootLevel", true);
  xhttp.send();
}




function getBootTime() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("currentBootTime").innerHTML = this.responseText;
    }
  };

  xhttp.open("GET", "bootTime", true);
  xhttp.send();
}










</script>
</body>
</html>
)=====";

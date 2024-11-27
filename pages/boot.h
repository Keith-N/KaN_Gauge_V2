
/*
 *
 * Boot Config
 *
 *
 */

const char bootConfigPage[] = R"rawliteral(
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
  
  <title> config</title>

</head>
<body>


  <script type="text/javascript">
      function notify(message) {
          alert(message);
      }
  </script>

  <h1 style="color:white;">Boot Configuration</h1>
  <h4 style="color:white;"></h4>
  


<form action="/boot"> 

  <p>Boot 1</p>
    <label for="A"></label>
    <select id="A" name="A">
    <option value="0">KaN</option>
    <option value="1">BMM</option>
    <option value="2">FOME</option>
    <option value="3">Mazda</option>
    <option value="4">Custom</option>
    </select>
  <br>
  <br>
  <p>Boot 2</p>
    <label for="B"></label>
    <select id="B" name="B">
    <option value="0">KaN</option>
    <option value="1">BMM</option>
    <option value="2">FOME</option>
    <option value="3">Mazda</option>
    <option value="4">Custom</option>
    </select>
<br>
<br>
  <p>Boot 3</p>
    <label for="B"></label>
    <select id="B" name="B">
    <option value="0">KaN</option>
    <option value="1">BMM</option>
    <option value="2">FOME</option>
    <option value="3">Mazda</option>
    <option value="4">Custom</option>
    </select>
<br>
<br>
  <p>Board Rev</p>
  <label for="D"></label>
  <input type="text" id="D" name="D"><br>

  <p>Logo Print Level</p>
    <label for="B"></label>
    <select id="B" name="B">
    <option value="0">All</option>
    <option value="1">2</option>
    <option value="2">1</option>
    <option value="3">NONE</option>
    </select>
<br>
<br>

  <p>Logo Time ms</p>
  <label for="F"></label>
  <input type="text" id="D" name="D"><br>
  
  <br>
  <input type="submit" value ="Set Config" onClick="notify('New config sent')">
  <br>

</form>

  <form action="/">
  <input type="submit" value = "Back">
  </form>

</body>
</html>
)rawliteral";
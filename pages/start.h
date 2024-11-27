/*

   Start Page

   Initial page on connection to /
   Go to update and configuration pages

*/

const char startPage[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>

<meta name="viewport" content="width=device-width, initial-scale=1">
<style>
input{background:#f1f1f1;border:0;padding:0 15px}
body{background:#cc8943;font-family:sans-serif;font-size:14px;color:#777}
#file-input,input{width: 100%;height:44px;border-radius:4px;margin:10px auto;font-size:15px}
#file-input{padding:0 10px;box-sizing:border-box;border:1px solid #ddd;line-height:44px;text-align:left;display:block;cursor:pointer; white-space: nowrap; overflow: hidden; text-overflow: ellipsis;}
#bar,#prgbar{background-color:#f1f1f1;border-radius:10px}#bar{background-color:#cc8943;width:0%;height:10px;}
form{background:#fff;max-width:258px;margin:75px auto;padding:35px; padding-bottom: 30px;border: 1px solid #cc8943;border-radius:5px;text-align:center}
.btn {background-color: #cc8943;box-shadow: 0 0 8px 0 rgba(0, 0, 0, 0.08), 0 0 15px 0 rgba(0, 0, 0, 0.02), 0 0 20px 4px rgba(0, 0, 0, 0.06);color: white;border-radius: 4px;padding: 9px 16px;background-image: none;
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

     h1 { font-size: 2.0rem; 
       font-family: Arial;
      text-align: center;
      font-weight: normal;
      color: #fafcfc;
     }
    
    h2 { font-size: 2.0rem; 
       font-family: Arial;
      text-align: center;
      font-weight: normal;
      color: #fafcfc;
     }
    p { font-size: 3.0rem; margin-top: 0;}
    .units { font-size: 1.2rem; }
    .dht-labels{
      font-size: 1.5rem;
      vertical-align:middle;
      padding-bottom: 15px;
      font-weight: normal;
      color: #333333;
    }
</style>
<head>

  
<title> KaN Gauge </title>


</head>

<body>


  <script type="text/javascript">
      function showMessage(message) {
          alert(message);
      }
  </script>

  <img src="  data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAALkAAABQCAYAAABF5tQWAAAABGdBTUEAALGPC/xhBQAAAYVpQ0NQSUNDIHByb2ZpbGUAACiRfZE9SMNQFIVPU6UiLRXsIOKQoTpZEBVxlCoWwUJpK7TqYPLSP2jSkKS4OAquBQd/FqsOLs66OrgKguAPiLODk6KLlHhfUmgR44XH+zjvnsN79wFCs8pUs2cCUDXLSCfiYi6/KgZe4UMIAwgjJDFTT2YWs/Csr3vqprqL8Szvvj8rpBRMBvhE4jmmGxbxBvHMpqVz3ieOsLKkEJ8Tjxt0QeJHrssuv3EuOSzwzIiRTc8TR4jFUhfLXczKhko8TRxVVI3yhZzLCuctzmq1ztr35C8MFrSVDNdpjSCBJSSRgggZdVRQhYUY7RopJtJ0HvfwDzv+FLlkclXAyLGAGlRIjh/8D37P1ixOTbpJwTjQ+2LbH6NAYBdoNWz7+9i2WyeA/xm40jr+WhOY/SS90dGiR0B4G7i47mjyHnC5Aww96ZIhOZKfllAsAu9n9E15YPAW6F9z59Y+x+kDkKVZLd8AB4fAWImy1z3e3dc9t3972vP7ASVScohSH37aAAAABmJLR0QAAAAAAAD5Q7t/AAAACXBIWXMAAAsTAAALEwEAmpwYAAAAB3RJTUUH6AENEBwoNi2U9QAABURJREFUeNrtnU9v3EQYxp/xerfrVEpLS5gARw5VDgiJAwp/FLUSVyREL0WKBaKoEkR74cAXQD0jRdz4Dty48QE4wpFDqlWUij+VVq1UitIA5pKgjrNOxva8Y8/4+R1fTcbv2o9fPzMeTwBCCCGEEEIIIYQQQgghZLiorg5cFEUh+sOUUsyfdCJyaXFIiyX0/Cly3wK3vX4nf1a3vWOhhJ7/UEm7ubWUn/ZSRTf0/FnJPVTx44toe/CiZrLFkorYthqGnv+QSbqq4qrmnaia3LkSugg9f9qVePE9YCQUeVmAVTMLTtozf4p8IKMP1VbJVAtFHqm46Y8p8r5agsrBXNPjUyvBkgzhR6qe9EEocndVn9eVhGJXas9atOiz2oqrU9W8aJA/Z05YyV3fHaKzIZQrRd6tReFUHwnJrriyKDb9VNkMV5aDL1wpcjcWhZCoRf7s8lQO8kiIIq+yDWfNeKiObcOzedKucODZXlClis5aTuKzK5HDpcLnPjVVkCKvetzXtS6ulsLSuvS7CFQJPcpKHp1VWSyA+dyMZRmgdb34ugb2S/Hpcfv7p+NHWuPwgRkfTTKkVzX+emzGkzRDsqLx6E8zno4yTMcaf5TaT0YZLmUavz8sxdMMq89r7P9rxqfI8EKyPH5ttEG7Ejx7e8Dmphnb2QHyvF784xz44g0z/vYMuJUD35Ti12Z4+n6OxQ9vGuHx2udYeSfHb3tm+wsXZ5i8nOOng7eM+Or0M+jLOb7/xWy/fnGG19dzfPezmedLqzt49UqOL4/M9ptqhg/S5fGvRrtxiLyudan7tyRiv+594LRk9sPn52NthO0qH5v2XKbgbvAZ7XpySoMC71Ullxa5Cvkm/f+08TVuUxKeAkKRuy/pte1E0aB902NJ5dMmf9IOb7MrSilVfmtXNBBXn7y+r/xpVVpqz28R97grbKmtEhB53adX011tfQzWJJYNSPTf5IaPd3/yMwa4bb7zpKXoSXWuIfY4/9PEOTM4LkS+VOgSu3R52gPdSf7S/Tfctz0qr2c7Telc5BKDc182XPpYEv3XnFYd0q629QTc4DtPiV26xPdAF6p4hYfzc1LUzhO7shRIWMbT09IBiRdOPl9iSR9L9PzUsC5JdAInQxl5Wtsga7uyWBxhPj80YlmWYF1PcDA/MuLTTGFNpziYPy3FE7yox1iU2o8zhTUN/D1/Yv6OLMFEF8D8VzOZ7AKgLy9fM72x4Wr07twa2RxL+sMPZTG16nIRm/J3ftp/NLF37xDXbz4wYp/eHOOTD6/g7o1HRvy12yne217B11sPjfjGnRS3ti/hx63HRvy5OyNsbRd4cmPfiI9uTzHJ/wHe/dZM5qNXgO3N5Wumd3fjKFQRHEMJ912cVPRzbhquXSHxO5soPXnDgafNT3U18JReQz+E9rYrNROLi8p1EyRorDx5KELnTBBpNfAchHdrsG1E17t0hY6Pc8WBZ49nJwhFTgjtSh8euz536ZKwatJ5+hjusZIT2hUS8dMnhtxt3m1EZhlE1pPXfbz2rX+b9fDSL7Nc5V+c7uykTZi72hJyxp0ycLsitBWF78d9EXDuPu2Qk48mQrYskj806I8OzhBCH+yQrRe3eRsf78BT+B/W8vyEQ3QiP3VnC+6iFVr/PrfR6FP+cf6niWOht92xa0ge3cZ+tM2xELrOgxR55Uhcal+RUPr3aU96lL+KX9805hYl0YkYfNqhIHbQikHsoe8lWDUT5aqKD3YvRNLjG7+jbdzEqz4vNYXetZ2gyElQYuc3wYQQQgghhBBCCCGEEEJIv/gP/oKXuRRPBJAAAAAASUVORK5CYII=">

<form action="/gaugeConfiguration">
<input type="submit" value = "Gauge Configuration">
</form>

<form action="/sensorConfiguration">
<input type="submit" value = "Sensor Limit Configuration">
</form>

<form action="/displayConfiguration">
<input type="submit" value = "Display Configuration">
</form>

<form action="/ledConfiguration">
<input type="submit" value = "LED Configuration">
</form>

<form action="/updateStart">
<input type="submit" value = "Update Firmware">
</form>

<form action="/wifiConfig">
<input type="submit" value = "Configure WiFi">
</form>

<form action="/boot">
<input type="submit" value = "Configure Boot">
</form>

<form action="/reset">
<input type="submit" value = "Restart Gauge">
</form>

<form action="/resetDefaults">
<input type="submit" value = "Reset Gauge to Default Values">
</form>

<button>
<a href="https://github.com/Keith-N/KaN_Gauge_V2/wiki" target="_blank" >GitHub</a>
</button>
<br>
<button>
<a href="https://github.com/Keith-N/KaN_Gauge_V2/releases" target="_blank">Firmware Releases</a>
</button>
<br>
<button>
<a href="https://github.com/Keith-N/KaN_Gauge_V2/wiki/Gauge-Types" target="_blank">Gauge Types</a>
</button>


</body>
</html> 
)rawliteral";
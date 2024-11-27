const char updatePage[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>

    <style>#file-input,input{width:100%;height:44px;border-radius:4px;margin:10px auto;font-size:15px}
    input{background:#f1f1f1;border:0;padding:0 15px}body{background:#cc8943;font-family:sans-serif;font-size:14px;color:#777}
    #file-input{padding:0;border:1px solid #ddd;line-height:44px;text-align:left;display:block;cursor:pointer}
    #bar,#prgbar{background-color:#f1f1f1;border-radius:10px}#bar{background-color:#3498db;width:0%;height:10px}
    form{background:#fff;max-width:258px;margin:75px auto;padding:30px;border-radius:5px;text-align:center}
    .btn{background:#3498db;color:#fff;cursor:pointer}</style>;

 
<!-- ------------------------------------------------------------------ Update ------------------------------------------------------------------ -->
 
    <script src='/jquery.min.js'></script> 
    <form method='POST' action='#' enctype='multipart/form-data' id='upload_form'>
    <input type='file' name='update' id='file' onchange='sub(this)' style=display:none>
    <label id='file-input' for='file'>   Choose .bin file...</label>
    <input type='submit' class=btn value='Update'>
    <br><br>
    <div id='prg'></div>
    <br><div id='prgbar'><div id='bar'></div></div><br></form>
    <script>
    function sub(obj){
    var fileName = obj.value.split('\\\\');
    document.getElementById('file-input').innerHTML = '   '+ fileName[fileName.length-1];
    };
    $('form').submit(function(e){
    e.preventDefault();
    var form = $('#upload_form')[0];
    var data = new FormData(form);
    $.ajax({
    url: '/update',
    type: 'POST',
    data: data,
    contentType: false,
    processData:false,
    xhr: function() {
    var xhr = new window.XMLHttpRequest();
    xhr.upload.addEventListener('progress', function(evt) {
    if (evt.lengthComputable) {
    var per = evt.loaded / evt.total;
    $('#prg').html('progress: ' + Math.round(per*100) + '%');
    $('#bar').css('width',Math.round(per*100) + '%');
    }
    }, false);
    return xhr; 
    },
    success:function(d, s) {
    console.log('success!') 
    },
    error: function (a, b, c) {
    }
    });
    });
    </script>
    </form>
	
	
<head>
  <title> Gauge Update </title>
</head>


<!-- ------------------------------------------------------------------ Back Button ------------------------------------------------------------------ -->
    <form action='/'>
	<h2> Gauge Information </h4>
    <h4>Hardware: <span id="displayHardware"></span></h4>
    <h4>Software: <span id="displayVersion"></span></h4>
    <h4><span id="displayNote"></span></h4><br>
    <button>
    <a href='https://github.com/Keith-N/KaN_Gauge_V2/releases' target='_blank'>Firmware Releases</a>
    </button>
    <input type='submit' value = 'Back'>
    </form>


<!-- ------------------------------------------------------------------ Intervals ------------------------------------------------------------------ -->
<script>

setInterval(function() {
  // Call a function repetatively with 2 Second interval
  getVersion();
  getNote();
  getHardware();
}, 1000); //2000mSeconds update rate


<!-- ------------------------------------------------------------------ Functions ------------------------------------------------------------------ -->

function getVersion() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("displayVersion").innerHTML = this.responseText;
    }
  };

  xhttp.open("GET", "version", true);
  xhttp.send();
}

function getNote() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("displayNote").innerHTML = this.responseText;
    }
  };
  
  xhttp.open("GET", "note", true);
  xhttp.send();
}

function getHardware() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("displayHardware").innerHTML = this.responseText;
    }
  };
  
  xhttp.open("GET", "hardware", true);
  xhttp.send();
}

</script>
</body>
</html>
)=====";

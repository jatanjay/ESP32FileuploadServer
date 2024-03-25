const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">

  <head>
    <meta name="viewport" content="width=device-width,initial-scale=1">
    <meta charset="UTF-8">
    <title>Retia</title>
    <style>
    body{
    background-color:#f4f4f4;
    display:flex;
    flex-direction:column;
    font-family:Arial,sans-serif;
    line-height:1.6;
    margin:0;
    min-height:100vh;
    overflow-x:hidden;
    padding-bottom:10px
}
button{
    border:none;
    border-radius:5px;
    color:#fff;
    cursor:pointer;
    margin:5px;
    padding:10px 20px
}
p{
    color:#4d4d4d;
    font-size:small;
    margin:8px 0
}
.container{
    background-color:#f9f9f9;
    border:1px solid #ccc;
    border-radius:10px;
    box-shadow:0 8px 15px #00000014;
    flex:1;
    margin:0 auto;
    max-width:90%;
    padding:2.5%;
    text-align:center
}
.banner,.footer{
    padding:10px;
    text-align:center
}
.banner{
    background-color:#04263d;
    color:#fff
}
input,select{
    box-sizing:border-box;
    margin-bottom:10px;
    padding:8px;
    width:100%
}
.footer{
    background:#111;
    color:#888
}
.button-success{
    background:#1cb841
}
.button-error{
    background:#ca3c3c
}
 
    </style>
  </head>

  <body>
    <div class="banner">
      <h3 class="banner-head">Retia CP200</h3>

      <a href="#" id="openModal">
        <svg width="35" height="35" viewBox="0 0 24 24" fill="none">
          <path fill-rule="evenodd" clip-rule="evenodd" d="M12 19.5C16.1421 19.5 19.5 16.1421 19.5 12C19.5 7.85786 16.1421 4.5 12 4.5C7.85786 4.5 4.5 7.85786 4.5 12C4.5 16.1421 7.85786 19.5 12 19.5ZM12 21C16.9706 21 21 16.9706 21 12C21 7.02944 16.9706 3 12 3C7.02944 3 3 7.02944 3 12C3 16.9706 7.02944 21 12 21ZM12.75 15V16.5H11.25V15H12.75ZM10.5 10.4318C10.5 9.66263 11.1497 9 12 9C12.8503 9 13.5 9.66263 13.5 10.4318C13.5 10.739 13.3151 11.1031 12.9076 11.5159C12.5126 11.9161 12.0104 12.2593 11.5928 12.5292L11.25 12.7509V14.25H12.75V13.5623C13.1312 13.303 13.5828 12.9671 13.9752 12.5696C14.4818 12.0564 15 11.3296 15 10.4318C15 8.79103 13.6349 7.5 12 7.5C10.3651 7.5 9 8.79103 9 10.4318H10.5Z" fill="#ffffff" />
        </svg>
      </a>


      <a href="/upload">
        <svg width="35" height="35" viewBox="0 0 24 24" fill="none">
          <g id="SVGRepo_bgCarrier" stroke-width="0"></g>
          <g id="SVGRepo_tracerCarrier" stroke-linecap="round" stroke-linejoin="round"></g>
          <g id="SVGRepo_iconCarrier">
            <path fill-rule="evenodd" clip-rule="evenodd" d="M8 10C8 7.79086 9.79086 6 12 6C14.2091 6 16 7.79086 16 10V11H17C18.933 11 20.5 12.567 20.5 14.5C20.5 16.433 18.933 18 17 18H16C15.4477 18 15 18.4477 15 19C15 19.5523 15.4477 20 16 20H17C20.0376 20 22.5 17.5376 22.5 14.5C22.5 11.7793 20.5245 9.51997 17.9296 9.07824C17.4862 6.20213 15.0003 4 12 4C8.99974 4 6.51381 6.20213 6.07036 9.07824C3.47551 9.51997 1.5 11.7793 1.5 14.5C1.5 17.5376 3.96243 20 7 20H8C8.55228 20 9 19.5523 9 19C9 18.4477 8.55228 18 8 18H7C5.067 18 3.5 16.433 3.5 14.5C3.5 12.567 5.067 11 7 11H8V10ZM15.7071 13.2929L12.7071 10.2929C12.3166 9.90237 11.6834 9.90237 11.2929 10.2929L8.29289 13.2929C7.90237 13.6834 7.90237 14.3166 8.29289 14.7071C8.68342 15.0976 9.31658 15.0976 9.70711 14.7071L11 13.4142V19C11 19.5523 11.4477 20 12 20C12.5523 20 13 19.5523 13 19V13.4142L14.2929 14.7071C14.6834 15.0976 15.3166 15.0976 15.7071 14.7071C16.0976 14.3166 16.0976 13.6834 15.7071 13.2929Z" fill="#ffffff"></path>
          </g>
        </svg>
      </a>



    </div>
    <div class="container">
      <form class="form-dropdown">
        <label for="waveform-type">Waveform</label>
        <select id="waveform-type" class="select-dropdown" required>
          <option value="" disabled selected>Select File</option>
        </select>
      </form>
      <button type="button" class="button-success" id="onButton">On</button>
      <button type="button" class="button-error" id="offButton">Off</button>
      <form method="POST" action="/format" target="/">
            <table><tr><td id="first_td_th">
            <p id="format_notice">Pressing the 'Format' button will immediately delete all data from SPIFFS!</p>
            </td><td>
            <input type="submit" id="submit" value="Format">
            </td></tr></table>
          </form>

    </div>
    <div class="footer">
      <p>© v.1.0.0 2024 <a href="https://www.quiretech.net/">QuireTech LLC</a></p>
    </div>
  </body>

</html>)rawliteral"; 

const char logout_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
  <head>
    <meta name="viewport" content="width=device-width, initial-scale=1" />
    <meta charset="UTF-8" />
  </head>
  <body>
    <p>
      <a href="/">Log Back In</a>
    </p>
  </body>
</html>
)rawliteral"; 


const char reboot_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="UTF-8" />
  </head>
  <body>
    <h3>
      Rebooting, returning to main page in
      <span id="countdown">30</span> seconds
    </h3>
    <script type="text/javascript">
      var seconds = 2;

      function countdown() {
          seconds = seconds - 1;
          if (seconds < 0) {
              window.location = "/";
          } else {
              document.getElementById("countdown").innerHTML = seconds;
              window.setTimeout("countdown()", 1000);
          }
      }
      countdown();
    </script>
  </body>
</html>
)rawliteral";



const char upload_html[] PROGMEM = R"rawliteral(
  <!DOCTYPE html>
<html lang="en">

  <head>
    <meta name="viewport" content="width=device-width,initial-scale=1">
    <meta charset="UTF-8">
    <title>Retia</title>
    <style>
    body{background-color:#f4f4f4;display:flex;flex-direction:column;font-family:Arial,sans-serif;line-height:1.6;margin-bottom:auto;min-height:100vh;overflow:hidden;padding-bottom:10px}.button-upload{background-color:#007bff;border:none;border-radius:5px;color:#fff;cursor:pointer;margin:5px;padding:10px 20px}.banner,.container,.footer{padding:10px;text-align:center}.banner{background-color:#04263d;color:#fff}.container{background-color:#f9f9f9;border:1px solid #ccc;border-radius:10px;box-shadow:0 8px 15px #0003;flex:1;margin:0 auto;max-width:90%}.footer{background:#111;color:#888;margin-top:auto}
    </style>
  </head>

  <body>
    <div class="banner">
      <h3 class="banner-head">Retia CP200</h3>
    </div>
    <div class="container">
      <div class="upload-box">
        <p><button type="button" class="button-upload" onclick="listFilesButton()">Files</button></p>
        <p><button type="button" class="button-upload" onclick="showUploadButtonFancy()">Upload</button></p>
        <p id="status"></p>
        <p id="detailsheader"></p>
        <p id="details"></p>
      </div>
    </div>
    <div class="footer">
      <p>© v.1.0.0 2024 <a href="https://www.quiretech.net/">QuireTech LLC</a></p>
    </div>


    <script>
      function logoutButton() {
        var e = new XMLHttpRequest;
        e.open("GET", "/logout", !0), e.send(), setTimeout(function() {
          window.open("/logged-out", "_self")
        }, 1e3)
      }

      function rebootButton() {
        document.getElementById("status").innerHTML = "Invoking Reboot ...";
        var e = new XMLHttpRequest;
        e.open("GET", "/reboot", !0), e.send(), window.open("/reboot", "_self")
      }

      function listFilesButton() {
        xmlhttp = new XMLHttpRequest, xmlhttp.open("GET", "/listfiles", !1), xmlhttp.send(), document.getElementById("detailsheader").innerHTML = "<h3>Files<h3>", document.getElementById("details").innerHTML = xmlhttp.responseText
      }

      function downloadDeleteButton(e, t) {
        var n = "/file?name=" + e + "&action=" + t;
        xmlhttp = new XMLHttpRequest, "delete" == t && (alert("Are you sure you want to delete?"), xmlhttp.open("GET", n, !1), xmlhttp.send(), document.getElementById("status").innerHTML = xmlhttp.responseText, xmlhttp.open("GET", "/listfiles", !1), xmlhttp.send(), document.getElementById("details").innerHTML = xmlhttp.responseText), "download" == t && (document.getElementById("status").innerHTML = "", window.open(n, "_blank"))
      }

      function showUploadButtonFancy() {
        document.getElementById("detailsheader").innerHTML = "<p>Select File</p>", document.getElementById("status").innerHTML = "";
        var e = '<form id="upload_form" enctype="multipart/form-data" method="post"><input type="file" name="file1" id="file1" onchange="uploadFile()"><br><div class="progress-container"><progress id="progressBar" value="0" max="100"></progress></div><h3 id="status"></h3><p id="loaded_n_total"></p></form>';
        document.getElementById("details").innerHTML = e
      }

      function _(e) {
        return document.getElementById(e)
      }

      function uploadFile() {
        var e = _("file1").files[0],
          t = new FormData;
        t.append("file1", e);
        var n = new XMLHttpRequest;
        n.upload.addEventListener("progress", progressHandler, !1), n.addEventListener("load", completeHandler, !1), n.addEventListener("error", errorHandler, !1), n.addEventListener("abort", abortHandler, !1), n.open("POST", "/"), n.send(t)
      }

      function progressHandler(e) {
        _("loaded_n_total").innerHTML = "Uploaded " + e.loaded + " bytes";
        var t = e.loaded / e.total * 100;
        _("progressBar").value = Math.round(t), _("status").innerHTML = Math.round(t) + "% uploaded... please wait", t >= 100 && (_("status").innerHTML = "Please wait, writing file to filesystem")
      }

      function completeHandler(e) {
        _("status").innerHTML = "Upload Complete", _("progressBar").value = 0, xmlhttp = new XMLHttpRequest, xmlhttp.open("GET", "/listfiles", !1), xmlhttp.send(), document.getElementById("status").innerHTML = "File Uploaded", document.getElementById("detailsheader").innerHTML = "<h3>Files</h3>", document.getElementById("details").innerHTML = xmlhttp.responseText
      }

      function errorHandler(e) {
        _("status").innerHTML = "Upload Failed"
      }

      function abortHandler(e) {
        _("status").innerHTML = "Upload Aborted"
      }
    </script>
  </body>

</html>
)rawliteral";





const char manual_html[] PROGMEM = R"rawliteral(


  <!DOCTYPE html>
<html lang="en">

  <head>
    <meta name="viewport" content="width=device-width,initial-scale=1">
    <meta charset="UTF-8">
    <title>Retia</title>
    <style>
    body{
    background-color:#f4f4f4;
    display:flex;
    flex-direction:column;
    font-family:Arial,sans-serif;
    line-height:1.6;
    margin:0;
    min-height:100vh;
    overflow-x:hidden;
    padding-bottom:10px
}

p{
    color:#4d4d4d;
    font-size:small;
    margin:8px 0
}
.container{
    background-color:#f9f9f9;
    border:1px solid #ccc;
    border-radius:10px;
    box-shadow:0 8px 15px #00000014;
    flex:1;
    margin:0 auto;
    max-width:90%;
    padding:2.5%;
    text-align:center
}
.banner,.footer{
    padding:10px;
    text-align:center
}
.banner{
    background-color:#04263d;
    color:#fff
}

.footer{
    background:#111;
    color:#888
}
 
    </style>
  </head>

  <body>
    <div class="banner">
      <h3 class="banner-head">Retia CP200</h3>

      <a href="#" id="openModal">
        <svg width="35" height="35" viewBox="0 0 24 24" fill="none">
          <path fill-rule="evenodd" clip-rule="evenodd" d="M12 19.5C16.1421 19.5 19.5 16.1421 19.5 12C19.5 7.85786 16.1421 4.5 12 4.5C7.85786 4.5 4.5 7.85786 4.5 12C4.5 16.1421 7.85786 19.5 12 19.5ZM12 21C16.9706 21 21 16.9706 21 12C21 7.02944 16.9706 3 12 3C7.02944 3 3 7.02944 3 12C3 16.9706 7.02944 21 12 21ZM12.75 15V16.5H11.25V15H12.75ZM10.5 10.4318C10.5 9.66263 11.1497 9 12 9C12.8503 9 13.5 9.66263 13.5 10.4318C13.5 10.739 13.3151 11.1031 12.9076 11.5159C12.5126 11.9161 12.0104 12.2593 11.5928 12.5292L11.25 12.7509V14.25H12.75V13.5623C13.1312 13.303 13.5828 12.9671 13.9752 12.5696C14.4818 12.0564 15 11.3296 15 10.4318C15 8.79103 13.6349 7.5 12 7.5C10.3651 7.5 9 8.79103 9 10.4318H10.5Z" fill="#ffffff" />
        </svg>
      </a>


      <a href="/upload">
        <svg width="35" height="35" viewBox="0 0 24 24" fill="none">
          <g id="SVGRepo_bgCarrier" stroke-width="0"></g>
          <g id="SVGRepo_tracerCarrier" stroke-linecap="round" stroke-linejoin="round"></g>
          <g id="SVGRepo_iconCarrier">
            <path fill-rule="evenodd" clip-rule="evenodd" d="M8 10C8 7.79086 9.79086 6 12 6C14.2091 6 16 7.79086 16 10V11H17C18.933 11 20.5 12.567 20.5 14.5C20.5 16.433 18.933 18 17 18H16C15.4477 18 15 18.4477 15 19C15 19.5523 15.4477 20 16 20H17C20.0376 20 22.5 17.5376 22.5 14.5C22.5 11.7793 20.5245 9.51997 17.9296 9.07824C17.4862 6.20213 15.0003 4 12 4C8.99974 4 6.51381 6.20213 6.07036 9.07824C3.47551 9.51997 1.5 11.7793 1.5 14.5C1.5 17.5376 3.96243 20 7 20H8C8.55228 20 9 19.5523 9 19C9 18.4477 8.55228 18 8 18H7C5.067 18 3.5 16.433 3.5 14.5C3.5 12.567 5.067 11 7 11H8V10ZM15.7071 13.2929L12.7071 10.2929C12.3166 9.90237 11.6834 9.90237 11.2929 10.2929L8.29289 13.2929C7.90237 13.6834 7.90237 14.3166 8.29289 14.7071C8.68342 15.0976 9.31658 15.0976 9.70711 14.7071L11 13.4142V19C11 19.5523 11.4477 20 12 20C12.5523 20 13 19.5523 13 19V13.4142L14.2929 14.7071C14.6834 15.0976 15.3166 15.0976 15.7071 14.7071C16.0976 14.3166 16.0976 13.6834 15.7071 13.2929Z" fill="#ffffff"></path>
          </g>
        </svg>
      </a>


    </div>
    <div class="container">
    <h1>User Manual</h1>
        <h2>Introduction:</h2>
        <p>Welcome to Retia CP200!</p>
        <h2>Navigation:</h2>
        <ul>
          <li><strong>Upload Box:</strong> Allows you to upload files.</li>
        </ul>
        <h2>Functionality:</h2>
        <ul>
          <li><strong>Upload File Button:</strong> Click this button to upload files to the application.</li>
          <li><strong>yadi yada File Button:</strong> Click this button to upload files to the application.</li>
        </ul>
    </div>
    <div class="footer">
      <p>© v.1.0.0 2024 <a href="https://www.quiretech.net/">QuireTech LLC</a></p>
    </div>
    
  </body>

</html>
)rawliteral";

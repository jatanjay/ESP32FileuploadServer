const char index_html[] PROGMEM = R"rawliteral(<!DOCTYPE html>
<html lang="en">

<head>
    <meta name="viewport" content="width=device-width,initial-scale=1">
    <meta charset="UTF-8">
    <title>Retia</title>
    <style>
    body,h1,h2,h3,p,form,button{margin:0;padding:0}body{font-family:'Arial',sans-serif;line-height:1.6;background-color:#f4f4f4;display:flex;flex-direction:column;min-height:100vh;overflow:hidden;margin-bottom:auto;padding-bottom:10px}button{padding:10px 20px;margin:5px;border:none;border-radius:5px;background-color:#007bff;color:#fff;cursor:pointer}button:hover{background-color:#0056b3}p{margin:8px 0;color:#4d4d4d;font-size:small}.content-box{background-color:#f0f0f0;border:2px solid #acacac;border-radius:10px;padding:10px;margin-bottom:15px;box-shadow:0 0 5px #0000001a}.content-box p{margin:10px 1px;color:#202020;font-size:small;font-weight:500}.container{margin:0 auto;text-align:center;padding:2.5%;border:1px solid #ccc;border-radius:10px;max-width:90%;background-color:#f9f9f9;box-shadow:0 8px 15px #0003;flex:1}.banner{background-color:#04263d;color:#fff;text-align:center;padding:10px}.banner-head{font-size:2em}select,input{width:100%;padding:8px;box-sizing:border-box;margin-bottom:10px}.footer{background:#111;color:#888;text-align:center;padding:10px;margin-top:auto}.footer a{color:#ddd}.footer p{color:gray;text-decoration:none;transition:color .3s}.button-success,.button-error{color:#fff;border-radius:4px;text-shadow:0 1px 1px #0003}.button-success{background:#1cb841}.button-error{background:#ca3c3c}.upload-box,.controls-container{background-color:#f0f0f0;padding:20px;margin-bottom:20px;border-radius:5px;justify-content:center;align-items:center}.progress-container{position:relative;width:100%;max-width:300px;height:20px;border:2px solid #ccc;border-radius:5px}progress{width:100%;height:100%;border:none;border-radius:5px}.modal{display:none;position:fixed;z-index:9999;left:0;top:0;width:100%;height:100%;overflow:auto;background-color:#00000080}.modal-content{background-color:#fefefe;margin:15% auto;padding:20px;border:1px solid #888;width:80%;max-width:600px;border-radius:5px;position:relative;z-index:10000}.close{color:#aaa;position:absolute;top:8px;right:16px;font-size:28px;font-weight:700;cursor:pointer}.close:hover,.close:focus{color:#000;text-decoration:none}
    </style>
</head>

<body>
    <div class="banner">
        <h3 class="banner-head">Retia CP200</h3>
        <a href="#" id="openModal"><img src="help.svg" alt="View Document"></a>
    </div>
    <div class="container">
        <div class="upload-box">
            <div class="content-box">
                <p><span id="freespiffs">%FREESPIFFS%</span> of <span id="totalspiffs">%TOTALSPIFFS%</span> left</p>
            </div>
            <p>
                <button type="button" class="button-upload" onclick="showUploadButtonFancy()">Upload</button>
            </p>
            <p id="status"></p>
            <p id="detailsheader"></p>  
            <p id="details"></p>
        </div>
        <div class="controls-container">
            <form class="form-dropdown">
                <div>
                    <label for="waveform-type">Waveform</label>
                    <select id="waveform-type" class="select-dropdown" required>
                        <option value="" disabled selected>Select File</option>
                        <option value="1">Select File</option>
                    </select>
                </div>
            </form>
            <button type="button" class="button-success" id="onButton">On</button>
            <button type="button" class="button-error" id="offButton">Off</button>
        </div>
    </div>
    <div class="footer">
        <p>© v.1.0.0 2024 <a href="https://www.quiretech.net/">QuireTech LLC</a></p>
    </div>
    <div id="myModal" class="modal">
        <div class="modal-content"><span class="close">×</span>
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
    </div>
    <script>
        function logoutButton() {
            var e = new XMLHttpRequest;
            e.open("GET", "/logout", !0), e.send(), setTimeout(function () {
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
        document.getElementById("openModal").onclick = function () {
            document.getElementById("myModal").style.display = "block"
        }, document.getElementsByClassName("close")[0].onclick = function () {
            document.getElementById("myModal").style.display = "none"
        }, window.onclick = function (e) {
            e.target == document.getElementById("myModal") && (document.getElementById("myModal").style.display = "none")
        };
    </script>
</body>

</html>)rawliteral";

const char reboot_html[] PROGMEM = R"rawliteral(<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <title></title>
</head>
<body>
  <div class="banner">
    <h3 class="banner-head">Retia CP200</h3>
  </div>
  <div class="container">
    <div class="upload-box">
      <h3>Rebooting, back to app in <span id="countdown">30</span> seconds</h3>
    </div>
  </div>
  <div class="footer l-box">
    <p>© v.1.0.0 2024 <a href="https://www.quiretech.net/">QuireTech LLC</a></p>
  </div>
  <script type="text/javascript">
        var seconds = 6;
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
</html>)rawliteral";

const char logout_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML>
<html lang="en">
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <meta charset="UTF-8">
</head>
<body>
  <p><a href="/">Log Back In</a></p>
</body>
</html>
)rawliteral";
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<!-- Author: Jatan Pandya -->
<head>
	<meta name="viewport" content="width=device-width,initial-scale=1">
	<meta charset="UTF-8">
	<title>Retia</title>
	<style>
	body {
		background-color: #f4f4f4;
		display: flex;
		flex-direction: column;
		font-family: Arial, sans-serif;
		line-height: 1.6;
		margin: 0;
		min-height: 100vh;
		overflow-x: hidden;
		padding-bottom: 10px;
		background-image: linear-gradient(0deg, #f4f4f4, #f4f4f4, #04263d);
	}

	button {
		border: none;
		border-radius: 5px;
		color: #fff;
		cursor: pointer;
		margin: 5px;
		padding: 10px 20px
	}

	p {
		color: #4d4d4d;
		font-size: small;
		margin: 8px 0
	}

	.container {
		background-color: #f9f9f9;
		border: 1px solid #ccc;
		border-radius: 10px;
		box-shadow: 0 8px 15px #00000014;
		flex: 1;
		margin: 0 auto;
		max-width: 90%;
		padding: 2.5%;
		text-align: center
	}

	.banner,
	.footer {
		padding: 10px;
		text-align: center
	}

	.banner {
		background-color: #04263d;
		color: #fff
	}

	input,
	select {
		box-sizing: border-box;
		margin-bottom: 10px;
		padding: 8px;
		width: 100%
	}

	.footer {
		background: #111;
		color: #888
	}

	.button-success {
		background: #1cb841
	}

	.button-error {
		background: #ca3c3c
	}
	</style>
</head>

<body>
	<div class="banner">
		<h2 class="banner-head">Retia CP200</h2>
		<a href="/manual">
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
			</select>
		</form>
		<button type="button" class="button-success" id="onButton">On</button>
	</div>
	<div class="footer">
		<p>© v.1.0.0 2024 <a href="https://www.quiretech.net/">QuireTech LLC</a>
		</p>
	</div>
	<script>
	function populateFileList() {
		var xhr = new XMLHttpRequest();
		xhr.open("GET", "/listfiles", true);
		xhr.onreadystatechange = function() {
			if(xhr.readyState === XMLHttpRequest.DONE && xhr.status === 200) {
				var responseHtml = xhr.responseText;
				var fileList = extractFileNames(responseHtml);
				var select = document.getElementById("waveform-type");
				select.innerHTML = "";
				var firstOption = document.createElement("option");
				firstOption.disabled = true;
				if(fileList.length === 0) {
					firstOption.text = "No files on the system";
				}
				else {
					firstOption.text = "Select file";
				}
				select.add(firstOption);
				fileList.forEach(function(fileName) {
					if(fileName.trim() !== "") {
						var option = document.createElement("option");
						option.text = fileName;
						option.value = fileName;
						select.add(option);
					}
				});
			}
		};
		xhr.send();
	}

	function extractFileNames(html) {
		var parser = new DOMParser();
		var doc = parser.parseFromString(html, "text/html");
		var fileNodes = doc.querySelectorAll("td:first-child");
		var fileList = [];
		fileNodes.forEach(function(node) {
			fileList.push(node.textContent);
		});
		return fileList;
	}
	window.onload = function() {
		populateFileList();
	};
	document.getElementById("onButton").addEventListener("click", function() {
		var selectedFile = document.getElementById("waveform-type").value;
		sendDataToServer(selectedFile);
	});

	function sendDataToServer(selectedFile) {
		var button = document.getElementById("onButton");
		if(!button) {
			console.error("Button with id 'onButton' not found.");
			return;
		}
		if(button.textContent !== "On") {
			console.log("Button is not in 'On' state.");
			return;
		}
		var xhr = new XMLHttpRequest();
		xhr.open("GET", "/process?file=" + encodeURIComponent(selectedFile), true);
		xhr.setRequestHeader("Content-Type", "application/json;charset=UTF-8");
		xhr.onreadystatechange = function() {
			if(xhr.readyState === XMLHttpRequest.DONE) {
				if(xhr.status === 200) {
					console.log("Request successful");
				}
				else {
					console.error("Request failed with status: " + xhr.status);
				}
			}
		};
		xhr.onerror = function() {
			console.error("Request failed");
		};
		xhr.send();
		console.log("GET request sent for file: " + selectedFile);
	}
	document.getElementById("onButton").addEventListener("click", function() {
		var xhr = new XMLHttpRequest();
		xhr.open("GET", "/onButton");
		xhr.onload = function() {
			if(xhr.status >= 200 && xhr.status < 300) {
				console.log("Request successful from Button!");
				toggleButtonState();
			}
			else {
				console.error("Request failed with status: " + xhr.status);
			}
		};
		xhr.onerror = function() {
			console.error("Request failed");
		};
		xhr.send();
	});

	function toggleButtonState() {
		var button = document.getElementById("onButton");
		if(button.textContent === "On") {
			button.textContent = "Off";
			button.classList.remove("button-success");
			button.classList.add("button-error");
			disableSelectionMenu();
		}
		else {
			button.textContent = "On";
			button.classList.remove("button-error");
			button.classList.add("button-success");
			enableSelectMenu();
		}
	}

	function disableSelectionMenu() {
		document.getElementById("waveform-type").disabled = true;
	}

	function enableSelectMenu() {
		document.getElementById("waveform-type").disabled = false;
	}
	</script>
</body>

</html>
)rawliteral"; 

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
		<span id="countdown">3</span> seconds
	</h3>
	<script type="text/javascript">
	var seconds = 4;

	function countdown() {
		seconds = seconds - 1;
		if(seconds < 0) {
			window.location = "/";
		}
		else {
			document.getElementById("countdown").innerHTML = seconds;
			window.setTimeout("countdown()", 1000);
		}
	}
	countdown();
	</script>
</body>

</html>
)rawliteral";

const char format_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">

<head>
	<meta charset="UTF-8" />
</head>

<body>
	<h3>
		formatting, returning to main page in
		<span id="countdown">30</span> seconds
	</h3>
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
	body {
		background-color: #f4f4f4;
		display: flex;
		flex-direction: column;
		font-family: Arial, sans-serif;
		line-height: 1.6;
		margin: 0;
		min-height: 100vh;
		overflow-x: hidden;
		padding-bottom: 10px;
		background-image: linear-gradient(0deg, #f4f4f4, #f4f4f4, #04263d);
	}

	button {
		border: none;
		background-color: #c1c1c1;
		border-radius: 5px;
		color: #030303;
		cursor: pointer;
		margin: 5px;
		padding: 10px 20px
	}


	.button-upload {
		background-color: #007bff;
		border: none;
		border-radius: 5px;
		color: #fff;
		cursor: pointer;
		margin: 5px;
		padding: 10px 20px
	}

	.banner,
	.container,
	.footer {
		padding: 10px;
		text-align: center
	}

	.banner {
		background-color: #04263d;
		color: #fff
	}

	.container {
		background-color: #f9f9f9;
		border: 1px solid #ccc;
		border-radius: 10px;
		box-shadow: 0 8px 15px #0003;
		flex: 1;
		margin: 0 auto;
		max-width: 90%
	}

	.footer {
		background: #111;
		color: #888;
		margin-top: auto
	}
	</style>
</head>

<body>
	<div class="banner">
		<h2 class="banner-head">Retia CP200</h2>
		<a href="/">
			<svg width="34" height="34" viewBox="0 0 24 24" fill="none">
				<path fill-rule="evenodd" clip-rule="evenodd" d="M11.3103 1.77586C11.6966 1.40805 12.3034 1.40805 12.6897 1.77586L20.6897 9.39491L23.1897 11.7759C23.5896 12.1567 23.605 12.7897 23.2241 13.1897C22.8433 13.5896 22.2103 13.605 21.8103 13.2241L21 12.4524V20C21 21.1046 20.1046 22 19 22H14H10H5C3.89543 22 3 21.1046 3 20V12.4524L2.18966 13.2241C1.78972 13.605 1.15675 13.5896 0.775862 13.1897C0.394976 12.7897 0.410414 12.1567 0.810345 11.7759L3.31034 9.39491L11.3103 1.77586ZM5 10.5476V20H9V15C9 13.3431 10.3431 12 12 12C13.6569 12 15 13.3431 15 15V20H19V10.5476L12 3.88095L5 10.5476ZM13 20V15C13 14.4477 12.5523 14 12 14C11.4477 14 11 14.4477 11 15V20H13Z" fill="#FFFFFF" />
			</svg>
		</a>
	</div>
	<div class="container">
		<div class="upload-box">
			<p id="status"></p>
			<p id="detailsheader"></p>
			<p id="details"></p>
			<p>
				<button type="button" class="button-upload" onclick="showUploadButtonFancy()">Upload File</button>
			</p>
			<p>
				<p id="formatdetails"></p>
				<button type="submit" class="button-upload" form="format-form" id="submit">Delete all Files!</button>
				<p>
					<form method="POST" action="/format-spiffs" target="/" id="format-form">
					</form>
		</div>
	</div>
	<div class="footer">
		<p>© v.1.0.0 2024 <a href="https://www.quiretech.net/">QuireTech LLC</a>
		</p>
	</div>
	<script>
	document.addEventListener("DOMContentLoaded", function() {
		var button = document.getElementById("submit");
		var formatDetails = document.getElementById("formatdetails");
		button.addEventListener("click", function(event) {
			event.preventDefault();
			var confirmDelete = confirm("Are you sure you want to delete all files?");
			if(confirmDelete) {
				formatDetails.textContent = "Deleting all files...";
				var xhr = new XMLHttpRequest();
				xhr.open("POST", "/format-spiffs", true);
				xhr.onreadystatechange = function() {
					if(xhr.readyState === XMLHttpRequest.DONE && xhr.status === 200) {}
				};
				xhr.send();
			}
			else {}
		});
	});

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
		xmlhttp = new XMLHttpRequest, xmlhttp.open("GET", "/listfiles", !1), xmlhttp.send(), document.getElementById("detailsheader").innerHTML = " <h3> Files On System <h3> ", document.getElementById("details").innerHTML = xmlhttp.responseText
	}

	function downloadDeleteButton(e, t) {
		var n = "/file?name=" + e + "&action=" + t;
		if(t === "delete") {
			if(confirm("Are you sure you want to delete?")) {
				xmlhttp = new XMLHttpRequest();
				xmlhttp.open("GET", n, false);
				xmlhttp.send();
				document.getElementById("status").innerHTML = xmlhttp.responseText;
				xmlhttp.open("GET", "/listfiles", false);
				xmlhttp.send();
				document.getElementById("details").innerHTML = xmlhttp.responseText;
			}
			else {}
		}
	}

	function showUploadButtonFancy() {
		document.getElementById("detailsheader").innerHTML = " <p> Select File </p>", document.getElementById("status").innerHTML = "";
		var e = '<form id="upload_form" enctype="multipart/form-data" method="post"><input type="file" name="file1" id="file1" onchange="uploadFile()"><br><div class="progress-container"><progress id="progressBar" value="0" max="100"></progress></div><h3 id="status"></h3><p id="loaded_n_total"></p></form>';
		document.getElementById("details").innerHTML = e
	}

	function _(e) {
		return document.getElementById(e)
	}

	function uploadFile() {
		var file = _("file1").files[0];
		// Check if the file name length exceeds 30 characters
		if(file.name.length > 30) {
			alert("File name must be 30 characters or fewer. Please choose a different file.");
			_("file1").value = ''; // Clear the file input
			return; // Stop further processing
		}
		var formData = new FormData();
		formData.append("file1", file);
		var xhr = new XMLHttpRequest();
		xhr.upload.addEventListener("progress", progressHandler, false);
		xhr.addEventListener("load", completeHandler, false);
		xhr.addEventListener("error", errorHandler, false);
		xhr.addEventListener("abort", abortHandler, false);
		xhr.open("POST", "/");
		xhr.send(formData);
	}

	function progressHandler(e) {
		_("loaded_n_total").innerHTML = "Uploaded " + e.loaded + " bytes";
		var t = e.loaded / e.total * 100;
		_("progressBar").value = Math.round(t), _("status").innerHTML = Math.round(t) + "% uploaded... please wait", t >= 100 && (_("status").innerHTML = "Please wait, writing file to filesystem")
	}

	function completeHandler(e) {
		_("status").innerHTML = "Upload Complete", _("progressBar").value = 0, xmlhttp = new XMLHttpRequest, xmlhttp.open("GET", "/listfiles", !1), xmlhttp.send(), document.getElementById("status").innerHTML = "File Uploaded", document.getElementById("detailsheader").innerHTML = " <h3> Files On System </h3>", document.getElementById("details").innerHTML = xmlhttp.responseText
	}

	function errorHandler(e) {
		_("status").innerHTML = "Upload Failed"
	}

	function abortHandler(e) {
		_("status").innerHTML = "Upload Aborted"
	}
	listFilesButton();
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
	body {
		background-color: #f4f4f4;
		display: flex;
		flex-direction: column;
		font-family: Arial, sans-serif;
		line-height: 1.6;
		margin: 0;
		min-height: 100vh;
		overflow-x: hidden;
		padding-bottom: 10px;
		background-image: linear-gradient(0deg, #f4f4f4, #f4f4f4, #04263d);
	}

	p {
		color: #4d4d4d;
		font-size: small;
		margin: 8px 0
	}

	.container {
		background-color: #f9f9f9;
		border: 1px solid #ccc;
		border-radius: 10px;
		box-shadow: 0 8px 15px #00000014;
		flex: 1;
		margin: 0 auto;
		max-width: 90%;
		padding: 2.5%;
		text-align: center
	}

	.banner,
	.footer {
		padding: 10px;
		text-align: center
	}

	.banner {
		background-color: #04263d;
		color: #fff
	}

	.footer {
		background: #111;
		color: #888
	}
	</style>
</head>

<body>
	<div class="banner">
		<h2 class="banner-head">Retia CP200</h2>
		<a href="/">
			<svg width="34" height="34" viewBox="0 0 24 24" fill="none">
				<path fill-rule="evenodd" clip-rule="evenodd" d="M11.3103 1.77586C11.6966 1.40805 12.3034 1.40805 12.6897 1.77586L20.6897 9.39491L23.1897 11.7759C23.5896 12.1567 23.605 12.7897 23.2241 13.1897C22.8433 13.5896 22.2103 13.605 21.8103 13.2241L21 12.4524V20C21 21.1046 20.1046 22 19 22H14H10H5C3.89543 22 3 21.1046 3 20V12.4524L2.18966 13.2241C1.78972 13.605 1.15675 13.5896 0.775862 13.1897C0.394976 12.7897 0.410414 12.1567 0.810345 11.7759L3.31034 9.39491L11.3103 1.77586ZM5 10.5476V20H9V15C9 13.3431 10.3431 12 12 12C13.6569 12 15 13.3431 15 15V20H19V10.5476L12 3.88095L5 10.5476ZM13 20V15C13 14.4477 12.5523 14 12 14C11.4477 14 11 14.4477 11 15V20H13Z" fill="#FFFFFF" />
			</svg>
		</a>
	</div>
	<div class="container">
		<h1>User Manual</h1>
		<h2>Introduction:</h2>
		<p>Welcome to Retia CP200!</p>
		<h2>Navigation:</h2>
		<ul>
			<li>
				<strong>Work In Progress:</strong> #TODO
			</li>
		</ul>
	</div>
	<div class="footer">
		<p>© v.1.0.0 2024 <a href="https://www.quiretech.net/">QuireTech LLC</a>
		</p>
	</div>
</body>

</html>
)rawliteral";
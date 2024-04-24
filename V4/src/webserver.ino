// // Auth: Jatan Pandya

// String processor(const String &
//   var) {
//   if (var == "FIRMWARE") {
//     return FIRMWARE_VERSION;
//   }

//   if (var == "FREESPIFFS") {
//     return humanReadableSize((SPIFFS.totalBytes() - SPIFFS.usedBytes()));
//   }

//   if (var == "USEDSPIFFS") {
//     return humanReadableSize(SPIFFS.usedBytes());
//   }

//   if (var == "TOTALSPIFFS") {
//     return humanReadableSize(SPIFFS.totalBytes());
//   }
// }

// void configureWebServer() {

//   server -> onNotFound(notFound);
//   server -> onFileUpload(handleUpload);

//   server -> on("/format-spiffs", HTTP_POST, [](AsyncWebServerRequest * request) {
//     handleSPIFFSFormat(request);
//   });

//   server -> on("/logout", HTTP_GET, [](AsyncWebServerRequest * request) {
//     request -> requestAuthentication();
//     request -> send(401);
//   });

//   server -> on("/logged-out", HTTP_GET, [](AsyncWebServerRequest * request) {
//     String logmessage = "Client:" + request -> client() -> remoteIP().toString() + " " + request -> url();
//     Serial.println(logmessage);
//     request -> send_P(401, "text/html", logout_html, processor);
//   });

//   server -> on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
//     String logmessage = "Client:" + request -> client() -> remoteIP().toString() + +" " + request -> url();

//     if (checkUserWebAuth(request)) {
//       logmessage += " Auth: Success";
//       Serial.println(logmessage);
//       request -> send_P(200, "text/html", index_html, processor);
//     } else {
//       logmessage += " Auth: Failed";
//       Serial.println(logmessage);
//       return request -> requestAuthentication();
//     }

//   });

//   server -> on("/onButton", HTTP_GET, [](AsyncWebServerRequest * request) {
//     if (!request -> client()) {
//       request -> send(400, "text/plain", "Invalid request");
//       return;
//     }
//     if (onFlag == true) {
//       onFlag = false;
//     } else {
//       onFlag = true;
//     }
//     request -> send(200, "text/plain", "On flag set to true");
//   });

//   server -> on("/process", HTTP_GET, [](AsyncWebServerRequest * request) {

//     if (request -> hasParam("file")) {
//       String receivedFile = "/" + request -> getParam("file") -> value();
//       receivedFile.toCharArray(new_file, receivedFile.length() + 1);

//       request -> send(200, "text/plain", "Received file: " + receivedFile);
//     } else {
//       request -> send(400, "text/plain", "Missing file parameter");
//     }
//   });

//   server -> on("/reboot", HTTP_GET, [](AsyncWebServerRequest * request) {
//     String logmessage = "Client:" + request -> client() -> remoteIP().toString() + " " + request -> url();

//     if (checkUserWebAuth(request)) {
//       request -> send(200, "text/html", reboot_html);
//       logmessage += " Auth: Success";
//       Serial.println(logmessage);
//       shouldReboot = true;
//     } else {
//       logmessage += " Auth: Failed";
//       Serial.println(logmessage);
//       return request -> requestAuthentication();
//     }
//   });

//   server -> on("/upload", HTTP_GET, [](AsyncWebServerRequest * request) {
//     String logmessage = "Client:" + request -> client() -> remoteIP().toString() + +" " + request -> url();

//     if (checkUserWebAuth(request)) {
//       logmessage += " Auth: Success";
//       Serial.println(logmessage);
//       request -> send(200, "text/html", upload_html);
//     } else {
//       logmessage += " Auth: Failed";
//       Serial.println(logmessage);
//       return request -> requestAuthentication();
//     }
//   });

//   server -> on("/manual", HTTP_GET, [](AsyncWebServerRequest * request) {
//     String logmessage = "Client:" + request -> client() -> remoteIP().toString() + +" " + request -> url();

//     if (checkUserWebAuth(request)) {
//       logmessage += " Auth: Success";
//       Serial.println(logmessage);
//       request -> send(200, "text/html", manual_html);
//     } else {
//       logmessage += " Auth: Failed";
//       Serial.println(logmessage);
//       return request -> requestAuthentication();
//     }
//   });

//   server -> on("/listfiles", HTTP_GET, [](AsyncWebServerRequest * request) {
//     String logmessage = "Client:" + request -> client() -> remoteIP().toString() + " " + request -> url();
//     if (checkUserWebAuth(request)) {
//       logmessage += " Auth: Success";
//       Serial.println(logmessage);
//       request -> send(200, "text/plain", listFiles(true));
//     } else {
//       logmessage += " Auth: Failed";
//       Serial.println(logmessage);
//       return request -> requestAuthentication();
//     }
//   });

//   server -> on("/file", HTTP_GET, [](AsyncWebServerRequest * request) {
//     String logmessage = "Client:" + request -> client() -> remoteIP().toString() + " " + request -> url();
//     if (checkUserWebAuth(request)) {
//       logmessage += " Auth: Success";
//       Serial.println(logmessage);

//       if (request -> hasParam("name") && request -> hasParam("action")) {
//         String fileNameWithPath = "/" + request -> getParam("name") -> value();
//         const char * fileName = fileNameWithPath.c_str();
//         const char * fileAction = request -> getParam("action") -> value().c_str();

//         logmessage = "Client:" + request -> client() -> remoteIP().toString() + " " + request -> url() + "?name=" + String(fileName) + "&action=" + String(fileAction);

//         if (!SPIFFS.exists(fileName)) {
//           Serial.println(logmessage + " ERROR: file does not exist");
//           request -> send(400, "text/plain", "ERROR: file does not exist");
//         } else {
//           Serial.println(logmessage + " file exists");
//           if (strcmp(fileAction, "download") == 0) {
//             logmessage += " downloaded";
//             request -> send(SPIFFS, fileName, "application/octet-stream");
//           } else if (strcmp(fileAction, "delete") == 0) {
//             logmessage += " deleted";
//             SPIFFS.remove(fileName);
//             request -> send(200, "text/plain", "Deleted File: " + String(fileName));
//           } else {
//             logmessage += " ERROR: invalid action param supplied";
//             request -> send(400, "text/plain", "ERROR: invalid action param supplied");
//           }
//           Serial.println(logmessage);
//         }
//       } else {
//         request -> send(400, "text/plain", "ERROR: name and action params required");
//       }
//     } else {
//       logmessage += " Auth: Failed";
//       Serial.println(logmessage);
//       return request -> requestAuthentication();
//     }
//   });
// }

// void notFound(AsyncWebServerRequest * request) {
//   String logmessage = "Client:" + request -> client() -> remoteIP().toString() + " " + request -> url();
//   Serial.println(logmessage);
//   request -> send(404, "text/plain", "Not found");
// }

// bool checkUserWebAuth(AsyncWebServerRequest * request) {
//   bool isAuthenticated = false;

//   if (request -> authenticate(config.httpuser.c_str(), config.httppassword.c_str())) {
//     Serial.println("is authenticated via username and password");
//     isAuthenticated = true;
//   }
//   return isAuthenticated;
// }

// void handleUpload(AsyncWebServerRequest * request, String filename, size_t index, uint8_t * data, size_t len, bool final) {
//   if (checkUserWebAuth(request)) {
//     String logmessage = "Client:" + request -> client() -> remoteIP().toString() + " " + request -> url();
//     Serial.println(logmessage);

//     if (!index) {
//       logmessage = "Upload Start: " + String(filename);
//       request -> _tempFile = SPIFFS.open("/" + filename, "w");
//       Serial.println(logmessage);
//     }

//     if (len) {
//       request -> _tempFile.write(data, len);
//       logmessage = "Writing file: " + String(filename) + " index=" + String(index) + " len=" + String(len);
//       Serial.println(logmessage);
//     }

//     if (final) {
//       logmessage = "Upload Complete: " + String(filename) + ",size: " + String(index + len);
//       request -> _tempFile.close();
//       Serial.println(logmessage);
//       request -> redirect("/");
//     }
//   } else {
//     Serial.println("Auth: Failed");
//     return request -> requestAuthentication();
//   }
// }

// void handleSPIFFSFormat(AsyncWebServerRequest * request) {
//   if (checkUserWebAuth(request)) {
//     shouldFormat = true;
//   } else {
//     Serial.println("Authentication failed. Requesting authentication...");
//     request -> requestAuthentication();
//   }
// }

// void handleRoot(AsyncWebServerRequest * request) {
//   request -> send(200, "text/html", "<script>window.location.reload();</script>");
//   Serial.println("handle root called");

// }
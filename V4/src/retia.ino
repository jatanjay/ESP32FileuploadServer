// Auth: Jatan Pandya

#include <Adafruit_MCP4725.h>

#include <AsyncTCP.h>

#include <ESPAsyncWebServer.h>

#include <FS.h>

#include <SPIFFS.h>

#include <WiFi.h>

#include <ArduinoJson.h>

#include "webpages.h"

#define FIRMWARE_VERSION "v0.0.1"
#define DAC_ADDRESS 0x60

String hostname = "Retia_CP200";
const String default_ssid = "Verizon_J9SPGP";
const String default_wifipassword = "cab3-azure-plot";
const String default_httpuser = "retia";
const String default_httppassword = "retia";
const int default_webserverporthttp = 80;

// const String default_ssid = "RetiaWest";
// const String default_wifipassword = "tuptu0ca!drac";
// const String default_httpuser = "retia";
// const String default_httppassword = "retia";
// const int default_webserverporthttp = 80;

struct Config {
  String ssid;
  String wifipassword;
  String httpuser;
  String httppassword;
  int webserverporthttp;
};

Config config;
AsyncWebServer * server;
Adafruit_MCP4725 dac;

bool shouldReboot = false;
bool shouldFormat = false;
bool timerFlag = false;
bool onFlag = false;
bool file_opened = false;

char new_file[32];

hw_timer_t * My_timer = NULL;

void IRAM_ATTR onTimer() {
  timerFlag = true;
}

File file_on_flash;

String listFiles(bool ishtml = false);

void openFile(const char * filename) {
  file_on_flash = SPIFFS.open(filename, "r");
  if (!file_on_flash) {
    Serial.println("Failed to open file for reading");
    return;
  }
}

void transmitToDAC(int value) {
  dac.setVoltage(value, false);
}

void rebootESP(String message) {
  Serial.print("Rebooting ESP32: ");
  Serial.println(message);
  ESP.restart();
}

String listFiles(bool ishtml) {
  String returnText = "";
  Serial.println("Listing files stored on SPIFFS");
  File root = SPIFFS.open("/");
  File foundfile = root.openNextFile();

  String excludeFiles[] = {};

  if (ishtml) {
    returnText +=
      "<table><tr><th align='left'>Name</th><th "
    "align='left'>Size</th><th></th><th></th></tr>";
  }

  while (foundfile) {
    bool exclude = false;
    for (int i = 0; i < sizeof(excludeFiles) / sizeof(excludeFiles[0]); i++) {
      if (String(foundfile.name()) == excludeFiles[i]) {
        exclude = true;
        break;
      }
    }

    if (!exclude) {
      if (ishtml) {
        returnText += "<tr align='left'><td>" + String(foundfile.name()) +
          "</td><td>" + humanReadableSize(foundfile.size()) +
          "</td>";
        returnText += "<td><button onclick=\"downloadDeleteButton(\'" +
          String(foundfile.name()) +
          "\', \'delete\')\">Delete</button></tr>";
      } else {
        returnText += "File: " + String(foundfile.name()) +
          " Size: " + humanReadableSize(foundfile.size()) + "\n";
      }
    }
    foundfile = root.openNextFile();
  }

  if (ishtml) {
    returnText += "</table>";
  }

  root.close();
  foundfile.close();
  return returnText;
}

String listFiles_api() {
  String returnText = "";
  Serial.println("Listing files stored on SPIFFS");
  File root = SPIFFS.open("/");
  File foundfile = root.openNextFile();

  while (foundfile) {
    returnText += "File: " + String(foundfile.name()) +
      " Size: " + String(foundfile.size()) + " kilobytes\n";
    foundfile = root.openNextFile();
  }
  root.close();
  return returnText;
}

String humanReadableSize(const size_t bytes) {
  if (bytes < 1024)
    return String(bytes) + " B";
  else if (bytes < (1024 * 1024))
    return String(bytes / 1024.0) + " KB";
  else if (bytes < (1024 * 1024 * 1024))
    return String(bytes / 1024.0 / 1024.0) + " MB";
  else
    return String(bytes / 1024.0 / 1024.0 / 1024.0) + " GB";
}

void setup() {
  Serial.begin(115200);

  My_timer = timerBegin(0, 80, true);
  timerAttachInterrupt(My_timer, & onTimer, true);
  timerAlarmWrite(My_timer, 12500, true);
  timerAlarmEnable(My_timer);
  dac.begin(DAC_ADDRESS);

  Serial.print("Firmware: ");
  Serial.println(FIRMWARE_VERSION);

  Serial.println("Booting ...");

  Serial.println("Mounting SPIFFS ...");
  if (!SPIFFS.begin(true)) {
    Serial.println("ERROR: Cannot mount SPIFFS, Rebooting");
    rebootESP("ERROR: Cannot mount SPIFFS, Rebooting");
  }

  Serial.print("SPIFFS Free: ");
  Serial.println(humanReadableSize((SPIFFS.totalBytes() - SPIFFS.usedBytes())));
  Serial.print("SPIFFS Used: ");
  Serial.println(humanReadableSize(SPIFFS.usedBytes()));
  Serial.print("SPIFFS Total: ");
  Serial.println(humanReadableSize(SPIFFS.totalBytes()));

  Serial.println(listFiles());

  Serial.println("Loading Configuration ...");

  config.ssid = default_ssid;
  config.wifipassword = default_wifipassword;
  config.httpuser = default_httpuser;
  config.httppassword = default_httppassword;
  config.webserverporthttp = default_webserverporthttp;
  WiFi.setHostname(hostname.c_str());

  Serial.print("\nConnecting to Wifi: ");
  WiFi.begin(config.ssid.c_str(), config.wifipassword.c_str());
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\n\nNetwork Configuration:");
  Serial.println("----------------------");
  Serial.print("         SSID: ");
  Serial.println(WiFi.SSID());
  Serial.print("  Wifi Status: ");
  Serial.println(WiFi.status());
  Serial.print("Wifi Strength: ");
  Serial.print(WiFi.RSSI());
  Serial.println(" dBm");
  Serial.print("          MAC: ");
  Serial.println(WiFi.macAddress());
  Serial.print("           IP: ");
  Serial.println(WiFi.localIP());
  Serial.print("       Subnet: ");
  Serial.println(WiFi.subnetMask());
  Serial.print("      Gateway: ");
  Serial.println(WiFi.gatewayIP());
  Serial.print("        DNS 1: ");
  Serial.println(WiFi.dnsIP(0));
  Serial.print("        DNS 2: ");
  Serial.println(WiFi.dnsIP(1));
  Serial.print("        DNS 3: ");
  Serial.println(WiFi.dnsIP(2));
  Serial.println();

  Serial.println("Configuring Webserver ...");
  server = new AsyncWebServer(config.webserverporthttp);
  configureWebServer();

  Serial.println("Starting Webserver ...");
  server -> begin();
}

void loop() {

  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');
    Serial.println(command);
    handleSerialCommand(command);
  }
  
  if (shouldReboot) {
    rebootESP("Web Admin Initiated Reboot");
  } else if (shouldFormat) {
    shouldFormat = false;
    Serial.println("Formatting SPIFFS...");
    if (SPIFFS.format()) {
      Serial.println("SPIFFS formatted successfully.");
      shouldReboot = true;
    } else {
      Serial.println("SPIFFS formatting failed.");
    }
  }
}

void handleSerialCommand(String command) {
  if (command.equals("listFiles")) {
    String fileList = listFiles(false);
    Serial.println(fileList);
  } else if (command.equals("runDac")) {
    selectFileToRunDAC();
  } else if (command.equals("stopDac")) {
    onFlag = false;
    Serial.println("DAC subroutine stopped.");
  } else if (command) {
    Serial.println(command);
    Serial.println("in handler");
    onFlag = true;
    timerFlag = true;
    trasmitter(command);
  } else {
    Serial.println("[API] Invalid command");
  }
}


void listFilesWithNumbers() {
  Serial.println("Listing files stored on SPIFFS");
  File root = SPIFFS.open("/");
  File foundfile = root.openNextFile();

  int fileNumber = 1;

  while (foundfile) {
    Serial.print("File ");
    Serial.print(fileNumber);
    Serial.print(": ");
    Serial.print(foundfile.name());
    Serial.print(" (Size: ");
    Serial.print(foundfile.size());
    Serial.println(" bytes)");

    foundfile = root.openNextFile();
    fileNumber++;
  }

  root.close();
}


void trasmitter(String command){
  // Serial.println("In Converter . . .");
  // if (timerFlag) {
    // if (onFlag) {
      String dataString = command;
      /*
        * Data in file is stored in mmHg e.g., 60.80
        * corresponds to blood pressure of the patient
        *
        * 0-3v == 0 - 300 mmHg
        */
      int intData = dataString.toFloat() * 100;
      /*
        * Value in file is stored as float with 2 decimal points.
        * Removing decimals by * 100 and storing as integer
        */
      int dacValue = map(intData, 0, 30000, 0, 4095);
      /*
        * 0 - 30,000 corresponds to 0-3v or 0-4096
        */
      transmitToDAC(dacValue);
      Serial.println(dacValue);
      // }
    // timerFlag = false;
  // }
}






void selectFileToRunDAC() {
  Serial.println("Select a file to run DAC subroutine:");
  listFilesWithNumbers();
  Serial.println("Enter the number corresponding to the file you want to run:");

  while (true) {
    if (Serial.available() > 0) {
      String selectedFileNumber = Serial.readStringUntil('\n');
      int fileNumber = selectedFileNumber.toInt();
      if (fileNumber > 0) {
        runFileSubroutine(fileNumber);
        break;
      } else {
        Serial.println("Invalid file number. Please enter a valid file number.");
      }
    }
  }
}

void runFileSubroutine(int fileNumber) {
  Serial.println("Running file subroutine for file number " + String(fileNumber));

  File root = SPIFFS.open("/");
  File foundfile = root.openNextFile();

  int count = 1;

  while (foundfile) {
    if (count == fileNumber) {
      Serial.print("Selected file: ");
      Serial.println(foundfile.name());
      strcpy(new_file, "/");
      strcat(new_file, foundfile.name());
      Serial.println(new_file);
      onFlag = true;
      break;
    }
    foundfile = root.openNextFile();
    count++;
  }

  root.close();
}
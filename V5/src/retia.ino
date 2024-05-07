/*
Auth: Jatan Pandya

Script to transmit serial data to MCP4725 DAC using ESP32

Tested on:
ESP32V2 Feather Huzzah
ESP32V1 Feather 
Current Build Config Files for : ESP32 V2 FEATHER 8M Flash, 2MB PSRAM

API Calls, Webserver Code has been removed.
*/

#include <Adafruit_MCP4725.h>

#define FIRMWARE_VERSION "v1.0.0"
#define DAC_ADDRESS 0x62

Adafruit_MCP4725 dac;

void setup() {
  Serial.begin(115200);
  dac.begin(DAC_ADDRESS);

  Serial.println("");
  Serial.println("***********************");
  Serial.println("Welcome to Retia CP200");
  Serial.print("Firmware: ");
  Serial.println(FIRMWARE_VERSION);
  Serial.println("***********************");
  Serial.println("");
}

void loop() {

  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');
    Serial.println(command);
    handleSerialCommand(command);
  }
}

void handleSerialCommand(String command) {
  bool isNumber = true;
  for (size_t i = 0; i < command.length(); i++) {
    if (!isdigit(command[i]) && command[i] != '.') {
      isNumber = false;
      break;
    }
  }
  if (isNumber) {
    trasmitter(command);
  } else if (command.equals("DeviceName")) {
    Serial.println("");
    Serial.println("--CP200-v1.0.0--");
    Serial.println("");
  } else {
    Serial.println("[API] Invalid command");
  }
}

void trasmitter(String command) {
  String dataString = command;
  /*
   * Data in file is stored in mmHg e.g., 60.80
   * corresponds to blood pressure of the patient
   *
   * 0-3v == 0 - 300 mmHg
   */
  float floatData = dataString.toFloat();

  // Scale down the input to fit within the range of 0 to 300
  float scaledData = floatData / 300.0;

  // New reference Voltage mapping: scale it down by 3.0/3.3
  float maxInput = 3.0;
  float mappedData = scaledData * maxInput;

  // Convert the mapped value to DAC value (0 - 4095)
  int dacValue = mappedData * 4095.0 / 3.3;

  // dacValue is within the range of 0 to 4095
  dacValue = constrain(dacValue, 0, 4095);
  transmitToDAC(dacValue);
}

void transmitToDAC(int value) {
  dac.setVoltage(value, false);
  Serial.print("Set Voltage to: ");
  Serial.println(value);
}
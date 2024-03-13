# 1 "C:\\Users\\jayes\\AppData\\Local\\Temp\\tmpo3v66nmq"
#include <Arduino.h>
# 1 "C:/Users/jayes/Documents/PlatformIO/Projects/retia_esp32/src/main.ino"
#include <Adafruit_MCP4725.h>
#include <FS.h>
#include <SPIFFS.h>
#include "WiFi.h"
#include "ESPAsyncWebServer.h"

Adafruit_MCP4725 dac;
#define DAC_ADDRESS 0x60

const char *ssid = "The Goblin Warren";
const char *password = "yellowwhale161";


void readAndTransmitFile(const char *filename);
void transmitToDAC(int value);

AsyncWebServer server(80);
void setup();
void loop();
#line 19 "C:/Users/jayes/Documents/PlatformIO/Projects/retia_esp32/src/main.ino"
void setup()
{
    Serial.begin(115200);

    dac.begin(DAC_ADDRESS);

    if (!SPIFFS.begin(true))
    {
        Serial.println("An Error has occurred while mounting SPIFFS");
        return;
    }

    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        Serial.println("Connecting to WiFi..");
    }

    Serial.println(WiFi.localIP());

    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/index.html", String(), false); });

    server.on("/styles.css", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/styles.css", "text/css"); });

    server.on("/pure.css", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/pure.css", "text/css"); });

    server.on("/grids-responsive-min.css", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/grids-responsive-min.css", "text/css"); });

    server.on("/app.js", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/app.js", "text/javascript"); });


    server.on("/on", HTTP_GET, [](AsyncWebServerRequest *request)
              {
# 84 "C:/Users/jayes/Documents/PlatformIO/Projects/retia_esp32/src/main.ino"
        readAndTransmitFile("/demo.txt"); });



    server.begin();
}

void loop()
{
}

void readAndTransmitFile(const char *filename)
{
    File file = SPIFFS.open(filename, "r");
    if (!file)
    {
        Serial.println("Failed to open file for reading");
        return;
    }

    while (file.available())
    {
        String dataString = file.readStringUntil('\n');
        int intData = dataString.toInt();

        Serial.print("Read from file: ");
        Serial.println(intData);
        transmitToDAC(intData);

        delay(2000);
    }

    file.close();
}


void transmitToDAC(int value)
{
    Serial.print("ADC Write for: ");
    Serial.println(value);
    dac.setVoltage(value, false);
}
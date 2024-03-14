#include <Adafruit_MCP4725.h>
#include <FS.h>
#include <SPIFFS.h>
#include "WiFi.h"
#include "ESPAsyncWebServer.h"

Adafruit_MCP4725 dac;
#define DAC_ADDRESS 0x60

const char* ssid = "Verizon_J9SPGP";
const char* password = "cab3-azure-plot";

AsyncWebServer server(80);

hw_timer_t* My_timer = NULL;

bool timerFlag = false;
bool onFlag = false;
File file;



void IRAM_ATTR onTimer()
{
    timerFlag = true;
}

void setup()
{

    My_timer = timerBegin(0, 80, true);
    timerAttachInterrupt(My_timer, &onTimer, true);
    timerAlarmWrite(My_timer, 8000, true);
    timerAlarmEnable(My_timer);

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


    readAndTransmitFile("/demo.txt"); 
    
    server.on("/", HTTP_GET, [](AsyncWebServerRequest* request) {
        request->send(SPIFFS, "/index.html", String(), false);
    });

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
                onFlag = true;
          });


    server.begin();
}

void loop()
{
    if (timerFlag & onFlag)
    {
        if (file.available())
        {

            String dataString = file.readStringUntil('\n');
            int intData = dataString.toInt();
            intData = intData * 10;
            
            Serial.print("Read from file: ");
            Serial.println(intData);
            transmitToDAC(intData);
        }
        timerFlag = false;

//        file.close();
    }
}

void readAndTransmitFile(const char* filename)
{
    file = SPIFFS.open(filename, "r");
    if (!file)
    {
        Serial.println("Failed to open file for reading");
        return;
    }
}

void transmitToDAC(int value)
{
    Serial.print("ADC Write for: ");
    Serial.println(value);
    dac.setVoltage(value, false);
}

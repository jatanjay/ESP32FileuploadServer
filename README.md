# ESP32 Local Webserver
## with SPIFFS Upload & MCP4725 Digital to Analog Transmission Routine

### Overview
This repository contains a web application for ESP32 that enables users to upload, delete, download, and format files. 
Additionally, it includes a routine to transmit data from a medical dataset uploaded on the SPIFFS using an MCP4725 DAC peripheral.

### Screenshots

![Screenshot1](screenshots\shot_2.png)
![Screenshot2](screenshots\shot_1.png)

### Structure
1. The final deployed application can be found under `V3/`.
2. Web application files (HTML/CSS/JS) are stored as a `.h` file under `include/`.
3. The webserver and DAC routine application are located in `src/`.
4. The maximum possible partition table for a 6MB ESP32 V2 is provided in `no_ota_2_2.csv`.
5. PlatformIO configuration files for `featheresp32` and `adafruit_feather_esp32_v2` are available in `platformio.ini`.

### Tips if forking for your project
1. There seems to be a limit to the amount of CSS that can be rendered at runtime when supplied using inline `<style>`. If your application requires elaborate CSS and/or frameworks, it's recommended to load the files onto SPIFFS and reference them in your HTML.
2. Since this project necessitated SPIFFS formatting capability, the HTML, CSS, and JS files are stored in app storage as header files. If this isn't an issue for your project, it's better to have separate `.html`, `.css`, and `.js` files in SPIFFS.
3. The app will be served at `http://"your-hostname"`. By default --> `retia_cp200`. Refer `V3`/`retia.ino` for complete wifi config details.
4. The app also has an API through which you can access the app via serial. You can test it using Docklight etc.
5. `V4/` is a "serial" version of the app, without the web app capabilites. Think of it as a glorified DAC system hooked onto your PC. It has an API that can be used to transmit files directly via serial. Using `com_script.py`, you can trasmit your local file. The script allows you to change your COM port, file location etc. The idea behind this implementation is that now you have no limit on file that has to be trasmitted, as the file will be on your PC and not SPIFFS. Note: The script is configured to scale down DAC's reference voltage of 3.3V to 3.0V. (See `V4/retia.ino`)

#### Acknowledgement
Parts of the SPIFFS upload mechanism are based on this [repository](https://github.com/smford/esp32-asyncwebserver-fileupload-example).

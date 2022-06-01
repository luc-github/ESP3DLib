ESP3DLib 3.0 triggers
in configuration_adv.h
1 - madatory define 
 #define ESP3D_WIFISUPPORT   // ESP3D Library WiFi management (https://github.com/luc-github/ESP3DLib)

 #define WEBSUPPORT          // Start a webserver (which may include auto-discovery)
 ->#define HTTP_FEATURE
 #define OTASUPPORT          // Support over-the-air firmware updates
 ->#define OTA_FEATURE
 #define WIFI_CUSTOM_COMMAND // Accept feature config commands (e.g., WiFi ESP3D) from the host

2 - Optional define
 #define WIFI_SSID "WiFi SSID"
 #define WIFI_PWD  "WiFi Password"

Task Core default is 0
 #define ESP3DLIB_RUNNING_CORE 0
Task Priority default is 1
 #define ESP3DLIB_RUNNING_PRIORITY 1

Features on by default
 #define DISABLE_MDNS_FEATURE
 #define DISABLE_SSDP_FEATURE
 #define DISABLE_CAPTIVE_PORTAL_FEATURE

 esp3dlibconfig.h include Marlin configuration define and translate to ESP3DLib define 


3 - Entry points

#include "esp3dlib.h"
//Serial2
Serial2Socket class

//init
 esp3dlib.init();

 //idle task
 esp3dlib.idletask();

//Custom command
esp3dlib.parse(command_ptr);

4 - Screen flags
    1 - ESP_SERIAL_FLAG 
        to Serial if ESP3D (ESP_SERIAL_CLIENT ) or ESP3DLib (ESP_ECHO_SERIAL_CLIENT)
    2 - ESP_REMOTE_SCREEN_FLAG
        a - to Serial using M117 if ESP3D for connected display
        b - to Socket2Serial using M117 if ESP3DLib (HAS_DISPLAY) for embedded display
        c - to Serial (ESP_ECHO_SERIAL_CLIENT) using M117 if ESP3DLib (HAS_SERIAL_DISPLAY) for serial display
    3 - ESP_SCREEN_FLAG
        to screen connected to ESP using ESP3D 


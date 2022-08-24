/*
  esp3dconfig.h -  esp3dlib functions class

  Copyright (c) 2014 Luc Lebosse. All rights reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/
//this is ESP3DLIB compilation environement
#define ESP3DLIB_ENV

//Uncomment if you want to compile Marlin and ESP3DLib with Arduino IDE
//Comment if you want to compile Marlin and ESP3DLib with PlatformIO
//#define COMPILE_WITH_ARDUINO_IDE

#if !defined(COMPILE_WITH_ARDUINO_IDE)
//config reference, do not touch
#ifndef ESP_XSTR
#define ESP_XSTR_(M) #M
#define ESP_XSTR(M) ESP_XSTR_(M)
#endif
#define MARLIN_PATH(PATH) ESP_XSTR(../../../../../Marlin/src/PATH)
#include MARLIN_PATH(inc/MarlinConfig.h)

#undef DISABLED
#undef _BV
#undef SPI_FULL_SPEED
#undef SPI_HALF_SPEED
#undef SPI_QUARTER_SPEED
#undef SPI_EIGHTH_SPEED
#undef SPI_SIXTEENTH_SPEED
#else
#define OTASUPPORT
#define WEBSUPPORT
#define SHORT_BUILD_VERSION "2.0.9.3+"

/*********************************************************
 *
 *        Manual Configuration for Arduino IDE
 *        because cannot access to
 *        Marlin configuration files
 *
 * *******************************************************/
//#define DISABLE_MDNS_FEATURE
//#define DISABLE_SSDP_FEATURE
//#define DISABLE_CAPTIVE_PORTAL_FEATURE
//#define DISABLE_TELNET_FEATURE
//#define DISABLE_NOTIFICATION_FEATURE
//#define DISABLE_SD_UPDATE_FEATURE
//#define DISABLE_WEB_UPDATE_FEATURE
//#define AUTHENTICATION_FEATURE

#ifndef SD_DETECT_STATE
#define SD_DETECT_STATE LOW
#endif

#define SDSUPPORT
//#define HAS_DISPLAY
//#define HAS_SERIAL_DISPLAY "M118 P1 "
#define GLOBAL_FILESYSTEM_FEATURE
//#define DISABLE_WDT_ESP3DLIB_TASK
//#define DISABLE_WDT_CORE_0
#endif //COMPILE_MARLIN_WITH_ARDUINO_IDE


//DISABLE_WDT_CORE_0: disable WDT on core 0 when procession webserver
//Rely on Configuration_adv.h or manual config above

//Allow to disable WDT for ESP3DLIB task only
#ifndef ENABLE_WDT_ESP3DLIB_TASK
#define DISABLE_WDT_ESP3DLIB_TASK
#endif

//Allow to override the default core used by ESP3DLIB
#ifndef ESP3DLIB_RUNNING_CORE
#define  ESP3DLIB_RUNNING_CORE 0
#endif //ESP3DLIB_RUNNING_CORE

//Allow to override the default priority task used by ESP3DLIB_RUNNING_PRIORITY
#ifndef ESP3DLIB_RUNNING_PRIORITY
#define  ESP3DLIB_RUNNING_PRIORITY 1
#endif //ESP3DLIB_RUNNING_PRIORITY

//Allow to override the default DELAY_START_ESP3D used by ESP3DLIB
#ifndef DELAY_START_ESP3D
#define DELAY_START_ESP3D 100
#endif //DELAY_START_ESP3D

//Allow to override the default Client SSID
//Rely on Configuration_adv.h
#ifdef WIFI_SSID
#define STATION_WIFI_SSID WIFI_SSID
#endif //WIFI_SSID

//Allow to override the default Client SSID password
//Rely on Configuration_adv.h
#ifdef WIFI_PWD
#define STATION_WIFI_PASSWORD WIFI_PWD
#endif //WIFI_PWD

//COMMUNICATION_PROTOCOL: to communicate ESP3DLIB
#define COMMUNICATION_PROTOCOL SOCKET_SERIAL

//AUTHENTICATION_FEATURE: protect pages by login password
//Rely on Configuration_adv.h  or manual config above

//WIFI_FEATURE : enable WIFI function
#define WIFI_FEATURE

//SERIAL_COMMAND_FEATURE: allow to send command by serial
#define SERIAL_COMMAND_FEATURE

//HTTP_FEATURE: enable Web Server
//Rely on Configuration_adv.h
#ifdef WEBSUPPORT
#define HTTP_FEATURE
#endif //WEBSUPPORT

//OTA_FEATURE: this feature is arduino update over the air
//Rely on Configuration_adv.h
#ifdef OTASUPPORT
#define OTA_FEATURE
#endif //OTASUPPORT

//MDNS_FEATURE: this feature allow  type the name defined
//in web browser by default: http:\\marlinesp.local and connect
//Rely on Configuration_adv.h
#ifndef DISABLE_MDNS_FEATURE
#define MDNS_FEATURE
#endif //DISABLE_MDNS_FEATURE

//SSDD_FEATURE: this feature is a discovery protocol, supported on Windows out of the box
//Rely on Configuration_adv.h
#ifndef DISABLE_SSDP_FEATURE
#define SSDP_FEATURE
#endif //DISABLE_SSDP_FEATURE

//CAPTIVE_PORTAL_FEATURE: In config mode redirect all unknow call to main page
//Rely on Configuration_adv.h
#ifndef DISABLE_CAPTIVE_PORTAL_FEATURE
#define CAPTIVE_PORTAL_FEATURE
#endif //DISABLE_CAPTIVE_PORTAL_FEATURE

//TELNET_FEATURE : enable Telnet function
//Rely on Configuration_adv.h
#ifndef DISABLE_TELNET_FEATURE
#define TELNET_FEATURE
#endif //DISABLE_TELNET_FEATURE

//FILESYSTEM_FEATURE: to host some files on flash
//ESP_SPIFFS_FILESYSTEM       0
//ESP_FAT_FILESYSTEM          1
//ESP_LITTLEFS_FILESYSTEM     2
#define FILESYSTEM_FEATURE ESP_LITTLEFS_FILESYSTEM

//WEB_UPDATE_FEATURE: allow to flash fw using web UI
//Rely on Configuration_adv.h
#ifndef DISABLE_WEB_UPDATE_FEATURE
#define WEB_UPDATE_FEATURE
#endif //DISABLE_WEB_UPDATE_FEATURE

#ifdef SDSUPPORT
//SD_DEVICE: to access SD Card files directly
//ESP_SD_NATIVE               1
//ESP_SDFAT                   3
//ESP_SDFAT2                  4
#define SD_DEVICE    ESP_SDFAT2

//SD Device Connection type (default is ESP_NO_SD if not defined)
//ESP_NO_SD
//ESP_DIRECT_SD
//ESP_SHARED_SD
#define SD_DEVICE_CONNECTION  ESP_SHARED_SD

//pin if reader has insert detection feature
//let -1 or comment if none
#if defined (SD_DETECT_PIN) && (SD_DETECT_PIN >= 0)
#define ESP_SD_DETECT_PIN       SD_DETECT_PIN
#endif //SD_DETECT_PIN  

//value expected for ESP_SD_DETECT_PIN
#ifdef SD_DETECT_STATE
#define ESP_SD_DETECT_VALUE      SD_DETECT_STATE
#endif

#if defined (SDSS) && (SDSS >= 0)
#define ESP_SD_CS_PIN SDSS
#endif //SDSS

#if defined(SD_SCK_PIN) && (SD_SCK_PIN >= 0)
#define ESP_SD_SCK_PIN SD_SCK_PIN
#endif //SD_SCK_PIN

#if defined(SD_MOSI_PIN) && (SD_MOSI_PIN >= 0)
#define ESP_SD_MOSI_PIN SD_MOSI_PIN
#endif //SD_MOSI_PIN

#if defined(SD_MISO_PIN) && (SD_MISO_PIN >= 0)
#define ESP_SD_MISO_PIN SD_MISO_PIN
#endif //SD_MISO_PIN

//SD_UPDATE_FEATURE: allow to configure settings using SD
//Rely on Configuration_adv.h
#ifndef DISABLE_SD_UPDATE_FEATURE
#define SD_UPDATE_FEATURE
#endif //DISABLE_SD_UPDATE_FEATURE
#endif //SDSUPPORT



//NOTIFICATION_FEATURE : allow to push notifications
//Rely on Configuration_adv.h
#ifndef DISABLE_NOTIFICATION_FEATURE
#define NOTIFICATION_FEATURE
#endif //DISABLE_NOTIFICATION_FEATURE

//GCODE_HOST_FEATURE: allow to host gcode files on flash, SD etc..
//Also used by ESP700
#define GCODE_HOST_FEATURE

//Allows to mount /FS and /SD under / for FTP server /WebDav
#define GLOBAL_FILESYSTEM_FEATURE

//WEBDAV_FEATURE : enable WebDav feature
//FS_ROOT        mount all FS
//FS_FLASH       mount Flash FS
//FS_SD          mount SD FS
#ifndef DISABLE_WEBDAV_FEATURE
#ifndef WEBDAV_FEATURE
#define WEBDAV_FEATURE  FS_ROOT
#endif //WEBDAV_FEATURE
#endif //DISABLE_WEBDAV_FEATURE

/************************************
 *
 * DEBUG
 *
 * **********************************/
//Do not do this when connected to printer !!!
//be noted all upload may failed if enabled
//DEBUG_OUTPUT_SERIAL0 1
//DEBUG_OUTPUT_TELNET  4
//DEBUG_OUTPUT_WEBSOCKET  5
//#define ESP_DEBUG_FEATURE DEBUG_OUTPUT_SERIAL0

#ifdef ESP_DEBUG_FEATURE
#define DEBUG_ESP3D_OUTPUT_PORT  8000
#endif //ESP_DEBUG_FEATURE

/************************************
 *
 * Benchmark report
 *
 * **********************************/
//#define ESP_BENCHMARK_FEATURE

/************************************
 *
 * Settings
 *
 * **********************************/
//SETTINGS_IN_EEPROM 0
//SETTINGS_IN_PREFERENCES 1
#define ESP_SAVE_SETTINGS SETTINGS_IN_PREFERENCES

//For Marlin Embedded no way to change the FW flavor
#define FIXED_FW_TARGET MARLIN_EMBEDDED
/************************************
 *
 * Customize SSDP
 *
 * **********************************/
#ifdef SSDP_FEATURE
#ifndef ESP_MODEL_NAME
#define ESP_MODEL_NAME "ESP32"
#endif //ESP_MODEL_NAME
#ifndef ESP_MODEL_URL
#define ESP_MODEL_URL "https://www.espressif.com/en/products/hardware/esp-wroom-32/overview"
#endif //ESP_MODEL_URL
#ifndef ESP_MODEL_NUMBER
#define ESP_MODEL_NUMBER "Marlin with ESP3DLib"
#endif //ESP_MODEL_NUMBER
#ifndef ESP_MANUFACTURER_NAME
#define ESP_MANUFACTURER_NAME "Espressif Systems"
#endif //ESP_MANUFACTURER_NAME
#ifndef ESP_MANUFACTURER_URL
#define ESP_MANUFACTURER_URL "http://espressif.com"
#endif //ESP_MANUFACTURER_URL
#endif //SSDP_FEATURE

/************************************
 *
 * Customize Notifications
 *
 * **********************************/
#ifdef NOTIFICATION_FEATURE
#ifndef NOTIFICATION_ESP_ONLINE
#define NOTIFICATION_ESP_ONLINE "Hi, %ESP_NAME% is now online at %ESP_IP%"
#endif //NOTIFICATION_ESP_ONLINE
#ifndef NOTIFICATION_ESP_OFFLINE
#define ESP_NOTIFICATION_TITLE "ESP3D Notification"
#endif //NOTIFICATION_TITLE
#endif //NOTIFICATION_FEATURE

#if defined (SD_TIMESTAMP_FEATURE) || defined (FILESYSTEM_TIMESTAMP_FEATURE)
#define TIMESTAMP_FEATURE
#endif //SD_TIMESTAMP_FEATURE || FILESYSTEM_TIMESTAMP_FEATURE 

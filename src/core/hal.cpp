/*
  hal.cpp - ESP3D hal class

  Copyright (c) 2014 Luc Lebosse. All rights reserved.

  This code is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This code is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with This code; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "../include/esp3d_config.h"

#if defined(ARDUINO_ARCH_ESP8266)
#include <ESP8266WiFi.h>
#endif //ARDUINO_ARCH_ESP8266
#if defined(ARDUINO_ARCH_ESP32)
#include <soc/soc.h>
#include <soc/rtc_wdt.h>
#include <soc/rtc_cntl_reg.h>
#include <WiFi.h>
#include <esp_task_wdt.h>
#include <driver/adc.h>
TaskHandle_t Hal::xHandle = nullptr;
void rtc_wdt_feed(void);
#endif //ARDUINO_ARCH_ESP32

#include "esp3doutput.h"


uint32_t Hal::_analogRange = 255;
uint32_t Hal::_analogWriteFreq = 1000;

void Hal::pinMode(uint8_t pin, uint8_t mode)
{
#if defined (ARDUINO_ARCH_ESP8266)
    if ((pin == 16) && (mode == INPUT_PULLUP)) {
        ::pinMode(pin, INPUT_PULLDOWN_16);
        return;
    }
#endif
    ::pinMode(pin, mode);
}

#if defined(ARDUINO_ARCH_ESP32)
int Hal::getAnalogWriteChannel(uint8_t pin)
{
    switch (pin) {
#if CONFIG_IDF_TARGET_ESP32
    case 39:
        return ADC1_CHANNEL_3;
    case 36:
        return ADC1_CHANNEL_0;
    case 35:
        return ADC1_CHANNEL_7;
    case 34:
        return ADC1_CHANNEL_6;
    case 33:
        return ADC1_CHANNEL_5;
    case 32:
        return ADC1_CHANNEL_4;
    default:
        return -1;
#else
#error "ADC1_CHANNEL not defined for this chip"
#endif
    }
}
#endif //ARDUINO_ARCH_ESP32

int Hal::analogRead(uint8_t pin)
{
#ifdef ARDUINO_ARCH_ESP8266 //only one ADC on ESP8266 A0     
    (void)pin;
    return ::analogRead (A0);
#else
    return ::analogRead (pin);
#endif
}

bool Hal::analogWrite(uint8_t pin, uint value)
{
    if (value > (_analogRange-1)) {
        return false;
    }
#ifdef ARDUINO_ARCH_ESP8266
    ::analogWrite(pin, value);
#endif //ARDUINO_ARCH_ESP8266
#ifdef ARDUINO_ARCH_ESP32
    ::analogWrite(pin, value);
#endif //ARDUINO_ARCH_ESP32
    return true;
}
void     Hal::analogWriteFreq(uint32_t freq)
{
    _analogWriteFreq = freq;
#ifdef ARDUINO_ARCH_ESP8266
    ::analogWriteFreq(_analogWriteFreq);
#endif //ARDUINO_ARCH_ESP8266
}
void Hal::analogRange(uint32_t range)
{
    _analogRange = range;
    uint8_t resolution = 0;
    switch(_analogRange) {
    case 8191:
        resolution=13;
        break;
    case 1024:
        resolution=10;
        break;
    case 2047:
        resolution=11;
        break;
    case 4095:
        resolution=12;
        break;
    default:
        resolution=8;
        _analogRange = 255;
        break;
    }
    ::analogReadResolution(resolution);
#ifdef ARDUINO_ARCH_ESP8266
    ::analogWriteRange(_analogRange);
#endif //ARDUINO_ARCH_ESP8266
}

//Setup
bool Hal::begin()
{
#if defined(ARDUINO_ARCH_ESP32) && defined(CAMERA_DEVICE)
    log_esp3d("Disable brown out");
    WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0); //disable brownout detector
#endif //ARDUINO_ARCH_ESP32 && CAMERA_DEVICE
    //Clear all wifi state
    WiFi.persistent(false);
    WiFi.disconnect(true);
    WiFi.enableSTA (false);
    WiFi.enableAP (false);
    WiFi.mode (WIFI_OFF);
#if SD_DEVICE_CONNECTION == ESP_SHARED_SD
#if defined(ESP_SD_DETECT_PIN) && ESP_SD_DETECT_PIN != -1
    pinMode (ESP_SD_DETECT_PIN, INPUT);
#endif
    pinMode (ESP_FLAG_SHARED_SD_PIN, OUTPUT);
    digitalWrite(ESP_FLAG_SHARED_SD_PIN, !ESP_FLAG_SHARED_SD_VALUE);
#endif //SD_DEVICE_CONNECTION == ESP_SHARED_SD 
    return true;
}

//End ESP3D
void Hal::end()
{
}

//Watchdog feeder
void Hal::wdtFeed()
{
#ifdef ARDUINO_ARCH_ESP8266
    ESP.wdtFeed();
#endif //ARDUINO_ARCH_ESP8266
#ifdef ARDUINO_ARCH_ESP32
    static uint64_t lastYield = 0;
    uint64_t now = millis();
    if((now - lastYield) > 2000) {
        lastYield = now;
        vTaskDelay(5); //delay 1 RTOS tick
    }
#if !defined(DISABLE_WDT_ESP3DLIB_TASK) && !defined(DISABLE_WDT_CORE_0)
    rtc_wdt_feed();
#endif//!defined(DISABLE_WDT_ESP3DLIB_TASK) && !defined(DISABLE_WDT_CORE_0)
#ifndef DISABLE_WDT_ESP3DLIB_TASK
    if (xHandle && esp_task_wdt_status(xHandle)==ESP_OK) {
        if (esp_task_wdt_reset()!=ESP_OK) {
            log_esp3d("WDT Reset failed");
        }
    }
#endif //DISABLE_WDT_ESP3DLIB_TASK
#endif //ARDUINO_ARCH_ESP32
}

//wait function
void Hal::wait (uint32_t milliseconds)
{
#if defined(ASYNCWEBSERVER)
    uint32_t timeout = millis();
    while ( (millis() - timeout) < milliseconds) {
        wdtFeed();
    }
#else // !(ASYNCWEBSERVER 
    wdtFeed();
    //before 0 was acceptable, now it seems need to put 5 to have some effect if on esp32 core 0
    delay(milliseconds<5?5:milliseconds);
#endif // !ASYNCWEBSERVER
}

uint16_t Hal::getChipID()
{
#ifdef ARDUINO_ARCH_ESP8266
    return ESP.getChipId();
#endif //ARDUINO_ARCH_ESP8266
#ifdef ARDUINO_ARCH_ESP32
    return (uint16_t) (ESP.getEfuseMac() >> 32);
#endif //ARDUINO_ARCH_ESP32
}

bool Hal::has_temperature_sensor()
{
#ifdef ARDUINO_ARCH_ESP8266
    return false;
#endif //ARDUINO_ARCH_ESP8266
#ifdef ARDUINO_ARCH_ESP32
    return true;
#endif //ARDUINO_ARCH_ESP32
}

float Hal::temperature()
{
#ifdef ARDUINO_ARCH_ESP8266
    return 0.0;
#endif //ARDUINO_ARCH_ESP8266
#ifdef ARDUINO_ARCH_ESP32
    return temperatureRead();
#endif //ARDUINO_ARCH_ESP32
}

bool Hal::is_pin_usable(uint pin)
{
#ifdef ARDUINO_ARCH_ESP8266
    if  ((pin <= 5) || ((pin >= 12) && (pin <= 16))) {
        return true;
    } else {
        return false;
    }
#endif //ARDUINO_ARCH_ESP8266
#ifdef ARDUINO_ARCH_ESP32
    //TODO: Add support for ESP32 S2 S3 C2 C3
    if  ((pin <= 5) || ((pin >= 12) && (pin <= 39))) {
        return true;
    } else {
        return false;
    }
#endif //ARDUINO_ARCH_ESP32
}

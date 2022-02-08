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

#include "../include/esp3dlib_config.h"

#include <soc/soc.h>
#include <soc/rtc_cntl_reg.h>
#include <WiFi.h>
#ifdef __cplusplus
extern "C" {
#endif //__cplusplus
esp_err_t esp_task_wdt_reset();
#ifdef __cplusplus
}
#endif //__cplusplus


//Setup
bool Hal::begin()
{
    //Clear all wifi state
    WiFi.persistent(false);
    WiFi.disconnect(true);
    WiFi.enableSTA (false);
    WiFi.enableAP (false);
    WiFi.mode (WIFI_OFF);
    return true;
}



//Watchdog feeder
void Hal::wdtFeed()
{
#ifdef ARDUINO_ARCH_ESP8266
    ESP.wdtFeed();
#endif //ARDUINO_ARCH_ESP8266
#ifdef ARDUINO_ARCH_ESP32
    void esp_task_wdt_feed();
#endif //ARDUINO_ARCH_ESP32
}

//wait function
void Hal::wait (uint32_t milliseconds)
{
    wdtFeed();
    delay(milliseconds);
}

uint16_t Hal::getChipID()
{
    return (uint16_t) (ESP.getEfuseMac() >> 32);
}

bool Hal::has_temperature_sensor()
{
    return true;
}

float Hal::temperature()
{
    return temperatureRead();
}

bool Hal::is_pin_usable(uint pin)
{
    if  ((pin <= 5) || ((pin >= 12) && (pin <= 39))) {
        return true;
    } else {
        return false;
    }
}
